// #include "Bios.h"

#include <avr/interrupt.h>

#include "M128Bios.h"
/**
 * @declare HardWareSet_lay()
 * @brief 硬體批次設定佈局函式
 * HWSetStr_t* HWSetStr_p：批次設定結構體指標。
 * HWFlagPara_t* HWFlagPara_p：批次設定旗標參數陣列指標。
 * HWRegPara_t* HWRegPara_p：批次設定暫存器參數陣列指標。
 * uint8_t* DataList_p：批次設定值陣列指標。
 */
int HardWareSet_lay(HWSetStr_t *HWSetStr_p, HWFlagPara_t *HWFlagPara_p,
                    HWRegPara_t *HWRegPara_p, uint8_t *DataList_p) {
  HWSetStr_p->FlagPara_p = HWFlagPara_p;
  HWSetStr_p->RegPara_p = HWRegPara_p;
  HWSetStr_p->SetDataList_p = DataList_p;
  return 1;
}

/**
 * @declare HardWareSet_step()
 * @brief 硬體批次設定執行函式
 * void* void_p：批次設定結構體無型態化指標。
 */
uint8_t HardWareSet_step(void *void_p) {
  HWSetStr_t *Str_p = (HWSetStr_t *)void_p;
  int i;
  for (i = 0; i < Str_p->FlagNum; i++) {  // For all flag groups
    volatile uint8_t *Reg_p =
        Str_p->FlagPara_p[i].Reg_p;              // Get Register Address
    uint8_t Mask = Str_p->FlagPara_p[i].Mask;    // Get Flag group mask
    uint8_t Shift = Str_p->FlagPara_p[i].Shift;  // Get Flag group shift
    uint8_t Data = Str_p->SetDataList_p[i];
    // Get Flag group Data Address
    REGFPT(Reg_p, Mask, Shift, Data);  // Call REGFPT
  }
  for (int j = 0; j < Str_p->RegNum; j++) {  // For all registers
    volatile uint8_t *Reg_p =
        Str_p->RegPara_p[j].Reg_p;              // Get Register Address
    uint8_t Bytes = Str_p->RegPara_p[j].Bytes;  // Get Registes Bytes
    uint8_t *Data_p = &(Str_p->SetDataList_p[i]);
    // Get Reg Data Address
    REGPUT(Reg_p, Bytes, Data_p);  // Call REGPUT to put datum
    i = i + Bytes;
  }
  return 0;
}

/**
 * @declare HardWareSet_insp()
 * @brief 硬體批次設定檢視函式
 * HWSetStr_t* Str_p：批次設定結構體指標。
 */
uint8_t HardWare_insp(HWSetStr_t *Str_p) {
  int i;
  for (i = 0; i < Str_p->FlagNum; i++) {  // For all flag groups
    volatile uint8_t *Reg_p =
        Str_p->FlagPara_p[i].Reg_p;              // Get Register Address
    uint8_t Mask = Str_p->FlagPara_p[i].Mask;    // Get Flag group mask
    uint8_t Shift = Str_p->FlagPara_p[i].Shift;  // Get Flag group shift
    uint8_t *Data_p =
        &(Str_p->SetDataList_p[i]);      // Get Flag group Data Address
    REGFGT(Reg_p, Mask, Shift, Data_p);  // Call REGFPT
  }
  for (int j = 0; j < Str_p->RegNum; j++) {  // For all registers
    volatile uint8_t *Reg_p =
        Str_p->RegPara_p[i].Reg_p;                 // Get Register Address
    uint8_t Bytes = Str_p->RegPara_p[i].Bytes;     // Get Registes Bytes
    uint8_t *Data_p = &(Str_p->SetDataList_p[i]);  // Get Reg Data Address
    REGGET(Reg_p, Bytes, Data_p);                  // Call REGPUT to put datum
    i = i + Bytes;
  }
  return 0;
}

/**
 * @define EEPROM_Mem_Read()
 * @brief EEPROM Memory Read function
 * uint16_t Addr, Address in EEPROM
 * uint8_t Bytes, Total bytes tobe Read
 * void *Data_p, Data destanation
 */

#ifndef ENABLE
#define ENABLE 1
#endif

// void EEPROM_Mem_Read(uint16_t Addr, uint8_t Bytes, void *Data_p) {
//   cli();

//   for (uint8_t i = 0; i < Bytes; i++, Addr += i) {
//     while (*EepromOp_str.BusyReg_p & EepromOp_str.BusyMask) {
//       /* Wait till previous write complete */;
//     }

//     /*Put Addr into Address Register*/
//     REGPUT(EepromOp_str.AddrReg_p, EepromOp_str.AddrBytes, &Addr);

//     /*Trigger Read Action */
//     REGFPT(EepromOp_str.RdReg_p, EepromOp_str.RdMask, EepromOp_str.RdShift,
//            ENABLE);
//     /*Get Data from Data Register*/
//     REGGET(EepromOp_str.DataReg_p, EepromOp_str.DataBytes, (Data_p + i));
//   }
//   sei();
// }

/**
 * @define EEPROM_Mem_Write()
 * @brief EEPROM Memory Read function
 * uint16_t Addr, Address in EEPROM
 * uint8_t Bytes, Total bytes tobe Read
 * void *Data_p, Data Source
 */

// void EEPROM_Mem_Write(uint16_t Addr, uint8_t Bytes, void *Data_p) {
//   cli();
//   for (uint8_t i = 0; i < Bytes; i++, Addr += i) {
//     while (*EepromOp_str.BusyReg_p & EepromOp_str.BusyMask) {
//       /* Wait till previous write complete */;
//     }

//     /*Put Addr into Address Register*/
//     REGPUT(EepromOp_str.AddrReg_p, EepromOp_str.AddrBytes, &Addr);
//     /*Put Data_p[i] into Data Register*/
//     REGPUT(EepromOp_str.DataReg_p, EepromOp_str.DataBytes, (Data_p + i));

//     /*Enable Write*/
//     REGFPT(EepromOp_str.WtEnReg_p, EepromOp_str.WtEnMask,
//            EepromOp_str.WtEnShift, ENABLE);

//     /*Trigger Write Action*/
//     REGFPT(EepromOp_str.WtReg_p, EepromOp_str.WtMask, EepromOp_str.WtShift,
//            ENABLE);
//   }
//   sei();
// }