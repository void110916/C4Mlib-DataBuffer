/**
 * @file M128Bios.h
 * @author SB Jiang
 * @date
 * @brief
 */

#include <avr/io.h>
#include <stdint.h>

#include "Bios.h"

#ifndef M128BIOS_H_
#define M128BIOS_H_

/*
 * @author SB Jiang
 * @brief General Constant Macro
 */
#ifndef IN
#define IN 1
#endif
#ifndef INPUT
#define INPUT 0
#endif
#ifndef OUTPUT
#define OUTPUT 1
#endif
#ifndef DISABLE
#define DISABLE 0
#endif
#ifndef ENABLE
#define ENABLE 1
#endif
#ifndef NULL
#define NULL 0
#endif

/** TIMER Batch setting and Operation related Define*/
/*Spectial canstant macro for both TIME and PWM*/
#define TIM_CLKS_SYSCLK 0
#define TIM_CLKS_OSCCLK 1
#define SQUARE_WAVE 1
#define SQUARE_WAVE_A 0
#define SQUARE_WAVE_B 1

#define TOGGLE_TOUT 1
#define N_PULSE 2
#define P_PULSE 3

#define TIM_CLKS_SYSCLK 0
#define TIM_CLKS_OSCCLK 1
#define TIM1_3_SQUARE_WAVE_A 0
#define TIM1_3_SQUARE_WAVE_B 1
#define TIM0_2_SQUARE_WAVE 1
#define TIM0_CLK_Stop 0
#define TIM0_CLK_DIV_BY1 1
#define TIM0_CLK_DIV_BY8 2
#define TIM0_CLK_DIV_BY32 3
#define TIM0_CLK_DIV_BY64 4
#define TIM0_CLK_DIV_BY128 5
#define TIM0_CLK_DIV_BY256 6
#define TIM0_CLK_DIV_BY1024 7

#define TIM123_CLK_Stop 0
#define TIM123_CLK_DIV_BY1 1
#define TIM123_CLK_DIV_BY8 2
#define TIM123_CLK_DIV_BY64 3
#define TIM123_CLK_DIV_BY256 4
#define TIM123_CLK_DIV_BY1024 5
#define TIM123_CLK_EXT_Falling 6
#define TIM123_CLK_EXT_Rising 7

#define TIM0FLAGPARALISTINI                            \
  {                                                    \
    {.Reg_p = &DDRB, .Mask = 0x10, .Shift = 4},        \
        {.Reg_p = &ASSR, .Mask = 0x08, .Shift = 3},    \
        {.Reg_p = &TCCR0, .Mask = 0x48, .Shift = 3},   \
        {.Reg_p = &TCCR0, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR0, .Mask = 0x30, .Shift = 4}, { \
      .Reg_p = &TIMSK, .Mask = 0x02, .Shift = 1        \
    }                                                  \
  }

#define TIM1FLAGPARALISTINI                             \
  {                                                     \
    {.Reg_p = &DDRB, .Mask = 0x20, .Shift = 5},         \
        {.Reg_p = &TCCR1A, .Mask = 0x03, .Shift = 0},   \
        {.Reg_p = &TCCR1B, .Mask = 0x18, .Shift = 3},   \
        {.Reg_p = &TCCR1B, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR1A, .Mask = 0xc0, .Shift = 6}, { \
      .Reg_p = &TIMSK, .Mask = 0x10, .Shift = 4         \
    }                                                   \
  }

#define TIM2FLAGPARALISTINI                            \
  {                                                    \
    {.Reg_p = &DDRB, .Mask = 0x80, .Shift = 7},        \
        {.Reg_p = &TCCR2, .Mask = 0x48, .Shift = 3},   \
        {.Reg_p = &TCCR2, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR2, .Mask = 0x30, .Shift = 4}, { \
      .Reg_p = &TIMSK, .Mask = 0x80, .Shift = 7        \
    }                                                  \
  }

#define TIM3FLAGPARALISTINI                             \
  {                                                     \
    {.Reg_p = &DDRE, .Mask = 0x08, .Shift = 3},         \
        {.Reg_p = &TCCR3A, .Mask = 0x03, .Shift = 0},   \
        {.Reg_p = &TCCR3B, .Mask = 0x18, .Shift = 3},   \
        {.Reg_p = &TCCR3B, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR3A, .Mask = 0xC0, .Shift = 6}, { \
      .Reg_p = &ETIMSK, .Mask = 0x10, .Shift = 4        \
    }                                                   \
  }

/**
 * @brief timer0
 *
 * @param ASn ClockSource
 * @param WGMn0_1 WaveSelection
 * @param CSn0_2 TIME0FreqDivide
 * @param COMn0_1 TIME0WareOut
 * @param DDx WaveOutPin
 * @param OCRn Adjust TIMER0 Cycle
 * @param IntEn Interrupt Enable disable
 */
typedef struct {
  uint8_t DDxn;     // WaveOutPin
  uint8_t ASn;      // ClockSource
  uint8_t WGMn0_1;  // WaveSelection
  uint8_t CSn0_2;   // TIME0FreqDivide
  uint8_t COMn0_1;  // TIME0WareOut
  uint8_t IntEn;    // Interrupt Ena`ble disable
  uint8_t OCRn;     // Adjust TIMER0 Cycle
} Tim8_0HWSetDataStr_t;

/**
 * @brief 8 bits timer
 *
 * @param WGMn0_1 WaveSelection
 * @param CSn0_2 TIME2FreqDivide
 * @param COMn0_1 TIME2WareOut
 * @param DDx WaveOutPin
 * @param OCRn Adjust TIMER2 Cycle
 * @param IntEn Interrupt Enable disable
 */
