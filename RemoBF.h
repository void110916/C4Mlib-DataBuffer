/**
 * @file RemoBF.h
 * @author sbjiang Yi-Mou , jerryhappyball , s915888
 * @date 2021.07.07, 2022,03, 25 SBJiang 改版，
 * 增加狀態及錯誤檢查機制，除了REMO
 * BUFFER外都可透過狀態檢查避免上下游工作方塊同時段讀寫同一變數。 REMO BUFFER
 * 提供了保護等式巨集PROTECTED_EQUATION()讓使用者叫用
 * 確保被登錄到REMOBF的變數在執行等式運算時，不被中斷避免上下游工作方塊同時段讀寫同一變數
 * 。
 * @brief
 * Define:
 *    PROTECTED_EQUATION():  Protect Equation Macro
 *    RemoVari_t: Type of variable parameter Structure
 *    RemoBFStr_t: type of the Remo Buffer management strucure
 * Declear:
 *    RemoBF_lay(): Remo Buffer layout function
 *    RemoBF_reg(): Remo Buffer register(Booking) function
 *    RemoBF_put(): Remo Buffer write(put) function
 *    RemoBF_dist(): Remo Buffer distribution function
 *    RemoBF_catch(): Remo Buffer catch function
 *    RemoBF_get(): Remo Buffer get(read) function
 *    RemoBF_clr(): Remo Buffer clear function
 */

#ifndef C4M_DATABF_REMOBF_H
#define C4M_DATABF_REMOBF_H

#include <stddef.h>
#include <stdint.h>

/**
 * @defgroup remobf_macro
 * @defgroup remobf_func
 * @defgroup remobf_struct
 */

/** Protect Equation Macro
 * @brief Provide memory r/w protection for the variable that booked as remo-IO
 * register
 * @ingroup remobf_macro
 */
#define PROTECTED_EQUATION(A) \
  {                           \
    uint8_t sreg_temp = SREG; \
    cli();                    \
    A;                        \
    SREG = sreg_temp;         \
  }

/**
 * @brief structure type provides field for whole information about remo R/W
 * variable
 * @ingroup remobf_struct
 */
typedef struct {
  uint8_t State;  // Buffer State of the variable, EMPTY: 0,FULL:1
  uint8_t Bytes;  // bytes of  variable
  void* Vari_p;   // address of variable
} RemoVari_t;     /*Structure Type of variable parameter*/

/**
 * @brief type of the Remo Buffer management strucure
 * @ingroup remobf_struct
 */
typedef struct {
  uint8_t State;       // state of Whole Data Buffer Full:1 or Empty:0
  uint8_t Dataindex;   // Data Temp array Index
  uint8_t Variindex;   // Variable Index
  uint8_t Byteindex;   // Byte Index of variable
  uint8_t DataTotal;   // Total Bytes of Data
  uint8_t VariTotal;   // Total Variable
  uint8_t ByteMax;     // Maximum bytes of all the variables,
  uint8_t DataDepth;   // length of the data buffer,
  uint8_t VariDepth;   // length of the variable buffer,
  RemoVari_t* VStr_p;  // Pointers of VariList
  uint8_t* DList_p;    // Pointers of DataList
} RemoBFStr_t;

/**
 * @brief Layout funtion for the remo R/W buffer connect its structure to its
 * data_list and vari_list
 *
 * @ingroup remobf_func
 * @param Str_p  pointer to Remo R/W Buffer structure
 * @param DataList_p address of the Remo Buffer Data list
 * @param VariList_p address of the Remo Buffer variables list
 * @return N/A
 */
void RemoBF_lay(RemoBFStr_t* Str_p, uint8_t* DataList_p,
                RemoVari_t* VariList_p);

/**
 * @brief provide variable to books as a remo R/W register.
 *
 * @ingroup remobf_func
 * @param Str_p : pointer to Remo R/W Buffer structure
 * @param Data_p : pointer address of the variable that booked as a remo R/W
 * Reg
 * @param Bytes : The size of the variable that booked as a remo R/W Reg
 * @return int16_t
 *  1~255:  RegId Register Id,
 *  0:  all variable
 *  -3 : DATA_BUFFER_OVER_REG_ERROR (Data_list Dimention is too small)
 *  -4 : VARI_BUFFER_OVER_REG_ERROR (Variable_list Dimention is too small)
 */
