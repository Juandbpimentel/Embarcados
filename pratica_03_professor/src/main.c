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

#include	"gpio.h"
#include	"uart.h"


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME						2000000

// state machine
typedef enum _state{
			SEQ1=1,
			SEQ2,
			SEQ3,
			SEQ4,
			SEQ5
}state;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay(int);
void ledON(gpioMod  ,ucPinNumber );
void ledOFF(gpioMod ,ucPinNumber );
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	unsigned int op=SEQ2, count=0; 
	ucPinNumber pin=22;
	
	/*-----------------------------------------------------------------------------
	 *  initialize GPIO and UART modules
	 *-----------------------------------------------------------------------------*/
	gpioInitModule(GPIO1);
	//delay(1000);
	//gpioInitModule(GPIO2);
   	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);

	/*-----------------------------------------------------------------------------
	 *  initialize pin of mudule
	 *-----------------------------------------------------------------------------*/
	for(count=pin; count<25; count++){
		gpioPinMuxSetup(GPIO1, pin, OUTPUT);
		delay(1000);
	}

	gpioPinMuxSetup(GPIO1, 12, INPUT);

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	for(count=pin; count<25; count++){
		gpioSetDirection(GPIO1, pin, OUTPUT);
		delay(1000);
	}

	gpioSetDirection(GPIO1, 12, INPUT);

    /*-----------------------------------------------------------------------------
     *  set pin in LOW level
     *-----------------------------------------------------------------------------*/
    for(count=pin; count<25; count++){
        ledOFF(GPIO1, count);
		delay(1000);
	}
	
	uartPutString(UART0,"GPIO INPUT Initialized\n",22);	
	
	while(true){
					switch (op) {
						case SEQ1:
							ledON(GPIO1, pin);
							delay(1000000);
							ledOFF(GPIO1, pin);
							delay(1000000);
							if(gpioGetPinValue(GPIO1, 12))
								op=SEQ2;
						break;
						case SEQ2:	
							ledON(GPIO1, pin);
							delay(1000000);
							ledOFF(GPIO1, pin);
							delay(1000000);	
							if(gpioGetPinValue(GPIO1, 12))
								op=SEQ3;
						break;
						case SEQ3:	
							ledON(GPIO1, pin+1);
							delay(1000000);
							ledOFF(GPIO1, pin+1);
							delay(1000000);	
							if(gpioGetPinValue(GPIO1, 12))
								op=SEQ4;
						break;
						case SEQ4:	
							ledON(GPIO1, pin+2);
							delay(1000000);
							ledOFF(GPIO1, pin+2);
							delay(1000000);
							if(gpioGetPinValue(GPIO1, 12))
								op=SEQ5;//
						break;
						case SEQ5:
							for(count=pin; count<25; count++)
								ledON(GPIO1, count);
							delay(1000000);
							//delay();
							for(count=pin; count<25; count++)
								ledOFF(GPIO1, count);
							delay(1000000);
							//delay();
							if(gpioGetPinValue(GPIO1, 12))
								op=SEQ2;
						break;
						default:	
						break;
					}				/* -----  end switch  ----- */
	}

	return(0);
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledON
 *  Description:  
 * =====================================================================================
 */
void ledON(gpioMod mod, ucPinNumber pin){
				gpioSetPinValue(mod, pin, HIGH);	
}/* -----  end of function ledON  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOFF
 *  Description:  
 * =====================================================================================
 */
void ledOFF(gpioMod mod,  ucPinNumber pin ){
				gpioSetPinValue(mod, pin, LOW);
}/* -----  end of function ledOFF  ----- */

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(int iTime){
	volatile unsigned int ra;
	for(ra = 0; ra < iTime; ra ++);
}