typedef struct {
  uint8_t DDxn;     // WaveOutPin
  uint8_t WGMn0_1;  // WaveSelection
  uint8_t CSn0_2;   // TIME2FreqDivide
  uint8_t COMn0_1;  // TIME2WareOut
  uint8_t IntEn;    // Interrupt Enable disable
  uint8_t OCRn;     // Adjust TIMER2 Cycle
} Tim8HWSetDataStr_t;

/**
 * @brief 16 bits timer
 *
 * @param WGMn0_1 WaveSelection
 * @param WGMn2_3 WaveSelection
 * @param CSn0_2 TIME13FreqDivide
 * @param COMnA0_1 TIME13WareOut
 * @param DDx WaveOutPin
 * @param OCRn Adjust TIMER13 Cycle
 * @param IntEn Interrupt Enable disable
 */
typedef struct {
  uint8_t DDxn;      // WaveOutPin
  uint8_t WGMn0_1;   // WaveSelection
  uint8_t WGMn2_3;   // WaveSelection
  uint8_t CSn0_2;    // TIME13FreqDivide
  uint8_t COMnA0_1;  // TIME13WareOut
  uint8_t IntEn;     // Interrupt Enable disable
  uint16_t OCRnAL;   // Adjust TIMER13 Cycle
} Tim16HWSetDataStr_t;

typedef union {
  Tim8_0HWSetDataStr_t Str;
  uint8_t List[7];
} Tim8_0HWSetDataUni_t;

typedef union {
  Tim8HWSetDataStr_t Str;
  uint8_t List[6];
} Tim8HWSetDataUni_t;

typedef union {
  Tim16HWSetDataStr_t Str;
  uint8_t List[8];
} Tim16HWSetDataUni_t;

Tim8_0HWSetDataUni_t Tim0HWSetData_uni = {.Str.DDxn = OUTPUT,
                                                 .Str.ASn = TIM_CLKS_SYSCLK,
                                                 .Str.WGMn0_1 = SQUARE_WAVE,
                                                 .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
                                                 .Str.COMn0_1 = ENABLE,
                                                 .Str.IntEn = ENABLE,
                                                 .Str.OCRn = 255};

Tim16HWSetDataUni_t Tim1HWSetData_uni = {.Str.DDxn = OUTPUT,
                                                .Str.WGMn0_1 = SQUARE_WAVE_A,
                                                .Str.WGMn2_3 = SQUARE_WAVE_B,
                                                .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
                                                .Str.COMnA0_1 = ENABLE,
                                                .Str.IntEn = ENABLE,
                                                .Str.OCRnAL = 255};

Tim16HWSetDataUni_t Tim2HWSetData_uni = {.Str.DDxn = OUTPUT,
                                                .Str.WGMn0_1 = SQUARE_WAVE_A,
                                                .Str.WGMn2_3 = SQUARE_WAVE_B,
                                                .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
                                                .Str.COMnA0_1 = ENABLE,
                                                .Str.IntEn = ENABLE,
                                                .Str.OCRnAL = 255};

Tim16HWSetDataUni_t Tim3HWSetData_uni = {.Str.DDxn = OUTPUT,
                                                .Str.WGMn0_1 = SQUARE_WAVE_A,
                                                .Str.WGMn2_3 = SQUARE_WAVE_B,
                                                .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
                                                .Str.COMnA0_1 = ENABLE,
                                                .Str.IntEn = ENABLE,
                                                .Str.OCRnAL = 255};

/**
 * @brief
 * @param IntEnReg_p Interrupt Enable flag Reg address
 * @param IntEnMask Interrupt Enable flag Mask, shift
 * @param IntEnShift
 * @param IntSetReg_p Interrupt flag Set Reg address
 * @param IntSetMask  Interrupt flag Set Mask, shift
 * @param IntSetShift
 * @param CountReg_p T/C Counter Register addr
 * @param CountBytes T/C Counter bytes
 * @param PeriodReg_p T/C Counter Period set Register addr
 * @param PeriodBytes T/C Counter Period set bytes
 */
typedef struct {
  volatile uint8_t* IntEnReg_p;    /*Interrupt Enable flag Reg address*/
  uint8_t IntEnMask, IntEnShift;   /*Interrupt Enable flag Mask, shift*/
  volatile uint8_t* IntSetReg_p;   /*Interrupt flag Set Reg address*/
  uint8_t IntSetMask, IntSetShift; /*Interrupt flag Set Mask, shift*/
  volatile uint8_t* StopReg_p;     /*Stop Count Contral Reg address*/
  uint8_t StopMask, StopShift;     /*Stop Count Contral Mask, shift*/
  volatile uint8_t* StartReg_p;    /*Start Count Reg address*/
  uint8_t StartMask, StartShift;   /*Start Count  Mask, shift*/
  volatile uint8_t* CountReg_p;    /*T/C Counter Register addr*/
  uint8_t CountBytes;              /*T/C Counter bytes*/
  volatile uint8_t* PeriodReg_p;   /*T/C Counter Period set Register addr*/
  uint8_t PeriodBytes;             /*T/C Counter Period set bytes*/
} Tim8OpStr_t;

/**
 * @brief
 * @param IntEnReg_p Interrupt Enable flag Reg address
 * @param IntEnMask Interrupt Enable flag Mask, shift
 * @param IntEnShift
 * @param IntSetReg_p Interrupt flag Set Reg address
 * @param IntSetMask  Interrupt flag Set Mask, shift
 * @param IntSetShift
 * @param CountReg_p T/C Counter Register addr
 * @param CountBytes T/C Counter bytes
 * @param PeriodReg_p T/C Counter Period set Register addr
 * @param PeriodBytes T/C Counter Period set bytes
 */
