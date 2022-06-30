#include "auxiliarFunctions.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
    volatile unsigned int count;
    
	for(count=0; count<mSec; count++);

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putCh
 *  Description:  
 * =====================================================================================
 */
void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));

	HWREG(UART0_THR) = c;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getCh
 *  Description:  
 * =====================================================================================
 */
char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));

	return(HWREG(UART0_RHR));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putString
 *  Description:  
 * =====================================================================================
 */
int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  
 * =====================================================================================
 */
int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
}


void intercalatedBlink(pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 2;
    // leds on
    ////ledON(pinAD15);
    ledON(pins[0]);
    ledON(pins[2]);
    delay(TIME);
    ////ledOFF(pinAD15);
    ledON(pins[1]);
    ledON(pins[3]);
    delay(TIME);

    // leds off
    ////ledOFF(pinAD15);
    ledOFF(pins[0]);
    ledOFF(pins[2]);
    delay(TIME);
    ////ledOFF(pinAD15);
    ledOFF(pins[1]);
    ledOFF(pins[3]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void sequentialBlink(pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 4;
    // leds on
    // ledON(pinAD15);
    ledON(pins[0]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledON(pins[1]);
    delay(TIME);

    // ledON(pinAD15);
    ledON(pins[2]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledON(pins[3]);
    delay(TIME);

    // leds off
    // ledON(pinAD15);
    ledOFF(pins[3]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledOFF(pins[2]);
    delay(TIME);

    // ledON(pinAD15);
    ledOFF(pins[1]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledOFF(pins[0]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void allBlink(pinNum pins[], int n, unsigned int TIME)
{
    // led(GPIO1,pinExtern);
    // delay();
    // ledON(pinAD15);
    for (int i = 0; i < n; i++)
    {
        ledON(pins[i]);
    }

    delay(TIME);

    for (int i = n - 1; i >= 0; i--)
    {
        ledOFF(pins[i]);
    }
    // ledOFF(pinAD15);
    delay(TIME);
    // led(GPIO1,pinExtern);
}

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readBut
 *  Description:  
 * =====================================================================================
 */
unsigned int readBut (btnPinNum pin){
	unsigned int temp;
	switch (pin)
	{
	case 1:
		temp = HWREG(GPIO1_DATAIN)&1<<14;
		break;
	case 2:
		temp = HWREG(GPIO1_DATAIN)&1<<15;
		break;
	default:
		break;
	}
	
	
	return(temp);
}/* -----  end of function readBut  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<21);
			break;
		case PIN2:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<22);
			break;
		case PIN3:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<23);
			break;
		case PIN4:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<24);
			break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
void ledON(pinNum pin){
	
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_SETDATAOUT) |= (1<<21);
			break;
		case PIN2:	
			HWREG(GPIO1_SETDATAOUT) |= (1<<22);
			break;
		case PIN3:
			HWREG(GPIO1_SETDATAOUT) |= (1<<23);
			break;
		case PIN4:	
			HWREG(GPIO1_SETDATAOUT) |= (1<<24);
			break;
	}/* -----  end switch  ----- */
}

void farEndBlink(pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 2;
    ledON(pins[0]);
    ledON(pins[3]);
    delay(TIME);
    ledOFF(pins[0]);
    ledOFF(pins[3]);
    delay(TIME);
    ledON(pins[0]);
    ledON(pins[3]);
    delay(TIME);
    ledOFF(pins[0]);
    ledOFF(pins[3]);
    delay(TIME);
}

void internBlink(pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 2;
    ledON(pins[1]);
    ledON(pins[2]);
    delay(TIME);
    ledOFF(pins[1]);
    ledOFF(pins[2]);
    delay(TIME);
    ledON(pins[1]);
    ledON(pins[2]);
    delay(TIME);
    ledOFF(pins[1]);
    ledOFF(pins[2]);
    delay(TIME);
}

void setLedsOFF(pinNum pins[], int n){
    for (int i = 0; i < n; i++){
		ledOFF(pins[i]);
	}
}