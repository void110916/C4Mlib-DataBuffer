/**
 * @file remobf.c
 * @author sbjiang Yi-Mou , jerryhappyball , s915888
 * @date 2021.07.07, 2022,03, 25 SBJiang 改版，
 * 增加狀態及錯誤檢查機制，除了REMO
 * BUFFER外都可透過狀態檢查避免上下游工作方塊同時段讀寫同一變數。 REMO BUFFER
 * 提供了保護等式巨集PROTECTED_EQUATION()讓使用者叫用
 * 確保被登錄到REMOBF的變數在執行等式運算時，不被中斷避免上下游工作方塊同時段讀寫同一變數
 * 。
 * @brief
 * Define:
 * RemoBF_lay(): Remo Buffer layout function
 * RemoBF_reg(): Remo Buffer register(Booking) function
 * RemoBF_put(): Remo Buffer write(put) function
 * RemoBF_dist(): Remo Buffer distribution function
 * RemoBF_catch(): Remo Buffer catch function
 * RemoBF_get(): Remo Buffer get(read) function
 * RemoBF_clr(): Remo Buffer clear function
 */

#include "RemoBF.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/*Error Code */
#define OK 0
#define DATA_BUFFER_NON_EXIST_ERROR -1
#define VARI_BUFFER_NON_EXIST_ERROR -2
#define DATA_BUFFER_OVER_REG_ERROR -3
#define VARI_BUFFER_OVER_REG_ERROR -4
#define REMOBF_ILLEGAL_PUT_ERROR -5
#define REMOBF_ILLEGAL_TEMP_ERROR -6
#define REMOBF_ILLEGAL_CATCH_ERROR -7
#define REMOBF_ILLEGAL_GET_ERROR -8
/*State */
#define EMPTY 0
#define FULL 1

/* RemoBF_lay(): Remo Buffer layout function */
void RemoBF_lay(RemoBFStr_t* Str_p, uint8_t* DataList_p,
                RemoVari_t* VariList_p) {
  Str_p->DList_p = DataList_p;
  Str_p->VStr_p = VariList_p;
}

/* RemoBF_reg(): Remo Buffer register(Booking) function */
int16_t RemoBF_reg(RemoBFStr_t* Str_p, void* Data_p, uint8_t Bytes) {
  uint8_t VIndex = Str_p->VariTotal;
  uint8_t RegId = VIndex + 1;
  Str_p->VStr_p[VIndex].Vari_p = Data_p;
  Str_p->VStr_p[VIndex].Bytes = Bytes;
  Str_p->ByteMax = max(Str_p->ByteMax, Bytes);
  if (Str_p->ByteMax >= Str_p->DataDepth)
    Return(DATA_BUFFER_OVER_REG_ERROR);
  Str_p->VariTotal++;
  if (Str_p->VariTotal >= Str_p->VariDepth)
    Return(VARI_BUFFER_OVER_REG_ERROR);
  Str_p->DataTotal += Bytes;
  if (Str_p->DataTotal >= Str_p->DataDepth)
    printf("Warning: Do not use this Remo Buffer with RegId=0 mode");
  return ((int16_t)RegId);
}

/* RemoBF_put(): Remo Buffer write(put) function */
int16_t RemoBF_put(RemoBFStr_t* Str_p, uint8_t RegId, uint8_t Data) {
  if (Str_p->DList_p = NULL) return (DATA_BUFFER_NON_EXIST_ERROR);
  if (Str_p->VStr_p = NULL) return (VARI_BUFFER_NON_EXIST_ERROR);
  RemoVari_t* VStr_p;  // Variable Structure address
  uint8_t Resid;
  if (RegId == 0) {
    if (Str_p->State == FULL) return (REMOBF_ILLEGAL_TEMP_ERROR);
    Str_p->DList_p[Str_p->Dataindex] = Data; /*Temp Data */
    Str_p->Dataindex++;                      /*increase data buffer Index */
    Resid = Str_p->DataTotal - Str_p->Dataindex; /*Residual space*/
    if (Resid == 0) Str_p->State = FULL;
  } else {
    VStr_p = &Str_p->VStr_p[RegId - 1];  // variable address
    if (VStr_p->State == FULL) return (REMOBF_ILLEGAL_TEMP_ERROR);
    Str_p->DList_p[Str_p->Dataindex] = Data; /*temp 1 byte*/
    Str_p->Dataindex++;
    Resid = VStr_p->Bytes - Str_p->Dataindex;
    if (Resid == 0) VStr_p->State = FULL;
  }
  return ((int16_t)Resid); /* Return Residual space in temp */
}