typedef struct {
  volatile uint8_t* IntEnReg_p;    /*Interrupt Enable flag Reg address*/
  uint8_t IntEnMask, IntEnShift;   /*Interrupt Enable flag Mask, shift*/
  volatile uint8_t* IntSetReg_p;   /*Interrupt flag Set Reg address*/
  uint8_t IntSetMask, IntSetShift; /*Interrupt flag Set Mask, shift*/
  volatile uint8_t* StopReg_p;     /*Stop Count Contral Reg address*/
  uint8_t StopMask, StopShift;     /*Stop Count Contral Mask, shift*/
  volatile uint8_t* StartReg_p;    /*Start Count Reg address*/
  uint8_t StartMask, StartShift;   /*Start Count  Mask, shift*/
  volatile uint8_t* CountReg_p;    /*T/C Counter Register addr*/
  uint8_t CountBytes;              /*T/C Counter bytes*/
  volatile uint8_t* PeriodReg_p;   /*T/C Counter Period set Register addr*/
  uint8_t PeriodBytes;             /*T/C Counter Period set bytes*/
} Tim16OpStr_t;

Tim8OpStr_t Tim0Op_str = {
    .IntEnReg_p = &TIMSK,
    .IntEnMask = 0x02,
    .IntEnShift = 1,
    .StopReg_p = &TCCR0,
    .StopMask = 0x07,
    .StopShift = 0,
    .StartReg_p = &TCCR0,
    .StartMask = 0x07,
    .StartShift = 0,
    .IntSetReg_p = &TIFR,
    .IntSetMask = 0x02,
    .IntSetShift = 1,
    .PeriodReg_p = &OCR0,
    .PeriodBytes = 1,
    .CountReg_p = &TCNT0,
    .CountBytes = 1,
};
Tim16OpStr_t Tim1Op_str = {.IntEnReg_p = &TIMSK,
                           .IntEnMask = 0x10,
                           .IntEnShift = 4,
                           .IntSetReg_p = &TIFR,
                           .IntSetMask = 0x10,
                           .IntSetShift = 4,
                           .StopReg_p = &TCCR1A,
                           .StopMask = 0x07,
                           .StopShift = 0,
                           .StartReg_p = &TCCR1A,
                           .StartMask = 0x07,
                           .StartShift = 0,
                           .CountReg_p = &TCNT1L,
                           .CountBytes = 2,
                           .PeriodReg_p = &OCR1AL,
                           .PeriodBytes = 2};
Tim8OpStr_t Tim2Op_str = {.IntEnReg_p = &TIMSK,
                          .IntEnMask = 0x80,
                          .IntEnShift = 7,
                          .IntSetReg_p = &TIFR,
                          .IntSetMask = 0x80,
                          .IntSetShift = 7,
                          .StopReg_p = &TCCR2,
                          .StopMask = 0x07,
                          .StopShift = 0,
                          .StartReg_p = &TCCR2,
                          .StartMask = 0x07,
                          .StartShift = 0,
                          .CountReg_p = &TCNT2,
                          .CountBytes = 1,
                          .PeriodReg_p = &OCR2,
                          .PeriodBytes = 1};
Tim16OpStr_t Tim3Op_str = {.IntEnReg_p = &ETIMSK,
                           .IntEnMask = 0x10,
                           .IntEnShift = 4,
                           .IntSetReg_p = &ETIFR,
                           .IntSetMask = 0x10,
                           .IntSetShift = 4,
                           .StopReg_p = &TCCR3A,
                           .StopMask = 0x07,
                           .StopShift = 0,
                           .StartReg_p = &TCCR3A,
                           .StartMask = 0x07,
                           .StartShift = 0,
                           .CountReg_p = &TCNT3L,
                           .CountBytes = 2,
                           .PeriodReg_p = &OCR3AL,
                           .PeriodBytes = 2};

HWFlagPara_t Tim0FgGpData_str[6] = TIM0FLAGPARALISTINI;
HWFlagPara_t Tim1FgGpData_str[6] = TIM1FLAGPARALISTINI;
HWFlagPara_t Tim2FgGpData_str[5] = TIM2FLAGPARALISTINI;
HWFlagPara_t Tim3FgGpData_str[6] = TIM3FLAGPARALISTINI;

HWRegPara_t Tim0RegPara_p[1] = {{&OCR0, 1}};
HWRegPara_t Tim1RegPara_p[1] = {{&OCR1AL, 2}};
HWRegPara_t Tim2RegPara_p[1] = {{&OCR2, 1}};
HWRegPara_t Tim3RegPara_p[1] = {{&OCR3AL, 2}};

HWSetStr_t Tim0HWSet_str = {.FlagNum = 6,
                                   .RegNum = 1,
                                   .ListBytes = 7,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};
HWSetStr_t Tim1HWSet_str = {.FlagNum = 6,
                                   .RegNum = 1,
                                   .ListBytes = 8,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};
HWSetStr_t Tim2HWSet_str = {.FlagNum = 5,
                                   .RegNum = 1,
                                   .ListBytes = 6,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};
HWSetStr_t Tim3HWSet_str = {.FlagNum = 6,
                                   .RegNum = 1,
                                   .ListBytes = 8,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};

/************************************************************************/
/** PWM Batch setting and Operation related Define*/
/*Spectial canstant macro for both TIME and PWM*/
// PWM 硬體設定
#define WAVE_OUT_DISABLED 0  // COMn0_1: 禁能輸出脈波
#define SQUARE_WAVE 1        // COMn0_1: 方波(非PWM)
#define PWM_N_PULSE 2        // COMn0_1: 負脈波
#define PWM_P_PULSE 3        // COMn0_1: 正脈波
#define WAVE_OUT_PIN 1       // DDx: 設定PWM接腳輸出

