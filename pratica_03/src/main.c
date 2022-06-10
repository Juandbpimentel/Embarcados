/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "gpio.h"
#include "uart.h"
#include "execution_functions.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME 1000000
// pinos do módulo gpio 1
#define pinBEN1 28 // botão 1
#define pinAD12 12 // botão 2
#define pinAD13 13 // led botão 1
#define pinAD14 14 // led botão 2

// pinos dos leds internos do gpio1
#define pinUSR0 21
#define pinUSR1 22
#define pinUSR2 23
#define pinUSR3 24

// state machine
typedef enum _state
{
	SEQ1 = 0,
	SEQ2 = 1,
	SEQ3 = 2,
	SEQ4 = 3,
	SEQ5 = 4
} state;

/*
 *
 * Funções auxiliares de sequenciação dos leds
 *
 */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */

int main(void)
{
	unsigned int opTwoButtons = 0;
	// unsigned int op = SEQ1;
	ucPinNumber pins[] = {pinUSR0, pinUSR1, pinUSR2, pinUSR3};
	ucPinNumber button1 = pinBEN1, button2 = pinAD12; //, pinLedButton1 = pinAD11, pinLedButton2 = pinAD12;

	/*-----------------------------------------------------------------------------
	 *  initialize GPIO and UART modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);

	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);

	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	for (int i = 0; i < 4; i++)
	{
		gpioPinMuxSetup(GPIO1, pins[i], OUTPUT);
	}
	gpioPinMuxSetup(GPIO1, button1, INPUT);
	gpioPinMuxSetup(GPIO1, button2, INPUT);
	delay(1000);

	/*-----------------------------------------------------------------------------
	 *  set pin direction
	 *-----------------------------------------------------------------------------*/

	for (int i = 0; i < 4; i++)
	{
		gpioSetDirection(GPIO1, pins[i], OUTPUT);
	}
	gpioSetDirection(GPIO1, button1, INPUT);
	gpioSetDirection(GPIO1, button2, INPUT);
	delay(1000);

	/*-----------------------------------------------------------------------------
	 *  set pin in LOW level
	 *-----------------------------------------------------------------------------*/

	uartPutString(UART0, "GPIO INPUT Initialized\n", 23);

	allBlink(GPIO1, pins, 4, TIME);
	allBlink(GPIO1, pins, 4, TIME);
	delay(TIME + TIME);
	uartPutString(UART0, "SEQ1 ", 4);
	while (true)
	{

		if (readButton(button1))
		{
			if (readButton(button2))
			{
				opTwoButtons |= 0x3;
				uartPutString(UART0, "SEQ4 ", 4);
			}
			else
			{
				opTwoButtons &= 0 << 0;
				opTwoButtons |= 1 << 1;
				uartPutString(UART0, "SEQ3 ", 4);
			}
		}
		else
		{
			if (readButton(button2))
			{
				opTwoButtons &= 0 << 1;
				opTwoButtons |= 0x1;
				uartPutString(UART0, "SEQ2 ", 4);
			}
			else
			{
				opTwoButtons &= 0 << 1;
				opTwoButtons &= 0 << 0;
				uartPutString(UART0, "SEQ1 ", 4);
			}
		}

		switch (opTwoButtons)
		{
		case SEQ1:
			intercalatedBlink(GPIO1, pins, 4, TIME);
			delay(TIME);
			break;
		case SEQ2:
			sequentialBlink(GPIO1, pins, 4, TIME);
			delay(TIME);
			break;
		case SEQ3:
			allBlink(GPIO1, pins, 4, TIME);
			delay(TIME);
			break;
		case SEQ4:
			farEndBlink(GPIO1, pins, 4, TIME);
			delay(TIME);
			break;
		default:
			break;
		} /* -----  end switch  ----- */
	}

	return (0);
} /* ----------  end of function main  ---------- */

/*
switch (op)
		{
		case SEQ1:
			uartPutString(UART0, "SEQ2", 4);
			op = SEQ2;
			break;
		case SEQ2:
			uartPutString(UART0, "SEQ3", 4);
			op = SEQ3;
			break;
		case SEQ3:
			uartPutString(UART0, "SEQ4", 4);
			op = SEQ4;
			break;
		case SEQ4:
			uartPutString(UART0, "SEQ5", 4);
			op = SEQ5;
			break;
		}

		*/