/**
 * @file std_def.h
 * @author LiYu87
 * @date 2019.09.06
 * @brief Provide C4MLIB standard macros.
 *
 */
#include <stdint.h>

#include "stdio.h"
#ifndef C4MLIB_MACRO_STD_DEF_H
#define C4MLIB_MACRO_STD_DEF_H

/* Public Section Start */
#define DISABLE 0  ///< 0 啟用 @ingroup macro_macro
#define ENABLE 1   ///< 1 關閉 @ingroup macro_macro

/**
 * @brief 確認 EN 是否為 ENABLE 或 DISABLE
 * @ingroup macro_macro
 */
#define IS_ENABLE_OR_DISABLE(EN) ((EN) == DISABLE || (EN) == ENABLE)

#define INPUT 0   ///< 0 輸入 @ingroup macro_macro
#define OUTPUT 1  ///< 1 輸出 @ingroup macro_macro

/**
 * @brief 確認 INOUT 是否為 INPUT 或 OUTPUT
 * @ingroup macro_macro
 */
#define IS_INPUT_OR_OUTPUT(INOUT) ((INOUT) == INPUT || (INOUT) == OUTPUT)
/* Public Section End */
#endif  // C4MLIB_MACRO_STD_DEF_H

/**
 * @file bits_op.h
 * @author LiYu87, cy023
 * @date 2021.01.28
 * @brief Provide standard bitswise operation.
 */

#ifndef C4MLIB_MACRO_BITS_OP_H
#define C4MLIB_MACRO_BITS_OP_H

/**
 * @defgroup macro_macro
 */

/* Public Section Start */
/**
 * @def SETBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief
 */

#define SETBIT(ADDRESS, BIT) ((ADDRESS) |= (1 << BIT))

/**
 * @def CLRBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief
 */
#define CLRBIT(ADDRESS, BIT) ((ADDRESS) &= ~(1 << BIT))

/**
 * @def CHKBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief
 */
#define CHKBIT(ADDRESS, BIT) (((ADDRESS) & (1 << BIT)) == (1 << BIT))

/**
 * @def REGFPT(REG_P, MASK, SHIFT, DATA)
 * @ingroup macro_macro
 * @brief Put bits into Reg_p
 */
#define REGFPT(REG_P, MASK, SHIFT, DATA)                                \
  (*((volatile char *)REG_P) = ((*((volatile char *)REG_P) & (~MASK)) | \
                                (((DATA) << (SHIFT)) & (MASK))))

/**
 * @def REGFGT(REG_P, MASK, SHIFT, DATA_P)
 * @ingroup macro_macro
 * @brief  Get bits in Reg_p
 */
#define REGFGT(REG_P, MASK, SHIFT, DATA_P) \
  (*((volatile char *)DATA_P) =            \
       ((*((volatile char *)REG_P) & (MASK)) >> (SHIFT)))

/**
 * @def REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief Read contant from Data_p variable and write into Register R_p
 */
#define REGPUT(REG_P, BYTES, DATA_P)                                    \
  do {                                                                  \
    for (signed char __putptr = BYTES - 1; __putptr >= 0; __putptr--) { \
      *((volatile char *)REG_P + __putptr) =                            \
          *((volatile char *)DATA_P + __putptr);                        \
    }                                                                   \
  } while (0)

/**
 * @def HF_REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief High byte first write to HW register REG_p
 *
 */
#define HF_REGPUT(REG_P, BYTES, DATA_P)                                 \
  do {                                                                  \
    for (signed char __putptr = BYTES - 1; __putptr >= 0; __putptr--) { \
      *((volatile char *)REG_P + __putptr) =                            \
          *((volatile char *)DATA_P + __putptr);                        \
    }                                                                   \
  } while (0)

/**
 * @def LF_REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief Low byte first write to HW register REG_p
 */
#define LF_REGPUT(REG_P, BYTES, DATA_P)                            \
  do {                                                             \
    for (signed char __putptr = 0; __putptr < BYTES; __putptr++) { \
      *((volatile char *)REG_P + (BYTES - __putptr - 1)) =         \
          *((volatile char *)DATA_P + __putptr);                   \
    }                                                              \
  } while (0)

/**
 * @def REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief Get data from Hard ware register and save to Data_p variable
 */