// PWM0,PWM2 硬體設定
#define TIM_CLKS_SYSCLK 0           // ASn:系統振盪器
#define TIM_CLKS_OSCCLK 1           // ASn:外加振盪器
#define PWM02_CENTRAL_ALIGN_WAVE 8  // WGMn0_1:中間對齊
#define PWM02_EDGE_ALIGN_WAVE 9     // WGMn0_1:邊緣對齊
#define TIM0_CLK_DIV_BY1 1          // CSn0_2:除頻Clk/2
#define TIM0_CLK_DIV_BY8 2          // CSn0_2:除頻Clk/8
#define TIM0_CLK_DIV_BY32 3         // CSn0_2:除頻Clk/32
#define TIM0_CLK_DIV_BY64 4         // CSn0_2:除頻Clk/64
#define TIM0_CLK_DIV_BY128 5        // CSn0_2:除頻Clk/128
#define TIM0_CLK_DIV_BY256 6        // CSn0_2:除頻Clk/256
#define TIM0_CLK_DIV_BY1024 7       // CSn0_2:除頻Clk/1024

// PWM1,PWM3 硬體設定
#define PWM13_TOP_ICRn_PFC 0  // WGMn0_1:ICR1提供最高值(Phase&Frequency Correct)
#define PWM13_TOP_OCRnA_PFC \
  1  // WGMn0_1:OCR1A提供最高值(Phase&Frequency Correct)
#define PWM13_TOP_ICRn_F 2          // WGMn0_1:ICR1提供最高值(Fast)
#define PWM13_TOP_OCRnA_F 3         // WGMn0_1:OCR1A提供最高值(Fast)
#define PWM13_CENTRAL_ALIGN_WAVE 2  // WGMn2_3:中間對齊(Phase&Frequency Correct)
#define PWM13_EDGE_ALIGN_WAVE 3  // WGMn2_3:邊緣對齊(Fast)

#define TIM16_CLK_DIV_BY1 1     // CSn0_2:除頻Clk/1
#define TIM16_CLK_DIV_BY8 2     // CSn0_2:除頻Clk/8
#define TIM16_CLK_DIV_BY64 3    // CSn0_2:除頻Clk/64
#define TIM16_CLK_DIV_BY256 4   // CSn0_2:除頻Clk/256
#define TIM16_CLK_DIV_BY1024 5  // CSn0_2:除頻Clk/1024

#define TIM8_CLK_DIV_BY1 1     // CSn0_2:除頻Clk/1
#define TIM8_CLK_DIV_BY8 2     // CSn0_2:除頻Clk/8
#define TIM8_CLK_DIV_BY64 3    // CSn0_2:除頻Clk/64
#define TIM8_CLK_DIV_BY256 4   // CSn0_2:除頻Clk/256
#define TIM8_CLK_DIV_BY1024 5  // CSn0_2:除頻Clk/1024
/*Genetal Type define for TIMER */

#define PWM8_CENTRAL_ALIGN_WAVE 8
#define PWM8_EDGE_ALIGN_WAVE 9
#define PWM16_CAW_TOP_ICRn 0
#define PWM16_CAW_TOP_OCRnA 1
#define PWM16_EAW_TOP_ICRn 2
#define PWM16_EAW_TOP_OCRnA 3
#define PWM16_CENTRAL_ALIGN_WAVE 2
#define PWM16_EDGE_ALIGN_WAVE 3
/*Define Setting Data Structure type for 8 bits PWM0*/
/**
 * @brief
 * @param IntEnReg_p Interrupt Enable flag Reg address
 * @param IntEnMask Interrupt Enable flag Mask, shift
 * @param IntEnShift
 * @param IntSetReg_p Interrupt flag Set Reg address
 * @param IntSetMask Interrupt flag Set Mask, shift
 * @param IntSetShift
 * @param CountReg_p PWM Counter Register addr
 * @param CountBytes PWM Counter bytes
 * @param WidthReg_p PWM Width set Register addr
 * @param WidthBytes PWM Width set byte *
 */
typedef struct {
  volatile uint8_t* IntEnReg_p;
  uint8_t IntEnMask;
  uint8_t IntEnShift;
  volatile uint8_t* IntSetReg_p;
  uint8_t IntSetMask;
  uint8_t IntSetShift;
  volatile uint8_t* CountReg_p;
  uint8_t CountBytes;
  volatile uint8_t* WidthReg_p;
  uint8_t WidthBytes;
} PWMOpStr_t;

/**
 * @brief 8bits PWM0
 *
 * @param DDx             // WaveOutPin
 * @param ASn             // ClockSource
 * @param WGMn0_1         // WaveSelection
 * @param CSn0_2          // PWME0FreqDivide
 * @param COMn0_1         // PWME0WareOut
 * @param IntEn           // PWM interrupt enable
 * @param OCRn            // Adjust PWMER0 Cycle
 *
 */
typedef struct {
  uint8_t DDx;
  uint8_t ASn;
  uint8_t WGMn0_1;
  uint8_t CSn0_2;
  uint8_t COMn0_1;
  uint8_t IntEn;
  uint8_t OCRn;
} PWM8_0HWSetDataStr_t;
/**
 * @brief  8bits PWM
 *
 * @param DDx             // WaveOutPin
 * @param WGMn0_1         // WaveSelection
 * @param CSn0_2          // PWME0FreqDivide
 * @param COMn0_1         // PWME0WareOut
 * @param IntEn           // PWM2 Interrupt Enable
 * @param OCRn            // Adjust PWMER0 Cycle
 */
typedef struct {
  uint8_t DDx;
  uint8_t WGMn0_1;
  uint8_t CSn0_2;
  uint8_t COMn0_1;
  uint8_t IntEn;
  uint8_t OCRn;
} PWM8HWSetDataStr_t;
/**
 * @brief PWM1 or PWM3
 *
 * @param DDxA            // WaveOutPin
 * @param DDxB            // WaveOutPin
 * @param DDxC            // WaveOutPin
 * @param WGMn0_1         // WaveSelection
 * @param WGMn2_3         // WaveSelection
 * @param CSn0_2          // PWMEnFreqDivide
 * @param COMnA0_1        // PWMEnWareOut
 * @param COMnB0_1        // PWMEnWareOut
 * @param COMnC0_1        // PWMEnWareOut
 * @param IntEn           // PWMn Interrupt Enable
 * @param ICRn            // PWMMaxWidth
 * @param OCRnA           // PWMPulseWidth
 * @param OCRnB           // PWMPulseWidth
 * @param OCRnC           // PWMPulseWidth
 */
