/**
  ******************************************************************************
  * @file           : core.c
  * @brief          : Central processing program includes state machine
  ******************************************************************************
  */

#include "core.h"

/**
  * @brief 	Handles command and performs action based on it.
  * 	   	Data to send is copied to output buffer
  * @retval Generic return integer
  * @param 	cmd  string-based command
  * @param  data_to_send  output buffer to store outgoing data
  */
static int handle_command(const char *cmd, char *data_to_send)
{
	if (strcmp(cmd, "temp?") == 0)
	{
		strcpy(data_to_send, "Temperature unknown\n");
		// TODO: Get temperature reading from sensor
	}
	else if (strcmp(cmd, "humid?") == 0)
	{
		strcpy(data_to_send, "Humidity unknown\n");
		// TODO: Get Humidity reading from sensor
	}
	else if (strcmp(cmd, "gps?") == 0)
	{
		strcpy(data_to_send, "Location unknown\n");
		// TODO: Get Location reading from sensor
	}
	else
	{
		strcpy(data_to_send, "Invalid command\n");
	}
	return 0;
}

/**
  * @brief 	Main system loop (or thread)
  * @retval Generic return integer
  */
int core_run()
{
	// Create Tx and Rx uart data buffer
	char tx_buf[UART_TX_BUF_SIZE];
	char rx_buf[UART_RX_BUF_SIZE];

	memset(tx_buf, 0, UART_TX_BUF_SIZE);
	memset(rx_buf, 0, UART_RX_BUF_SIZE);

	// Setup UART to listen for data
	if (uart_init() == -1)
	{
		return -1;
	}

	// Core loop (main thread loop)
	while (1)
	{
		// Check if new data is available
		if (uart_receive(rx_buf) != 0)
		{
			// Toggle user led. Green on board
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
			HAL_Delay(LOOP_DELAY);
		}
		else
		{
			// Handle data from uart
			handle_command((const char *)rx_buf, tx_buf);

			// send data over uart
			uart_send(tx_buf);

			// reset tx_buf and rx_buf
			memset(tx_buf, 0, UART_TX_BUF_SIZE);
			memset(rx_buf, 0, UART_RX_BUF_SIZE);
		}
	}
}