#define REGGET(REG_P, BYTES, DATA_P)                               \
  do {                                                             \
    for (signed char __getptr = 0; __getptr < BYTES; __getptr++) { \
      *((volatile char *)DATA_P + __getptr) =                      \
          *((volatile char *)REG_P + __getptr);                    \
    }                                                              \
  } while (0)

/**
 * @def HF_REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief High byte first to ge multi-bytes Data
 */
#define HF_REGGET(REG_P, BYTES, DATA_P)                                 \
  do {                                                                  \
    for (signed char __getptr = BYTES - 1; __getptr >= 0; __getptr--) { \
      *((volatile char *)DATA_P + (BYTES - __getptr - 1)) =             \
          *((volatile char *)REG_P + __getptr);                         \
    }                                                                   \
  } while (0)

/**
 * @def LF_REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro Low byte first to ge multi-bytes Data
 * @brief
 */
#define LF_REGGET(REG_P, BYTES, DATA_P)                            \
  do {                                                             \
    for (signed char __getptr = 0; __getptr < BYTES; __getptr++) { \
      *((volatile char *)DATA_P + __getptr) =                      \
          *((volatile char *)REG_P + __getptr);                    \
    }                                                              \
  } while (0)

/**
 * @def HIBYTE16(SOURCE)
 * @ingroup macro_macro
 * @brief Macro to get Hight Byte in 16 bit variable
 */
#define HIBYTE16(SOURCE) (SOURCE >> 8)

/**
 * @def LOBYTE16(SOURCE)
 * @ingroup macro_macro
 * @brief Macro to get Low Byte in 16 bit variable
 */

#define LOBYTE16(SOURCE) (SOURCE & 0xff)
/* Public Section End */

/**
 * @def DELAY(tick)
 * @brief
 */

#define DELAY(tick)                \
  for (int i = 0; i < tick; i++) { \
    __asm__ __volatile__("nop");   \
  }

/**
 * @def HWFlagPara_t
 * @brief HardWare Batch Setting Flags parameter structure type
 */
typedef struct {
  volatile uint8_t *Reg_p; /* Register Pointer */
  uint8_t Mask;            /* Flag Mask  */
  uint8_t Shift;           /*  Flag Shift */
} HWFlagPara_t;

/**
 * @def HWRegPara_t
 * @brief HardWare Batch Setting Register parameter structure type
 */
typedef struct {
  volatile uint8_t *Reg_p;  // Register Pointer
  uint8_t Bytes;            // Byte Number
} HWRegPara_t;

/**
 * @def HWSetStr_t
 * @brief
 */
typedef struct {
  uint8_t FlagNum;             // HardWare Setting Flag-group number
  uint8_t RegNum;              // HardWate Setting Register Number;
  uint8_t ListBytes;           // Total Bytes of Set Data list
  uint8_t TaskId, B2BId, HWId; /*Pipeline TaskId, B2B exchange Id,HardWare Id in
                                  HardWare set command*/
  HWFlagPara_t *FlagPara_p;    // points to Flag parameter
  HWRegPara_t *RegPara_p;      // points to Reg parameter
  uint8_t *SetDataList_p;      // points to DataList
} HWSetStr_t;

/**
 * @declare HardWareSet_lay()
 * @brief 硬體批次設定佈局函式
 * HWSetStr_t* HWSetStr_p：批次設定結構體指標。
 * HWFlagPara_t* HWFlagPara_p：批次設定旗標參數陣列指標。
 * HWRegPara_t* HWRegPara_p：批次設定暫存器參數陣列指標。
 * uint8_t* DataList_p：批次設定值陣列指標。
 */
int HardWareSet_lay(HWSetStr_t *HWSetStr_p, HWFlagPara_t *HWFlagPara_p,
                    HWRegPara_t *HWRegPara_p, uint8_t *DataList_p);

/**
 * @declare HardWareSet_step()
 * @brief 硬體批次設定執行函式
 * void* void_p：批次設定結構體無型態化指標。
 */
uint8_t HardWareSet_step(void *void_p);

/**
 * @declare HardWareSet_insp()
 * @brief
 * HWSetStr_t* Str_p
 */
uint8_t HardWare_insp(HWSetStr_t *Str_p);
void EEPROM_Mem_Read(uint16_t Addr, uint8_t Bytes, void *Data_p);
void EEPROM_Mem_Write(uint16_t Addr, uint8_t Bytes, void *Data_p);
#endif  // C4MLIB_MACRO_BITS_OP_H