typedef struct {
  uint8_t DDxA;
  uint8_t DDxB;
  uint8_t DDxC;
  uint8_t WGMn0_1;
  uint8_t WGMn2_3;
  uint8_t CSn0_2;
  uint8_t COMnA0_1;
  uint8_t COMnB0_1;
  uint8_t COMnC0_1;
  uint8_t IntEn;
  uint16_t ICRn;
  uint16_t OCRnA;
  uint16_t OCRnB;
  uint16_t OCRnC;
} PWM16HWSetDataStr_t;

#define PWM0FLAGPARALISTINI                            \
  {                                                    \
    {.Reg_p = &DDRB, .Mask = 0x10, .Shift = 4},        \
        {.Reg_p = &ASSR, .Mask = 0x08, .Shift = 3},    \
        {.Reg_p = &TCCR0, .Mask = 0x48, .Shift = 3},   \
        {.Reg_p = &TCCR0, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR0, .Mask = 0x30, .Shift = 4}, { \
      .Reg_p = &TIMSK, .Mask = 0x01, .Shift = 0        \
    }                                                  \
  }

#define PWM1FLAGPARALISTINI                             \
  {                                                     \
    {.Reg_p = &DDRB, .Mask = 0x20, .Shift = 5},         \
        {.Reg_p = &DDRB, .Mask = 0x40, .Shift = 6},     \
        {.Reg_p = &DDRB, .Mask = 0x80, .Shift = 7},     \
        {.Reg_p = &TCCR1A, .Mask = 0x03, .Shift = 0},   \
        {.Reg_p = &TCCR1B, .Mask = 0x18, .Shift = 3},   \
        {.Reg_p = &TCCR1B, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR1A, .Mask = 0xc0, .Shift = 6},   \
        {.Reg_p = &TCCR1A, .Mask = 0x30, .Shift = 4},   \
        {.Reg_p = &TCCR1A, .Mask = 0x0c, .Shift = 2}, { \
      .Reg_p = &TIMSK, .Mask = 0x04, .Shift = 2         \
    }                                                   \
  }

#define PWM2FLAGPARALISTINI                            \
  {                                                    \
    {.Reg_p = &DDRB, .Mask = 0x80, .Shift = 7},        \
        {.Reg_p = &TCCR2, .Mask = 0x48, .Shift = 3},   \
        {.Reg_p = &TCCR2, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR2, .Mask = 0x30, .Shift = 4}, { \
      .Reg_p = &TIMSK, .Mask = 0x40, .Shift = 6        \
    }                                                  \
  }

#define PWM3FLAGPARALISTINI                             \
  {                                                     \
    {.Reg_p = &DDRE, .Mask = 0x08, .Shift = 3},         \
        {.Reg_p = &DDRE, .Mask = 0x10, .Shift = 4},     \
        {.Reg_p = &DDRE, .Mask = 0x20, .Shift = 5},     \
        {.Reg_p = &TCCR3A, .Mask = 0x03, .Shift = 0},   \
        {.Reg_p = &TCCR3B, .Mask = 0x18, .Shift = 3},   \
        {.Reg_p = &TCCR3B, .Mask = 0x07, .Shift = 0},   \
        {.Reg_p = &TCCR3A, .Mask = 0xc0, .Shift = 6},   \
        {.Reg_p = &TCCR3A, .Mask = 0x30, .Shift = 4},   \
        {.Reg_p = &TCCR3A, .Mask = 0x0c, .Shift = 2}, { \
      .Reg_p = &ETIMSK, .Mask = 0x04, .Shift = 2        \
    }                                                   \
  }

#define PWM0REGPARALISTINI         \
  {                                \
    { .Reg_p = &OCR0, .Bytes = 1 } \
  }

#define PWM1REGPARALISTINI                                         \
  {                                                                \
    {.Reg_p = &ICR1L, .Bytes = 2}, {.Reg_p = &OCR1AL, .Bytes = 2}, \
        {.Reg_p = &OCR1BL, .Bytes = 2}, {                          \
      .Reg_p = &OCR1CL, .Bytes = 2                                 \
    }                                                              \
  }

#define PWM2REGPARALISTINI         \
  {                                \
    { .Reg_p = &OCR2, .Bytes = 1 } \
  }

#define PWM3REGPARALISTINI                                         \
  {                                                                \
    {.Reg_p = &ICR3L, .Bytes = 2}, {.Reg_p = &OCR3AL, .Bytes = 2}, \
        {.Reg_p = &OCR3BL, .Bytes = 2}, {                          \
      .Reg_p = &OCR3CL, .Bytes = 2                                 \
    }                                                              \
  }

#define PWM0OPSTRINI                                            \
  {                                                             \
    .IntEnReg_p = &TIMSK, .IntEnMask = 0x01, .IntEnShift = 0,   \
    .IntSetReg_p = &TIFR, .IntSetMask = 0x01, .IntSetShift = 0, \
    .CountReg_p = &TCNT0, .CountBytes = 1, .WidthReg_p = &OCR0, \
    .WidthBytes = 1                                             \
  }

#define PWM1OPSTRINI                                               \
  {                                                                \
    .IntEnReg_p = &TIMSK, .IntEnMask = 0x04, .IntEnShift = 2,      \
    .IntSetReg_p = &TIFR, .IntSetMask = 0x04, .IntSetShift = 2,    \
    .CountReg_p = &TCNT1L, .CountBytes = 2, .WidthReg_p = &OCR1AL, \
    .WidthBytes = 2                                                \
  }

