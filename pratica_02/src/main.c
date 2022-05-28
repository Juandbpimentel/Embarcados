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

#include "hw_types.h"
#include "soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME 5000000
#define TOGGLE (0x01u)

#define CM_PER_GPIO1 0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK (0x00040000u)

#define CM_conf_gpmc_ben1 0x0878
#define CM_conf_gpmc_a5 0x0854
#define CM_conf_gpmc_ad14 0x0838
#define CM_conf_gpmc_a6 0x858
#define CM_conf_gpmc_a7 0x85c
#define CM_conf_gpmc_a8 0x860
#define CM_conf_gpmc_a9 0x864

#define GPIO_OE 0x134
#define pinExtern 14
#define pinUSR0 21
#define pinUSR1 22
#define pinUSR2 23
#define pinUSR3 24
#define dir 0

#define GPIO_CLEARDATAOUT 0x190
#define GPIO_SETDATAOUT 0x194
#define GPIO_DATAOUT 0x13c

unsigned int flagBlink;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void ledInit();
// static void ledInitCustomGpio1(int CM_conf, int gpioPin, int direction);
static void ledToggle();

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int _main(void)
{

	flagBlink = 0; // init flag

	/* Configure the green LED control pin. */
	ledInit();

	while (1)
	{
		/* Change the state of the green LED. */
		ledToggle();
		delay();
		ledToggle();
		delay();
	}

	return (0);
} /* ----------  end of function main  ---------- */

/*FUNCTION*-------------------------------------------------------
 *
 * Function Name : Delay
 * Comments      :
 *END*-----------------------------------------------------------*/
static void delay()
{
	volatile unsigned int ra;
	for (ra = 0; ra < TIME; ra++)
		;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:
 * =====================================================================================
 */
void ledInit()
{

	unsigned int val_temp;
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;

	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
	// HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_ad14) |= 7;
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a6) |= 7;
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a7) |= 7;
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a8) |= 7;
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a9) |= 7;

	/*-----------------------------------------------------------------------------
	 *  set pin direction
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS + GPIO_OE);

	val_temp &= ~(1 << pinExtern);
	val_temp |= (dir << pinExtern);

	val_temp &= ~(1 << pinUSR0);
	val_temp |= (dir << pinUSR0);

	val_temp &= ~(1 << pinUSR1);
	val_temp |= (dir << pinUSR1);

	val_temp &= ~(1 << pinUSR2);
	val_temp |= (dir << pinUSR2);

	val_temp &= ~(1 << pinUSR3);
	val_temp |= (dir << pinUSR3);

	HWREG(SOC_GPIO_1_REGS + GPIO_OE) = val_temp;

} /* -----  end of function ledInit  ----- */

/*
void ledInitCustomGpio1(int CM_conf, int gpioPin, int direction)
{}

*/

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:
 * =====================================================================================
 */

void intercalatedBlink()
{
	flagBlink ^= TOGGLE;

	if (flagBlink)
	{
		// HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinExtern);
		// delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR0);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR2);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR1);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR3);
		delay();
	}
	else
	{
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR3);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR1);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR2);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR0);
		delay();
		// delay();
		// HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinExtern);
	}
}
void sequentialBlink()
{
	flagBlink ^= TOGGLE;

	if (flagBlink)
	{
		// HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinExtern);
		// delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR0);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR1);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR2);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR3);
		delay();
	}
	else
	{
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR3);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR2);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR1);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR0);
		// delay();
		// HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinExtern);
	}
}
void ledToggle()
{
	sequentialBlink();
	sequentialBlink();
	intercalatedBlink();
	intercalatedBlink();
} /* -----  end of function ledToggle  ----- */