/* RemoBF_dist(): Remo Buffer distribution function */
int16_t RemoBF_dist(RemoBFStr_t* Str_p, uint8_t RegId) {
  if (Str_p->DList_p = NULL) return (DATA_BUFFER_NON_EXIST_ERROR);
  if (Str_p->VStr_p = NULL) return (VARI_BUFFER_NON_EXIST_ERROR);
  uint8_t sreg_temp;
  RemoVari_t* VStr_p;
  Str_p->Dataindex = 0;
  if (RegId == 0) {
    if (Str_p->State == EMPTY) return (REMOBF_ILLEGAL_PUT_ERROR);
    for (uint8_t VIndex = 0; VIndex < Str_p->VariTotal; VIndex++) {  // for all
      VStr_p = &Str_p->VStr_p[VIndex];
      sreg_temp = SREG;  // record whole interrupt flag state
      cli();             // disable whole interrupt
      for (uint8_t i = 0; i < VStr_p->Bytes; i++) {  // for all bytes
        ((uint8_t*)VStr_p->Vari_p)[i] =
            Str_p->DList_p[Str_p->Dataindex];  // Move content from Buffer to
                                               // variable
        Str_p->Dataindex++;
      }
      SREG = sreg_temp; /*Reset Interrupt state to original */
    }
    Str_p->Dataindex = 0;
    Str_p->State = EMPTY;
  } else {
    VStr_p = &Str_p->VStr_p[RegId - 1]; /* address of assinged variable */
    if (VStr_p->State == EMPTY) return (REMOBF_ILLEGAL_PUT_ERROR);
    sreg_temp = SREG;  // record whole interrupt flag state
    cli();             // disable whole interrupt
    for (uint8_t i = 0; i < VStr_p->Bytes;
         i++) { /*for all bytes of this varialbe*/
      ((uint8_t*)VStr_p->Vari_p)[i] = Str_p->DList_p[Str_p->Dataindex];
      Str_p->Dataindex++;
    }
    SREG = sreg_temp; /*Reset Interrupt state to original */
    Str_p->Dataindex = 0;
    VStr_p->State = EMPTY;
  }
  return OK;
}

/* RemoBF_catch(): Remo Buffer catch function */
int16_t RemoBF_catch(RemoBFStr_t* Str_p, uint8_t RegId) {
  if (Str_p->DList_p = NULL) return (DATA_BUFFER_NON_EXIST_ERROR);
  if (Str_p->VStr_p = NULL) return (VARI_BUFFER_NON_EXIST_ERROR);
  uint8_t sreg_temp;
  RemoVari_t* VStr_p;
  Str_p->Dataindex = 0;
  if (RegId == 0) {
    if (Str_p->State == FULL) return (REMOBF_ILLEGAL_CATCH_ERROR);
    for (uint8_t VIndex = 0; VIndex < Str_p->VariTotal;
         VIndex++) {  // for all vari
      VStr_p = &Str_p->VStr_p[VIndex];
      sreg_temp = SREG;  // record whole interrupt flag state
      cli();             // disable whole interrupt
      for (uint8_t i = 0; i < VStr_p->Bytes;
           i++) {  // for all bytes of this vari
        Str_p->DList_p[Str_p->Dataindex] =
            ((uint8_t*)VStr_p
                 ->Vari_p)[i];  // Move content from variable to temp buffer
        Str_p->Dataindex++;
      }
      SREG = sreg_temp; /*Reset Interrupt state to original */
    }
    Str_p->Dataindex = 0;
    Str_p->State = FULL;
  } else {
    VStr_p = &Str_p->VStr_p[RegId - 1]; /* address of assinged variable */
    if (VStr_p->State == FULL) return (REMOBF_ILLEGAL_CATCH_ERROR);
    sreg_temp = SREG;  // record whole interrupt flag state
    cli();             // disable whole interrupt
    for (uint8_t i = 0; i < VStr_p->Bytes;
         i++) { /*for all bytes of this variable*/
      Str_p->DList_p[Str_p->Dataindex] = ((uint8_t*)VStr_p->Vari_p)[i];
      Str_p->Dataindex++;
    }
    SREG = sreg_temp; /*Reset Interrupt state to original */
    Str_p->Dataindex = 0;
    VStr_p->State = FULL;
  }
  return OK;
}

/* RemoBF_get(): Remo Buffer get(read) function */
int16_t RemoBF_get(RemoBFStr_t* Str_p, uint8_t RegId, uint8_t* Data_p) {
  if (Str_p->DList_p = NULL) return (DATA_BUFFER_NON_EXIST_ERROR);
  if (Str_p->VStr_p = NULL) return (VARI_BUFFER_NON_EXIST_ERROR);
  RemoVari_t* VStr_p;  // Variable Structure address
  uint8_t Resid;
  if (RegId == 0) {
    if (Str_p->State == EMPTY) return (REMOBF_ILLEGAL_GET_ERROR);
    *Data_p = Str_p->DList_p[Str_p->Dataindex]; /*Get 1 byte of Data */
    Str_p->Dataindex++;                         /*increase data buffer Index */
    uint8_t Resid = Str_p->DataTotal - Str_p->Dataindex; /*Residual space*/
    if (Resid == 0) Str_p->State = EMPTY;
  } else {
    VStr_p = &Str_p->VStr_p[RegId - 1];  // variable address
    if (VStr_p->State == EMPTY) return (REMOBF_ILLEGAL_GET_ERROR);
    *Data_p = Str_p->DList_p[Str_p->Dataindex]; /*Get 1 byte of Data*/
    Str_p->Dataindex++;
    Resid = VStr_p->Bytes - Str_p->Dataindex;
    if (Resid == 0) VStr_p->State = EMPTY;
  }
  return ((int16_t)Resid); /* Return Residual space in temp */
}

/*  RemoBF_clr(): Remo Buffer clear function*/
int16_t RemoBF_clr(RemoBFStr_t* Str_p) {
  if (Str_p->DList_p = NULL) return (DATA_BUFFER_NON_EXIST_ERROR);
  if (Str_p->VStr_p = NULL) return (VARI_BUFFER_NON_EXIST_ERROR);
  Str_p->Byteindex = 0;  // reset Byte index
  Str_p->Variindex = 0;  // reset Variable index 住址矩陣引數歸零
  Str_p->Dataindex = 0;  // reset Data index 資料矩陣引數歸零
  return (OK);
}