#define PWM2OPSTRINI                                            \
  {                                                             \
    .IntEnReg_p = &TIMSK, .IntEnMask = 0x40, .IntEnShift = 6,   \
    .IntSetReg_p = &TIFR, .IntSetMask = 0x40, .IntSetShift = 6, \
    .CountReg_p = &TCNT2, .CountBytes = 1, .WidthReg_p = &OCR2, \
    .WidthBytes = 1                                             \
  }

#define PWM3OPSTRINI                                               \
  {                                                                \
    .IntEnReg_p = &ETIMSK, .IntEnMask = 0x04, .IntEnShift = 2,     \
    .IntSetReg_p = &ETIFR, .IntSetMask = 0x10, .IntSetShift = 4,   \
    .CountReg_p = &TCNT3L, .CountBytes = 2, .WidthReg_p = &OCR3AL, \
    .WidthBytes = 2                                                \
  }

typedef union {
  PWM8_0HWSetDataStr_t Str;
  uint8_t List[7];
} Pwm8_0HWSetDataUni_t;

typedef union {
  PWM8HWSetDataStr_t Str;
  uint8_t List[6];
} Pwm8HWSetDataUni_t;

typedef union {
  PWM16HWSetDataStr_t Str;
  uint8_t List[18];
} Pwm16HWSetDataUni_t;

typedef struct {
  volatile uint8_t* IntEnReg_p;    /*Interrupt Enable flag Reg address*/
  uint8_t IntEnMask, IntEnShift;   /*Interrupt Enable flag Mask, shift*/
  volatile uint8_t* IntSetReg_p;   /*Interrupt flag Set Reg address*/
  uint8_t IntSetMask, IntSetShift; /*Interrupt flag Set Mask, shift*/
  volatile uint8_t* StopReg_p;     /*Stop Count Contral Reg address*/
  uint8_t StopMask, StopShift;     /*Stop Count Contral Mask, shift*/
  volatile uint8_t* StartReg_p;    /*Start Count Reg address*/
  uint8_t StartMask, StartShift;   /*Start Count  Mask, shift*/
  volatile uint8_t* CountReg_p;    /*PWM Counter Register addr*/
  uint8_t CountBytes;              /*PWM Counter bytes*/
  volatile uint8_t* WidthReg_p;    /*PWM-A Width set Register addr*/
  uint8_t WidthBytes;              /*PWM-A Width set bytes*/
} Pwm8OpStr_t;
typedef struct {
  volatile uint8_t* IntEnReg_p;    /*Interrupt Enable flag Reg address*/
  uint8_t IntEnMask, IntEnShift;   /*Interrupt Enable flag Mask, shift*/
  volatile uint8_t* IntSetReg_p;   /*Interrupt flag Set Reg address*/
  uint8_t IntSetMask, IntSetShift; /*Interrupt flag Set Mask, shift*/
  volatile uint8_t* StopReg_p;     /*Stop Count Contral Reg address*/
  uint8_t StopMask, StopShift;     /*Stop Count Contral Mask, shift*/
  volatile uint8_t* StartReg_p;    /*Start Count Reg address*/
  uint8_t StartMask, StartShift;   /*Start Count  Mask, shift*/
  volatile uint8_t* CountReg_p;    /*PWM Counter Register addr*/
  uint8_t CountBytes;              /* PWM Counter bytes*/
  volatile uint8_t* WidthAReg_p;   /*PWM-A Width set Register addr*/
  uint8_t WidthABytes;             /*PWM-A Width set bytes*/
  volatile uint8_t* WidthBReg_p;   /*PWM-B Width set Register addr*/
  uint8_t WidthBBytes;             /*PWM-B Width set bytes*/
  volatile uint8_t* WidthCReg_p;   /*PWM-C Width set Register addr*/
  uint8_t WidthCBytes;             /*PWM-C Width set bytes*/
} Pwm16OpStr_t;

HWFlagPara_t Pwm0FlagPara_p[] = PWM0FLAGPARALISTINI;
HWFlagPara_t Pwm1FlagPara_p[] = PWM1FLAGPARALISTINI;
HWFlagPara_t Pwm2FlagPara_p[] = PWM2FLAGPARALISTINI;
HWFlagPara_t Pwm3FlagPara_p[] = PWM3FLAGPARALISTINI;

HWRegPara_t Pwm0RegPara_p[] = PWM0REGPARALISTINI;
HWRegPara_t Pwm1RegPara_p[] = PWM1REGPARALISTINI;
HWRegPara_t Pwm2RegPara_p[] = PWM2REGPARALISTINI;
HWRegPara_t Pwm3RegPara_p[] = PWM3REGPARALISTINI;

Pwm8_0HWSetDataUni_t Pwm0HWSetData_uni = {
    .Str.DDx = OUTPUT,
    .Str.ASn = TIM_CLKS_SYSCLK,
    .Str.WGMn0_1 = PWM8_CENTRAL_ALIGN_WAVE,
    .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
    .Str.COMn0_1 = PWM_P_PULSE,
    .Str.IntEn = ENABLE,
    .Str.OCRn = 128};

Pwm16HWSetDataUni_t Pwm1HWSetData_uni = {
    .Str.DDxA = OUTPUT,
    .Str.DDxB = OUTPUT,
    .Str.DDxC = OUTPUT,
    .Str.WGMn0_1 = PWM16_CAW_TOP_ICRn,
    .Str.WGMn2_3 = PWM16_CENTRAL_ALIGN_WAVE,
    .Str.CSn0_2 = TIM16_CLK_DIV_BY1,
    .Str.COMnA0_1 = PWM_P_PULSE,
    .Str.COMnB0_1 = PWM_P_PULSE,
    .Str.COMnC0_1 = PWM_P_PULSE,
    .Str.IntEn = ENABLE,
    .Str.ICRn = 256,
    .Str.OCRnA = 128,
    .Str.OCRnB = 128,
    .Str.OCRnC = 128};

