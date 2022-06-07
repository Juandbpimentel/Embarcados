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

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME 5000000

#define TOGGLEALL 0x1
#define TOGGLESEQ 0x1
#define TOGGLEINT 0x1

#define pinAD14INPUT 14
#define pinUSR0 21
#define pinUSR1 22
#define pinUSR2 23
#define pinUSR3 24

// state machine
typedef enum _state
{
	SEQ1 = 1,
	SEQ2 = 2,
	SEQ3 = 3,
	SEQ4 = 4,
	SEQ5 = 5
} state;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(int);
void ledON(gpioMod, ucPinNumber);
void ledOFF(gpioMod, ucPinNumber);

void intercalatedBlink();
void sequentialBlink();
void allBlink();
void opAll();
void opIntercaled();
void opSequential();

/*
 *
 * Funções auxiliares de sequenciação dos leds
 *
 */

void intercalatedBlink()
{

	// leds on
	////ledON(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR0);
	ledON(GPIO1, pinUSR2);
	delay(TIME);
	////ledOFF(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR1);
	ledON(GPIO1, pinUSR3);
	delay(TIME);

	// leds off
	////ledOFF(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR3);
	ledOFF(GPIO1, pinUSR1);
	delay(TIME);
	////ledOFF(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR2);
	ledOFF(GPIO1, pinUSR0);
	delay(TIME);
	// led(GPIO1,pinExtern);
}
void sequentialBlink()
{
	// leds on
	// ledON(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR0);
	delay(TIME);

	// ledOFF(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR1);
	delay(TIME);

	// ledON(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR2);
	delay(TIME);

	// ledOFF(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR3);
	delay(TIME);

	// leds off
	// ledON(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR3);
	delay(TIME);

	// ledOFF(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR2);
	delay(TIME);

	// ledON(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR1);
	delay(TIME);

	// ledOFF(GPIO1, pinAD15);
	ledOFF(GPIO1, pinUSR0);
	delay(TIME);
	// led(GPIO1,pinExtern);
}
void allBlink()
{
	// led(GPIO1,pinExtern);
	// delay();
	// ledON(GPIO1, pinAD15);
	ledON(GPIO1, pinUSR0);
	ledON(GPIO1, pinUSR1);
	ledON(GPIO1, pinUSR2);
	ledON(GPIO1, pinUSR3);
	delay(TIME);

	ledOFF(GPIO1, pinUSR3);
	ledOFF(GPIO1, pinUSR2);
	ledOFF(GPIO1, pinUSR1);
	ledOFF(GPIO1, pinUSR0);
	// ledOFF(GPIO1, pinAD15);
	delay(TIME);
	// led(GPIO1,pinExtern);
}

void opAll()
{
	allBlink();
	allBlink();
}

void opIntercaled()
{
	intercalatedBlink();
	intercalatedBlink();
}

void opSequential()
{
	sequentialBlink();
	sequentialBlink();
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main(void)
{
	unsigned int op = 1;
	ucPinNumber pinIntern0 = pinUSR0,
				pinIntern1 = pinUSR1,
				pinIntern2 = pinUSR2,
				pinIntern3 = pinUSR3,
				pinInputAd14 = pinAD14INPUT;

	/*-----------------------------------------------------------------------------
	 *  initialize GPIO and UART modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);

	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);

	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	gpioPinMuxSetup(GPIO1, pinIntern0, OUTPUT);
	gpioPinMuxSetup(GPIO1, pinIntern1, OUTPUT);
	gpioPinMuxSetup(GPIO1, pinIntern2, OUTPUT);
	gpioPinMuxSetup(GPIO1, pinIntern3, OUTPUT);
	delay(1000);

	gpioPinMuxSetup(GPIO1, pinInputAd14, INPUT);

	/*-----------------------------------------------------------------------------
	 *  set pin direction
	 *-----------------------------------------------------------------------------*/

	gpioSetDirection(GPIO1, pinIntern0, OUTPUT);
	gpioSetDirection(GPIO1, pinIntern1, OUTPUT);
	gpioSetDirection(GPIO1, pinIntern2, OUTPUT);
	gpioSetDirection(GPIO1, pinIntern3, OUTPUT);
	delay(1000);

	gpioSetDirection(GPIO1, pinInputAd14, INPUT);

	/*-----------------------------------------------------------------------------
	 *  set pin in LOW level
	 *-----------------------------------------------------------------------------*/

	uartPutString(UART0, "GPIO INPUT Initialized\n", 22);

	while (true)
	{
		switch (op)
		{
		case SEQ1:
			opIntercaled();
			delay(1000000);
			if (gpioGetPinValue(GPIO1, pinInputAd14))
				op = SEQ2;
			break;
		case SEQ2:
			opSequential();
			delay(1000000);
			if (gpioGetPinValue(GPIO1, pinInputAd14))
				op = SEQ3;
			break;
		case SEQ3:
			opAll();
			delay(1000000);
			if (gpioGetPinValue(GPIO1, pinInputAd14))
				op = SEQ1;
			break;
		default:
			break;
		} /* -----  end switch  ----- */
	}

	return (0);
} /* ----------  end of function main  ---------- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:
 * =====================================================================================
 */
void ledON(gpioMod mod, ucPinNumber pin)
{
	gpioSetPinValue(mod, pin, HIGH);
} /* -----  end of function ledON  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:
 * =====================================================================================
 */
void ledOFF(gpioMod mod, ucPinNumber pin)
{
	gpioSetPinValue(mod, pin, LOW);
} /* -----  end of function ledOFF  ----- */

/*FUNCTION*-------------------------------------------------------
 *
 * Function Name : Delay
 * Comments      :
 *END*-----------------------------------------------------------*/
static void delay(int iTime)
{
	volatile unsigned int ra;
	for (ra = 0; ra < iTime; ra++)
		;
}
