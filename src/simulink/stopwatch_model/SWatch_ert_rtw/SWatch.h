/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: SWatch.h
 *
 * Code generated for Simulink model 'SWatch'.
 *
 * Model version                  : 1.130
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Tue Feb  5 11:30:54 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SWatch_h_
#define RTW_HEADER_SWatch_h_
#include <stddef.h>
#include <string.h>
#ifndef SWatch_COMMON_INCLUDES_
# define SWatch_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* SWatch_COMMON_INCLUDES_ */

#include "SWatch_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define SWatch_M_TYPE                  RT_MODEL_SWatch_T

/* Block signals (default storage) */
typedef struct {
    boolean_T plus_button;             /* '<S1>/plus_button' */
    boolean_T minus_button;            /* '<S1>/minus_button' */
    boolean_T timemode_button;         /* '<S1>/timemode_button' */
    boolean_T timesetmode_button;      /* '<S1>/timesetmode_button' */
    boolean_T alarmsetmode_button;     /* '<S1>/alarmsetmode_button' */
    boolean_T swatchmode_button;       /* '<S1>/swatchmode_button' */
    boolean_T buzzer;                  /* '<S1>/buzzer' */
    boolean_T buzz;                    /* '<S1>/SWatch2018' */
} B_SWatch_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
    int32_T sfEvent;                   /* '<S1>/SWatch2018' */
    uint8_T Output_DSTATE;             /* '<S2>/Output' */
    uint8_T is_TimeCount;              /* '<S1>/SWatch2018' */
    uint8_T is_active_TimeCount;       /* '<S1>/SWatch2018' */
    uint8_T is_Interface;              /* '<S1>/SWatch2018' */
    uint8_T is_active_Interface;       /* '<S1>/SWatch2018' */
    uint8_T is_Stopwatch;              /* '<S1>/SWatch2018' */
    uint8_T was_Stopwatch;             /* '<S1>/SWatch2018' */
    uint8_T is_TimeSet;                /* '<S1>/SWatch2018' */
    uint8_T was_TimeSet;               /* '<S1>/SWatch2018' */
    uint8_T is_AlarmSet;               /* '<S1>/SWatch2018' */
    uint8_T was_AlarmSet;              /* '<S1>/SWatch2018' */
    uint8_T is_StopwatchMgmt;          /* '<S1>/SWatch2018' */
    uint8_T was_StopwatchMgmt;         /* '<S1>/SWatch2018' */
    uint8_T is_active_StopwatchMgmt;   /* '<S1>/SWatch2018' */
    uint8_T is_AlarmMgmt;              /* '<S1>/SWatch2018' */
    uint8_T is_active_AlarmMgmt;       /* '<S1>/SWatch2018' */
    uint8_T is_Buzzing;                /* '<S1>/SWatch2018' */
    uint8_T Ahours;                    /* '<S1>/SWatch2018' */
    uint8_T Aminutes;                  /* '<S1>/SWatch2018' */
    uint8_T hours;                     /* '<S1>/SWatch2018' */
    uint8_T minutes;                   /* '<S1>/SWatch2018' */
    uint8_T seconds;                   /* '<S1>/SWatch2018' */
    uint8_T tenths;                    /* '<S1>/SWatch2018' */
    uint8_T Shours;                    /* '<S1>/SWatch2018' */
    uint8_T Sminutes;                  /* '<S1>/SWatch2018' */
    uint8_T Sseconds;                  /* '<S1>/SWatch2018' */
    uint8_T Stenths;                   /* '<S1>/SWatch2018' */
} DW_SWatch_T;

/* Zero-crossing (trigger) state */
typedef struct {
    ZCSigState SWatch2018_Trig_ZCE[7]; /* '<S1>/SWatch2018' */
} PrevZCX_SWatch_T;

/* Real-time Model Data Structure */
struct tag_RTM_SWatch_T {
    const char_T *errorStatus;
    B_SWatch_T *blockIO;
    PrevZCX_SWatch_T *prevZCSigState;
    DW_SWatch_T *dwork;
};

/* External data declarations for dependent source files */
extern const char *RT_MEMORY_ALLOCATION_ERROR;

/* Model entry point functions */
extern RT_MODEL_SWatch_T *SWatch(boolean_T *SWatch_U_plusbutton, boolean_T
    *SWatch_U_minusbutton, boolean_T *SWatch_U_timemode, boolean_T
    *SWatch_U_timesetmode, boolean_T *SWatch_U_alarmsetmode, boolean_T
    *SWatch_U_swatchmode, uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
    uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode);
extern void SWatch_initialize(RT_MODEL_SWatch_T *const SWatch_M, boolean_T
    *SWatch_U_plusbutton, boolean_T *SWatch_U_minusbutton, boolean_T
    *SWatch_U_timemode, boolean_T *SWatch_U_timesetmode, boolean_T
    *SWatch_U_alarmsetmode, boolean_T *SWatch_U_swatchmode, uint8_T
    *SWatch_Y_hours, uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds,
    uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode);
extern void SWatch_step(RT_MODEL_SWatch_T *const SWatch_M, uint8_T
                        *SWatch_Y_hours, uint8_T *SWatch_Y_minutes, uint8_T
                        *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T
                        *SWatch_Y_mode);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('stopwatch/SWatch')    - opens subsystem stopwatch/SWatch
 * hilite_system('stopwatch/SWatch/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'stopwatch'
 * '<S1>'   : 'stopwatch/SWatch'
 * '<S2>'   : 'stopwatch/SWatch/Counter Limited'
 * '<S3>'   : 'stopwatch/SWatch/SWatch2018'
 * '<S4>'   : 'stopwatch/SWatch/Counter Limited/Increment Real World'
 * '<S5>'   : 'stopwatch/SWatch/Counter Limited/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_SWatch_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
