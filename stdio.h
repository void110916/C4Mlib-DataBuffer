/**
 * @file stdio.h
 * @author LiYu87
 * @brief 宣告初始化 stdio 相關函式原型。
 * @date 2019.4.6
 */

#ifndef C4MLIB_STDIO_STDIO_H
#define C4MLIB_STDIO_STDIO_H

/**
 * @defgroup stdio_func stdio functions
 */

/* Public Section Start */
/**
 * @brief 進行標準IO進行初始化的動作。
 * @ingroup stdio_func
 *
 * 依據各個硬體平台去連結不同的通訊方式到 standard IO 中，
 * 便有printf、scanf等的標準IO操作函式可以使用。
 */
void stdio_lay();
/* Public Section End */

#define C4M_STDIO_init()                                            \
  HardWareSet_lay(&Uart0HWSet_str, Uart0FlagPara_p, Uart0RegPara_p, \
                  Uart0HWSetData_uni.List);                         \
  HardWareSet_step(&Uart0HWSet_str);                                \
  stdio_lay(&Uart0Op_str);
#endif  // C4MLIB_STDIO_STDIO_H