Pwm8HWSetDataUni_t Pwm2HWSetData_uni = {
    .Str.DDx = OUTPUT,
    .Str.WGMn0_1 = PWM8_CENTRAL_ALIGN_WAVE,
    .Str.CSn0_2 = TIM0_CLK_DIV_BY1,
    .Str.COMn0_1 = PWM_P_PULSE,
    .Str.IntEn = ENABLE,
    .Str.OCRn = 128};

Pwm16HWSetDataUni_t Pwm3HWSetData_uni = {
    .Str.DDxA = OUTPUT,
    .Str.DDxB = OUTPUT,
    .Str.DDxC = OUTPUT,
    .Str.WGMn0_1 = PWM16_CAW_TOP_ICRn,
    .Str.WGMn2_3 = PWM16_CENTRAL_ALIGN_WAVE,
    .Str.CSn0_2 = TIM16_CLK_DIV_BY1,
    .Str.COMnA0_1 = PWM_P_PULSE,
    .Str.COMnB0_1 = PWM_P_PULSE,
    .Str.COMnC0_1 = PWM_P_PULSE,
    .Str.IntEn = ENABLE,
    .Str.ICRn = 256,
    .Str.OCRnA = 128,
    .Str.OCRnB = 128,
    .Str.OCRnC = 128};

HWSetStr_t Pwm0HWSet_str = {.FlagNum = 6,
                                   .RegNum = 1,
                                   .ListBytes = 7,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};

HWSetStr_t Pwm1HWSet_str = {.FlagNum = 10,
                                   .RegNum = 4,
                                   .ListBytes = 18,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};

HWSetStr_t Pwm2HWSet_str = {.FlagNum = 5,
                                   .RegNum = 1,
                                   .ListBytes = 6,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};

HWSetStr_t Pwm3HWSet_str = {.FlagNum = 10,
                                   .RegNum = 4,
                                   .ListBytes = 18,
                                   .TaskId = 0,
                                   .B2BId = 0,
                                   .HWId = 0};

Pwm8OpStr_t Pwm0Op_str = {.IntEnMask = 0x01,
                                 .IntEnShift = 0,
                                 .IntEnReg_p = &TIMSK,
                                 .IntSetMask = 0x01,
                                 .IntSetShift = 0,
                                 .IntSetReg_p = &TIFR,
                                 .CountBytes = 1,
                                 .CountReg_p = &TCNT0,
                                 .WidthBytes = 1,
                                 .WidthReg_p = &OCR0};

Pwm16OpStr_t Pwm1Op_str = {.IntEnMask = 0x04,
                                  .IntEnShift = 2,
                                  .IntEnReg_p = &TIMSK,
                                  .IntSetMask = 0x04,
                                  .IntSetShift = 2,
                                  .IntSetReg_p = &TIFR,
                                  .CountBytes = 2,
                                  .CountReg_p = &TCNT1L,
                                  .WidthABytes = 2,
                                  .WidthAReg_p = &OCR1AL,
                                  .WidthBBytes = 2,
                                  .WidthBReg_p = &OCR1BL,
                                  .WidthCBytes = 2,
                                  .WidthCReg_p = &OCR1CL};

Pwm8OpStr_t Pwm2Op_str = {.IntEnMask = 0x40,
                                 .IntEnShift = 6,
                                 .IntEnReg_p = &TIMSK,
                                 .IntSetMask = 0x40,
                                 .IntSetShift = 6,
                                 .IntSetReg_p = &TIFR,
                                 .CountBytes = 1,
                                 .CountReg_p = &TCNT2,
                                 .WidthBytes = 1,
                                 .WidthReg_p = &OCR2};

Pwm16OpStr_t Pwm3Op_str = {.IntEnMask = 0x04,
                                  .IntEnShift = 2,
                                  .IntEnReg_p = &ETIMSK,
                                  .IntSetMask = 0x10,
                                  .IntSetShift = 4,
                                  .IntSetReg_p = &ETIFR,
                                  .CountBytes = 2,
                                  .CountReg_p = &TCNT3L,
                                  .WidthABytes = 2,
                                  .WidthAReg_p = &OCR3AL,
                                  .WidthBBytes = 2,
                                  .WidthBReg_p = &OCR3BL,
                                  .WidthCBytes = 2,
                                  .WidthCReg_p = &OCR3CL};

/* Public Section End */

/** UART Batch setting and Operation related Define*/
/*Spectial canstant macro for UART*/
#define TXOUTRXIN 0
#define UART_NONE_PARITY 0
#define UART_EVEN_PARITY 2
#define UART_ODD_PARITY 3
#define UART_STOP_BITS_1 0
#define UART_STOP_BITS_2 1
#define UART_WORD_BITS_5BIT 0
#define UART_WORD_BITS_6BIT 1
#define UART_WORD_BITS_7BIT 2
#define UART_WORD_BITS_8BIT 3
#define UART_WORD_BITS_9BIT 3

#define DEFAULTUARTBAUD 38400
#define DEF_UBRR (F_CPU / 16 / DEFAULTUARTBAUD - 1)
/*Genetal Type define for UART */
/*Define Setting Data Structure type for  UART*/
typedef struct {
  uint8_t DDn0_1;   /*TXOUTRXIN*/
  uint8_t DDswi;    /*Switch OUT*/
  uint8_t UMPn0_1;  /* UART_PARITY_NONE*/
  uint8_t USBSn;    /*UART_STOPBITS_1*/
  uint8_t UCSZn0_1; /*UART_WORDBITS_8*/
  uint8_t TXENn;    /*TX ENABLE*/
  uint8_t RXENn;    /*RX ENABLE*/
  uint8_t TXCIEn;   /*TX INT ENABLE*/
  uint8_t RXCIEn;   /*RX INT ENABLE*/
  uint8_t U2Xn;     /* UART DOUBLE Baud Rate*/
  uint8_t UBRRnL;   /* Low Byte of UART Baud Rate*/
  uint8_t UBRRnH;   /* High Byte of UART Baud Rate*/
} UartHWSetDataStr_t;
/*Define Setting Data Union type for UART*/
typedef union {
  UartHWSetDataStr_t Str;
  uint8_t List[12];
} UartHWSetDataUni_t;

