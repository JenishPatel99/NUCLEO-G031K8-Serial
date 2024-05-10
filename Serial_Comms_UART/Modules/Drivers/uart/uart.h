/**
  ******************************************************************************
  * @file           : core.h
  * @brief          : header file
  ******************************************************************************
  */

#ifndef __UART_H
#define __UART_H

#include "main.h"
#include "string.h"

#define UART_RX_BUF_SIZE 128
#define UART_TX_BUF_SIZE 128

int uart_init();
int uart_send(const char *buf);
int uart_receive(char *buf);

#endif
