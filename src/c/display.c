#include <stdio.h>

#include "stm32f4_discovery_lcd.h"
#include "display.h"
#include "WidgetConfig.h"

extern uint8_t hours, minutes, seconds, tenths;
extern uint8_t mode, tsmode, asmode;
/*	s_minutes, s_seconds, s_tenths,
	a_hours, a_minutes;
extern Mode mode;
extern TimeSetMode tsmode;
extern AlarmSetMode asmode;*/


/* Stringify digits */
void strencode2digit(char *str, int digit, bool singledigit)
{
	if (singledigit) {
		str[0] = digit % 10 + '0';
		str[1] = str[2] = 0;
	} else {
		str[0] = digit / 10 + '0';
		str[1] = digit % 10 + '0';
		str[2] = 0;
	}
}


/* Visually update the mode selection panel */
void update_mode_visual(uint8_t old_m, uint8_t m)
{
	// Clear the previous mode marker
	switch(old_m) {
		case TIMEMODE:
			DrawOff(&MyWatchScr[BTIME]);
			break;
		case TIMESETMODE:
			DrawOff(&MyWatchScr[BTIMESET]);
			break;
		case ALARMMODE:
			DrawOff(&MyWatchScr[BALARM]);
			break;
		case SWATCHMODE:
			DrawOff(&MyWatchScr[BSWATCH]);
			break;
		default:
			break;
	}
	// Set the new mode marker
	switch(m) {
		case TIMEMODE:
			DrawOn(&MyWatchScr[BTIME]);
			break;
		case TIMESETMODE:
			DrawOn(&MyWatchScr[BTIMESET]);
			break;
		case ALARMMODE:
			DrawOn(&MyWatchScr[BALARM]);
			break;
		case SWATCHMODE:
			DrawOn(&MyWatchScr[BSWATCH]);
			break;
		default:
			break;
	}
}


/* Print the current time on the LCD screen */
void display_time(uint8_t old_mode)
{
	static unsigned char old_h = 0xFF, old_m = 0xFF, old_s = 0xFF;
	static unsigned char old_ah = 0xFF, old_am = 0xFF;
	static unsigned char old_sm = 0xFF, old_ss = 0xFF, old_st = 0xFF;
	static uint8_t old_tsmode = SETHOURS, old_asmode = ASETMINUTES;
	char str[3];
	uint16_t color;

	// Left-most digits (hours or stopwatch minutes)
	if (((mode == TIMEMODE || mode == TIMESETMODE) && hours != old_h) ||
		(mode == ALARMMODE && hours != old_ah) ||
		(mode == SWATCHMODE && minutes != old_sm) ||
		(mode != old_mode) || (tsmode != old_tsmode) || (asmode != old_asmode))
	{
		strencode2digit(str, (mode == ALARMMODE) ? hours :
				(mode == SWATCHMODE) ? minutes : hours, false);
		color = ((mode == TIMESETMODE && tsmode == SETHOURS) ||
				 (mode == ALARMMODE && asmode == ASETHOURS)) ? Ochre : Black;
		LCD_DrawFilledRect(27, 62, 90, 118, color, color);
		WPrint(&MyWatchScr[HRSSTR], str);
		old_h = hours;
		old_ah = hours;
		old_sm = minutes;
	}

	// Middle digits (minutes or stopwatch seconds)
	if (((mode == TIMEMODE || mode == TIMESETMODE) && minutes != old_m) ||
		(mode == ALARMMODE && minutes != old_am) ||
		(mode == SWATCHMODE && seconds != old_ss) ||
		(mode != old_mode) || (tsmode != old_tsmode) || (asmode != old_asmode))
	{
		strencode2digit(str, (mode == ALARMMODE) ? minutes :
				(mode == SWATCHMODE) ? seconds : minutes, false);
		color = ((mode == TIMESETMODE && tsmode == SETMINUTES) ||
				 (mode == ALARMMODE && asmode == ASETMINUTES)) ? Ochre : Black;
		LCD_DrawFilledRect(100, 62, 160, 118, color, color);
		WPrint(&MyWatchScr[MINSTR], str);
		old_m = minutes;
		old_am = minutes;
		old_ss = seconds;
	}

	// Right-most digits (seconds or stopwatch tenths)
	if ((mode != SWATCHMODE && seconds != old_s) ||
		(mode == SWATCHMODE && tenths != old_st) ||
		(mode != old_mode))
	{
		strencode2digit(str, (mode == ALARMMODE) ? 0 :
				(mode == SWATCHMODE) ? tenths : seconds,
				(mode == SWATCHMODE));
		color = Black;
		LCD_DrawFilledRect(168, 62, 228, 118, color, color);
		WPrint(&MyWatchScr[SECSTR], str);
		old_s = seconds;
		old_st = tenths;
	}

	old_tsmode = tsmode;
	old_asmode = asmode;
}
