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
#define TIME 1000000
#define TOGGLEINT (0x01u)
#define TOGGLESEQ (0x01u)
#define TOGGLEALL (0x01u)

#define CM_PER_GPIO1 0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK (0x00040000u)

#define CM_conf_gpmc_ad14 0x0838
#define CM_conf_gpmc_ad15 0x083C
#define CM_conf_gpmc_a5 0x0854
#define CM_conf_gpmc_a6 0x858
#define CM_conf_gpmc_a7 0x85c
#define CM_conf_gpmc_a8 0x860

#define GPIO_OE 0x134
#define OUTPUTDIR 0
#define INPUTDIR 1

#define pinAD14 14
#define pinAD15 15
#define pinUSR0 21
#define pinUSR1 22
#define pinUSR2 23
#define pinUSR3 24

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
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_ad14) |= 7;
	HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_ad15) |= 7;
	// HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a5) |= 7;
	// HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a6) |= 7;
	// HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a7) |= 7;
	// HWREG(SOC_CONTROL_REGS + CM_conf_gpmc_a8) |= 7;

	/*-----------------------------------------------------------------------------
	 *  set pin direction
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS + GPIO_OE);

	// input pin
	val_temp &= ~(1 << pinAD14);
	val_temp |= (INPUTDIR << pinAD14);

	// output pins
	val_temp &= ~(1 << pinAD15);
	val_temp |= (OUTPUTDIR << pinAD15);

	val_temp &= ~(1 << pinUSR0);
	val_temp |= (OUTPUTDIR << pinUSR0);

	val_temp &= ~(1 << pinUSR1);
	val_temp |= (OUTPUTDIR << pinUSR1);

	val_temp &= ~(1 << pinUSR2);
	val_temp |= (OUTPUTDIR << pinUSR2);

	val_temp &= ~(1 << pinUSR3);
	val_temp |= (OUTPUTDIR << pinUSR3);

	HWREG(SOC_GPIO_1_REGS + GPIO_OE) = val_temp;

} /* -----  end of function ledInit  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:
 * =====================================================================================
 */

void intercalatedBlink()
{
	flagBlink ^= TOGGLEINT;

	if (flagBlink)
	{

		// leds on
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR0);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR2);
		delay();
		// leds off
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR1);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR3);
		delay();
	}
	else
	{
		// leds on
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR3);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR1);
		delay();

		// leds off
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR2);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR0);
		delay();
		delay();
		opAll();
		opAll();
		opAll();
		// HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinExtern);
	}
}
void sequentialBlink()
{
	flagBlink ^= TOGGLESEQ;

	if (flagBlink)
	{
		// HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinExtern);
		// delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR0);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR1);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR2);
		delay();

		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR3);
		delay();
	}
	else
	{
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR3);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR2);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR1);
		delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR0);
		delay();
		// HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinExtern);
	}
}

void allBlink()
{
	flagBlink ^= TOGGLEALL;

	if (flagBlink)
	{
		// HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinExtern);
		// delay();
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR0);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR1);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR2);
		HWREG(SOC_GPIO_1_REGS + GPIO_SETDATAOUT) = (1 << pinUSR3);
		delay();
	}
	else
	{
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR3);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR2);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR1);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinAD15);
		HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinUSR0);
		delay();
		// HWREG(SOC_GPIO_1_REGS + GPIO_CLEARDATAOUT) = (1 << pinExtern);
	}
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

void ledToggle()
{
	opAll();
	opAll();
	opAll();
	opSequential();
	opIntercaled();
} /* -----  end of function ledToggle  ----- */
