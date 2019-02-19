#include <stdio.h>

#include "ee.h"
#include "ee_irq.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"

#include "STMPE811QTR.h"
#include "custom_types.h"
#include "display.h"
#include "Buzzer.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "Swatch.h"
#include "SWatch_types.h"
#include "rtwtypes.h"
#include "debug.h"

#define NO_TOUCH_HOLD		// events generated only on first press, not hold

const char *RT_MEMORY_ALLOCATION_ERROR;		// needed by SWatch.h

RT_MODEL_SWatch_T *Swatch_M;
uint8_T hours=0, minutes=0, seconds=0, tenths=0, mode=0;
uint8_T tsmode = SETHOURS, asmode = ASETHOURS;
boolean_T plusButton;
boolean_T minusButton;
boolean_T timeMode;
boolean_T timesetmode;
boolean_T alarmMode;
boolean_T swatchMode;

char s[64];		// buffer for debug

/* SysTick ISR2 */
ISR2(systick_handler)
{
	CounterTick(myCounter);
}


/* TASK LCD */
TASK(TaskLCD)
{
	static bool pressed = false;
	unsigned int i = 0, px = 0, py = 0;
	TPoint p = {0,0};

	/* Read 6 times and average because my screen is damaged and
	   x-coordinate jitter is very high in some regions */
	while ((i < 6) && GetTouch_SC_Async(&px, &py)) {
		++i;
		p.x += px;
		p.y += py;
	}

	if (i > 0) {
#ifdef NO_TOUCH_HOLD
		if (!pressed) {
#endif
			p.x /= i;
			p.y /= i;
			OnTouch(MyWatchScr, &p);
#ifdef NO_TOUCH_HOLD
		}
		pressed = true;
	} else {
		pressed = false;
#endif
	}
}


void setTimeString(char *watchstr, uint8_T hours, uint8_T minutes, uint8_T seconds, uint8_T tenths, uint8_T mode)
{
	sprintf(watchstr, "%2d:%2d:%2d", hours, minutes, seconds);
}

/* TASK Clock */
unsigned char IsUpdateTime()
{
	unsigned char res;
	static unsigned char oh=0, om=0, os=0;
	if (hours!=oh || minutes!=om || seconds!= os)
		res = 1;
	else
		res = 0;

	oh = hours;
	om = minutes;
	os = seconds;
	return res;
}


void UpdateTime()
{
	unsigned char watchstr[20];
	setTimeString(watchstr, hours, minutes, seconds, tenths, mode);

	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(30, 76, 160, 32);
}


void UpdateMode(unsigned char om, unsigned char m)
{
	switch(om) {
	case 0:
		DrawOff(&MyWatchScr[BTIME]);
		break;
	case 1:
		DrawOff(&MyWatchScr[BTIMESET]);
		break;
	case 2:
		DrawOff(&MyWatchScr[BALARM]);
		break;
	case 3:
		DrawOff(&MyWatchScr[BSWATCH]);
		break;
	}
	switch(m) {
	case 0:
		DrawOn(&MyWatchScr[BTIME]);
		break;
	case 1:
		DrawOn(&MyWatchScr[BTIMESET]);
		break;
	case 2:
		DrawOn(&MyWatchScr[BALARM]);
		break;
	case 3:
		DrawOn(&MyWatchScr[BSWATCH]);
		break;
	}
}


TASK(TaskClock)
{
	unsigned char i;
	static uint8_t oldmode = 8;
	static unsigned char oh = 99, om = 99, os = 99;
	char tstr[3];

	if(IsEvent(TIMEMODE_EV)) timeMode = 1;
	else timeMode = 0;

	if(IsEvent(TIMESETMODE_EV)) timesetmode = 1;
	else timesetmode = 0;

	if(IsEvent(ALARMMODE_EV)) alarmMode = 1;
	else alarmMode = 0;

	if(IsEvent(SWATCHMODE_EV)) swatchMode = 1;
	else swatchMode = 0;

	if(IsEvent(PLUS_EV)) plusButton = 1;
	else plusButton = 0;

	if(IsEvent(MINUS_EV)) minusButton = 1;
	else minusButton = 0;

	SWatch_step(Swatch_M, &hours, &minutes, &seconds, &tenths, &mode);

	// If in timeset mode, select the digit to change
	if (timesetmode == 1 && (oldmode == TIMESETMODE) && (mode == TIMESETMODE))
		tsmode = (tsmode == SETHOURS) ? SETMINUTES : SETHOURS;

	// If in alarmset mode, select the digit to change
	if (alarmMode && (oldmode == ALARMMODE) && (mode == ALARMMODE))
		asmode = (asmode == ASETHOURS) ? ASETMINUTES : ASETHOURS;

	ClearEvents();

	// Plot the current time
	display_time(oldmode);

	// Plot the current mode if it has changed
	if (mode != oldmode) {
		update_mode_visual(oldmode, mode);
		oldmode = mode;
	}
}

/* MAIN TASK  */
int main(void)
{
	// Initialize system and Erika
	SystemInit();
	EE_system_init();

	// Initialize state machine
	Swatch_M = SWatch(
		&plusButton, &minusButton, &timeMode,
		&timesetmode, &alarmMode, &swatchMode,
		&hours, &minutes, &seconds, &tenths, &mode
	);

	SWatch_initialize(Swatch_M,
		&plusButton, &minusButton, &timeMode,
		&timesetmode, &alarmMode, &swatchMode,
		&hours, &minutes, &seconds, &tenths, &mode
	);

	// Initialize systick
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	// Initialize LCD and touchscreen
	IOE_Config();
	STM32f4_Discovery_LCD_Init();

	// Calibrate the touchscreen
	InitTouch(-0.112, 0.0623, -340, 11);

	// Initialize the buzzer
	Buzzer_init();

	// Initialize serial debug
	debug_init();

	// Draw the background
	DrawInit(MyWatchScr);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(Black);
	LCD_DrawFullRect(28, 62, 200, 56);
	WPrint(&MyWatchScr[SEP1STR], ":");
	WPrint(&MyWatchScr[SEP2STR], ":");

	// Program periodic alarms
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	SetRelAlarm(AlarmTaskClock, 10, 100);

	// Forever loop
	for (;;) {}
}