/*Define Operation structure type for UART*/
typedef struct {
  volatile uint8_t* TXIntEnReg_p;      /*TX Interrupt Enable flag Reg address*/
  uint8_t TXIntEnMask, TXIntEnShift;   /*TX Interrupt Enable flag Mask, shift*/
  volatile uint8_t* TXIntSetReg_p;     /*TX Interrupt flag Set Reg address*/
  uint8_t TXIntSetMask, TXIntSetShift; /*TX Interrupt flag Set Mask, shift*/
  volatile uint8_t* TXIntClrReg_p;     /* TX Interrupt flag Clear Reg address*/
  uint8_t TXIntClrMask, TXIntClrShift; /*TX Interrupt flag Clear  Mask, shift*/
  volatile uint8_t* TXEnReg_p;         /*UART TX Enable flag Reg address*/
  uint8_t TXEnMask, TXEnShift;         /*UART TX Enable flag Mask, shift*/
  volatile uint8_t* RXIntEnReg_p;      /*RX Interrupt Enable flag Reg address*/
  uint8_t RXIntEnMask, RXIntEnShift;   /*RX Interrupt Enable flag Mask, shift*/
  volatile uint8_t* RXIntSetReg_p;     /*RX Interrupt flag Set Reg address*/
  uint8_t RXIntSetMask, RXIntSetShift; /*RX Interrupt flag Set Mask, shift*/
  volatile uint8_t* RXIntClrReg_p;     /* RX Interrupt flag Clear Reg address*/
  uint8_t RXIntClrMask, RXIntClrShift; /*RX Interrupt flag Clear  Mask, shift*/
  volatile uint8_t* RXEnReg_p;         /* UART RX Enable flag Reg address*/
  uint8_t RXEnMask, RXEnShift;         /*UART RX Enable flag Mask, shift*/
  volatile uint8_t* TXRXSwiReg_p;      /*UART TX/RX Switch Contr Reg address*/
  uint8_t TXRXSwiMask, TXRXSwiShift;   /*UART TX/RX Switch Contr Mask, shift*/
  volatile uint8_t* DataReg_p;         /* UART Data I/O Reg address*/
  uint8_t DataBytes;                   /* UART Data I/O Reg Bytes*/
} UartOpStr_t;
/* UART0 */
/*Define UART HW Set Flag REGFPT parameter array  */
static HWFlagPara_t Uart0FlagPara_p[] = {
    {&DDRE, 0x03, 0},   {&DDRF, 0X08, 3},   {&UCSR0C, 0x30, 4},
    {&UCSR0C, 0x08, 3}, {&UCSR0C, 0x06, 1}, {&UCSR0B, 0x08, 3},
    {&UCSR0B, 0x10, 4}, {&UCSR0B, 0x40, 6}, {&UCSR0B, 0x80, 7},
    {&UCSR0A, 0x02, 1}};
/*Define UART HW Set Reg REGPUT parameter array  */
static HWRegPara_t Uart0RegPara_p[] = {{&UBRR0L, 1}, {&UBRR0H, 1}};
/*Define UART Batch Set setting Data union and initialize */
static UartHWSetDataUni_t Uart0HWSetData_uni = {
    .Str = {.DDn0_1 = TXOUTRXIN,
            .DDswi = OUTPUT,
            .UMPn0_1 = UART_NONE_PARITY,
            .USBSn = UART_STOP_BITS_1,
            .UCSZn0_1 = UART_WORD_BITS_8BIT,
            .TXENn = ENABLE,
            .RXENn = ENABLE,
            .TXCIEn = DISABLE,
            .RXCIEn = DISABLE,
            .U2Xn = DISABLE,
            .UBRRnL = (uint8_t)DEF_UBRR,
            .UBRRnH = (uint8_t)(DEF_UBRR >> 8)}};
/*Define UART Batch Set Function block structure and initialize */
static HWSetStr_t Uart0HWSet_str = {.FlagNum = 10,
                                    .RegNum = 2,
                                    .ListBytes = 12,
                                    .TaskId = 0,
                                    .B2BId = 0,
                                    .HWId = 0};

/*Define UART operatrion structure and initialize */
static UartOpStr_t Uart0Op_str = {.TXIntEnReg_p = &UCSR0B,
                                  .TXIntEnMask = 0x40,
                                  .TXIntEnShift = 6,
                                  .TXIntSetReg_p = &UCSR0A,
                                  .TXIntSetMask = 0x20,
                                  .TXIntSetShift = 5,
                                  .TXIntClrReg_p = &UCSR0A,
                                  .TXIntClrMask = 0x40,
                                  .TXIntClrShift = 6,
                                  .TXEnReg_p = &UCSR0B,
                                  .TXEnMask = 0x10,
                                  .TXEnShift = 3,
                                  .RXIntEnReg_p = &UCSR0B,
                                  .RXIntEnMask = 0x80,
                                  .RXIntEnShift = 7,
                                  .RXIntSetReg_p = &UCSR0A,
                                  .RXIntSetMask = 0x80,
                                  .RXIntSetShift = 7,
                                  .RXIntClrReg_p = &UCSR0A,
                                  .RXIntClrMask = 0x80,
                                  .RXIntClrShift = 7,
                                  .RXEnReg_p = &UCSR0B,
                                  .RXEnMask = 0x40,
                                  .RXEnShift = 4,
                                  .TXRXSwiReg_p = &PORTF,
                                  .TXRXSwiMask = 0x01,
                                  .TXRXSwiShift = 4,
                                  .DataReg_p = &UDR0,
                                  .DataBytes = 1};

#endif