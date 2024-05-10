/**
  ******************************************************************************
  * @file           : uart.c
  * @brief          : Application driver for UART
  ******************************************************************************
  */

#include "uart.h"

extern UART_HandleTypeDef huart2;

// Flag to indicate arrival of new UART data
int new_data_available = 0;
// Local UART Rx buffer
uint8_t uart_rx_buf[UART_RX_BUF_SIZE];

/**
  * @brief 	Initialize UART receive idle interrupt
  * @retval Generic return integer
  */
int uart_init()
{
	if (HAL_UARTEx_ReceiveToIdle_IT(&huart2, uart_rx_buf, UART_RX_BUF_SIZE) != HAL_OK)
	{
		return -1;
	}
	return 0;
}


/**
  * @brief 	Send UART data
  * @retval Generic return integer
  * @param 	buf  Input buffer storing data to send
  */
int uart_send(const char *buf)
{
	// Use polling mode UART transmit as interrupt is not necessary
	if (HAL_UART_Transmit(&huart2, (uint8_t *) buf, UART_TX_BUF_SIZE, 100) != HAL_OK)
	{
		return -1;
	}
	return 0;
}

/**
  * @brief 	Receive UART data
  * @retval Generic return integer
  * @param 	buf  Output buffer storing received data
  */
int uart_receive(char *buf)
{
	if (new_data_available == 1)
	{
		memcpy(buf, uart_rx_buf, UART_RX_BUF_SIZE);
		memset(uart_rx_buf, 0, UART_RX_BUF_SIZE);
		new_data_available = 0;
		return 0;
	}
	return -1;
}

/**
  * @brief 	Modified UART Rx Event Callback
  * @retval Generic return integer
  * @param 	huart  UART Handle type
  * @param  Size   Length of incoming data
  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	new_data_available = 1;
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, (uint8_t *) uart_rx_buf, UART_RX_BUF_SIZE);
}


