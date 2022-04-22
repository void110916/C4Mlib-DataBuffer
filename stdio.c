/**
 * @file stdio.c
 * @author LiYu87
 * @brief C4M_STDIO_init的實現。
 * @date 2019.10.13
 * @author SBJiang
 * @brief 1. 修改stdio_getchar,stdio_putchar, 不再直接讀寫暫存器，代以Op
 * Structure 欄位。
 * @brief 2. 刪除C4M_STDIO_init，其硬體設定移至批次設定中執行。
 * @brief 3.
 * 新增stdio_lay()佈局函式，讓使用者呼叫指定&Uart0Op_str或&Uart1Op_str提供選用不同UART的彈性
 * @date 2022.03.09
 */

#include <avr/io.h>
#include <stdio.h>
// #include "M128Bios.h"
#include "stdio.h"
/**
 * @brief ASA M128 標準IO 之 putchar 實現。
 *
 * @param c
 * @param stream
 * @return int
 */
static int stdio_putchar(char c, FILE *stream);

/**
 * @brief ASA M128 標準IO 之 getchar 實現。
 *
 * @param stream
 * @return int
 */
static int stdio_getchar(FILE *stream);

/**
 * @brief 標準IO 管理用的結構。
 *
 * 結構中包含輸出入單位元組該呼叫何種函式及其他資訊。
 * 會被 avrlibc 中的標準IO函式(getc、putc、printf、scanf等)所使用。
 */
static FILE STDIO_BUFFER =
    FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar, _FDEV_SETUP_RW);

static int stdio_putchar(char c, FILE *stream) {
  if (c == '\n') stdio_putchar('\r', stream);
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = c;

  return 0;
}

static int stdio_getchar(FILE *stream) {
  int UDR_Buff;
  while (!(UCSR0A & (1 << RXC0)))
    ;
  UDR_Buff = UDR0;

  return UDR_Buff;
}

void stdio_lay() {
  stdout = &STDIO_BUFFER;
  stdin = &STDIO_BUFFER;
}


