#ifndef __EXECUTION_FUNCTIONS_H
#define __EXECUTION_FUNCTIONS_H

#include "gpio.h"

/*FUNCTION*-------------------------------------------------------
 *
 * Function Name : Delay
 * Comments      :
 *END*-----------------------------------------------------------*/
void delay(int);
void ledON(gpioMod, ucPinNumber);
void ledOFF(gpioMod, ucPinNumber);
int readButton(ucPinNumber);

void intercalatedBlink(gpioMod mod, ucPinNumber pin[], int n, int TIME);
void sequentialBlink(gpioMod mod, ucPinNumber pin[], int n, int TIME);
void allBlink(gpioMod mod, ucPinNumber pin[], int n, int TIME);
void farEndBlink(gpioMod mod, ucPinNumber pin[], int n, int TIME);
void internBlink(gpioMod mod, ucPinNumber pin[], int n, int TIME);

#endif // 	__EXECUTION_FUNCTIONS_H