int16_t RemoBF_reg(RemoBFStr_t* Str_p, void* Data_p, uint8_t Bytes);

/**
 * @brief put one byte data to the Remo Buffer.
 *
 * @ingroup remobf_func
 * @param Str_p pointer to Remo R/W Buffer structure
 * @param RegId=1~255: Register Id,  RegId=0: for all the registed variables
 * @param Data：one byte data to be saved into Buffer
 * @return   int16_t:
 *  0:  OK
 * -1:  DATA_BUFFER_NON_EXIST_ERROR (Forget to call RemoBF_lay() before call
 * this function) -2:  VARI_BUFFER_NON_EXIST_ERROR (Forget to call RemoBF_lay()
 * before call this function) -5:  REMOBF_ILLEGAL_PUT_ERROR (Buffer not EMPTY
 * yet)
 *
 */
int16_t RemoBF_put(RemoBFStr_t* Str_p, uint8_t RegId, uint8_t Data);

/**
 * @brief Copy the contain in Remo buffer to the variable with RegId or  *
 * distributes to all of the variables.
 *
 * @ingroup remobf_func
 * @param Str_p :pointer to Remo R/W Buffer structure
 * @param RegId :RegId=1~255: the Register Id,  RegId=0:for all the
 * registed variables
 * @return int16_t
 * >=0 : Residual space in buffer for more recording
 * -1:  DATA_BUFFER_NON_EXIST_ERROR (Forget to call RemoBF_lay() before
 * call this function) -2:  VARI_BUFFER_NON_EXIST_ERROR (Forget to call
 * RemoBF_lay() before call this function) -6:  REMOBF_ILLEGAL_DIST_ERROR
 * (Buffer not FULL yet)
 */
int16_t RemoBF_dist(RemoBFStr_t* Str_p, uint8_t RegId);

/**
 * @brief Collect the whole contain in the variable with RegId or all the
 * * variables and store into Remo Buffer. .
 *
 * @ingroup remobf_func
 * @param Str_p :pointer to Remo R/W Buffer structure
 * @param RegId :RegId=1~255: the Register Id,  RegId=0:for all the
 * registed variables
 * @return int16_t
 * >=0 : Residual space in buffer for more recording
 * -1:  DATA_BUFFER_NON_EXIST_ERROR (Forget to call RemoBF_lay() before
 * call this function) -2:  VARI_BUFFER_NON_EXIST_ERROR (Forget to call
 * RemoBF_lay() before call this function) -7:  REMOBF_ILLEGAL_CATCH_ERROR
 * (Buffer not Empty)
 */
int16_t RemoBF_catch(RemoBFStr_t* Str_p, uint8_t RegId);

/**
 * @brief Get one byte data from the Remo Buffer.
 *
 * @ingroup remobf_func
 * @param Str_p: pointer to Remo R/W Buffer structure
 * @param RegId=1~255: Register Id,  RegId=0: for all the registed
 * variables
 * @param Data_p  the address of destenation variable
 * @return int16_t，
 *  1~255:  RegId Register Id,
 *  0:  all variable
 * -1:  DATA_BUFFER_NON_EXIST_ERROR
 * -2:  VARI_BUFFER_NON_EXIST_ERROR
 * -8:  REMOBF_ILLEGAL_GET_ERROR (Buffer not FULL)
 */
int16_t RemoBF_get(RemoBFStr_t* Str_p, uint8_t RegId, uint8_t* Data_p);

/**
 * @brief Clear the Remo Buffer contain by reset all the index to zero。
 *
 * @ingroup remobf_func
 * @param Str_p: pointer to Remo R/W Buffer structure
 * @return int16_t:
 *  0:  OK
 * -1:  DATA_BUFFER_NON_EXIST_ERROR
 * -2:  VARI_BUFFER_NON_EXIST_ERROR
 */
int16_t RemoBF_clr(RemoBFStr_t* Str_p);

/* Public Section End */
#endif