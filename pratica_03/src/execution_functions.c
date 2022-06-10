#include "execution_functions.h"

void intercalatedBlink(gpioMod mod, ucPinNumber pins[], int n, int TIME)
{

    // leds on
    ////ledON(GPIO1, pinAD15);
    ledON(mod, pins[0]);
    ledON(mod, pins[2]);
    delay(TIME);
    ////ledOFF(GPIO1, pinAD15);
    ledON(mod, pins[1]);
    ledON(mod, pins[3]);
    delay(TIME);

    // leds off
    ////ledOFF(GPIO1, pinAD15);
    ledOFF(mod, pins[0]);
    ledOFF(mod, pins[2]);
    delay(TIME);
    ////ledOFF(GPIO1, pinAD15);
    ledOFF(mod, pins[1]);
    ledOFF(mod, pins[3]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void sequentialBlink(gpioMod mod, ucPinNumber pins[], int n, int TIME)
{
    // leds on
    // ledON(GPIO1, pinAD15);
    ledON(GPIO1, pins[0]);
    delay(TIME);

    // ledOFF(GPIO1, pinAD15);
    ledON(GPIO1, pins[1]);
    delay(TIME);

    // ledON(GPIO1, pinAD15);
    ledON(GPIO1, pins[2]);
    delay(TIME);

    // ledOFF(GPIO1, pinAD15);
    ledON(GPIO1, pins[3]);
    delay(TIME);

    // leds off
    // ledON(GPIO1, pinAD15);
    ledOFF(GPIO1, pins[3]);
    delay(TIME);

    // ledOFF(GPIO1, pinAD15);
    ledOFF(GPIO1, pins[2]);
    delay(TIME);

    // ledON(GPIO1, pinAD15);
    ledOFF(GPIO1, pins[1]);
    delay(TIME);

    // ledOFF(GPIO1, pinAD15);
    ledOFF(GPIO1, pins[0]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void allBlink(gpioMod mod, ucPinNumber pins[], int n, int TIME)
{
    // led(GPIO1,pinExtern);
    // delay();
    // ledON(GPIO1, pinAD15);
    for (int i = 0; i < n; i++)
    {
        ledON(mod, pins[i]);
    }

    delay(TIME);

    for (int i = n - 1; i >= 0; i--)
    {
        ledOFF(mod, pins[i]);
    }
    // ledOFF(GPIO1, pinAD15);
    delay(TIME);
    // led(GPIO1,pinExtern);
}

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

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

int readButton(ucPinNumber pin)
{
    return (HWREG(SOC_GPIO_1_REGS + GPIO_DATAIN) & (1 << pin)) ? 1 : 0;
}

void delay(int iTime)
{
    volatile unsigned int ra;
    for (ra = 0; ra < iTime; ra++)
        ;
}

void farEndBlink(gpioMod mod, ucPinNumber pins[], int n, int TIME)
{
    ledON(GPIO1, pins[0]);
    ledON(GPIO1, pins[3]);
    delay(TIME);
    ledOFF(GPIO1, pins[0]);
    ledOFF(GPIO1, pins[3]);
    delay(TIME);
    ledON(GPIO1, pins[0]);
    ledON(GPIO1, pins[3]);
    delay(TIME);
    ledOFF(GPIO1, pins[0]);
    ledOFF(GPIO1, pins[3]);
    delay(TIME);
}

void internBlink(gpioMod mod, ucPinNumber pins[], int n, int TIME)
{
    ledON(GPIO1, pins[1]);
    ledON(GPIO1, pins[2]);
    delay(TIME);
    ledOFF(GPIO1, pins[1]);
    ledOFF(GPIO1, pins[2]);
    delay(TIME);
    ledON(GPIO1, pins[1]);
    ledON(GPIO1, pins[2]);
    delay(TIME);
    ledOFF(GPIO1, pins[1]);
    ledOFF(GPIO1, pins[2]);
    delay(TIME);
}