/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2018 14:32:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "auxiliarFunctions.h"

#define TIME 0x3FFFFFF

bool flag_btn_1;
bool flag_btn_2;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioSetup
 *  Description:  
 * =====================================================================================
 */
void gpioSetup(){
	/* set clock for GPIO1, TRM 8.1.12.1.31 */
	HWREG(CM_PER_GPIO1_CLKCTRL) = 0x40002;

    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR3) |= (1<<2)|(1<<3);// (98 --> Bit 2 do 4º registrador (MIR CLEAR3)) e (99 --> Bit 3 do 4º registrador (MIR CLEAR3))
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  butConfig
 *  Description:  
 * =====================================================================================
 */
void butConfig ( ){
    /*  configure pin mux for input GPIO */
	//gpio_14_btn_01
    HWREG(CM_PER_GPMCAD14_REGS) |= 0x2F;
	//gpio_15_btn_02
	HWREG(CM_PER_GPMCAD15_REGS) |= 0x2F;
	
    /* clear pin 14 and 15 for input, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) |= 1<<14;
	HWREG(GPIO1_OE) |= 1<<15;
	
	flag_btn_1 = false;
	flag_btn_2 = false;

    /* Setting interrupt GPIO pin. */
	HWREG(GPIO1_IRQSTATUS_SET_0) |= 1<<14; 	
	HWREG(GPIO1_IRQSTATUS_SET_1) |= 1<<15; 	

  	/* Enable interrupt generation on detection of a rising edge.*/
	HWREG(GPIO1_RISINGDETECT) |= 1<<14 |  1<<15;	
	HWREG(GPIO1_DEBOUNCENABLE) |= 1<<14 |  1<<15;	
}/* -----  end of function butConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledConfig
 *  Description:  
 * =====================================================================================
 */
void ledConfig ( ){
    /*  configure pin mux for output GPIO */
    HWREG(CM_PER_GPMCA5_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA6_REGS) |= 0x7;
	HWREG(CM_PER_GPMCA7_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA8_REGS) |= 0x7;

    /* clear pin 23 and 24 for output, leds USR3 and USR4, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) &= ~(1<<21);
    HWREG(GPIO1_OE) &= ~(1<<22);
	HWREG(GPIO1_OE) &= ~(1<<23);
    HWREG(GPIO1_OE) &= ~(1<<24);

}/* -----  end of function ledConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioIsrHandler
 *  Description:  
 * =====================================================================================
 */
void gpioIsrHandler(btnPinNum pin){

    /* Clear the status of the interrupt flags */
	switch(pin){
		case 1:
			HWREG(GPIO1_IRQSTATUS_0) |= 1<<14; 
			flag_btn_1 = !(flag_btn_1) ;
			break;
		case 2:
			HWREG(GPIO1_IRQSTATUS_1) |= 1<<15; 
			flag_btn_2 = !(flag_btn_2) ;
			break;
	}

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:  
 * =====================================================================================
 */
void ISR_Handler(void){
	/* Verify active IRQ number */
	unsigned int irq_number = HWREG(INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 98){
		putString("button 1 pressed!\n\r",19);
		gpioIsrHandler(btnPIN1);
	}

	if(irq_number == 99){
		putString("button 2 pressed!\n\r",19);
		gpioIsrHandler(btnPIN2);
	}
    
	/* acknowledge IRQ */
	HWREG(INTC_CONTROL) = 0x1;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	pinNum pins[] = {PIN1,PIN2,PIN3,PIN4};
	/* Hardware setup */
	gpioSetup();
	ledConfig();
	butConfig();
	disableWdt();

	putString("gpio Interrupt...\n\r",19);
	setLedsOFF(pins,3);
	delay(TIME);
	putString("esta ligado\n\r",13);
	while(true){
		if(flag_btn_1){
			if (flag_btn_2)
			{
				allBlink(pins,4,TIME);
			}else{
				intercalatedBlink(pins,4,TIME);
			}

		}else{
			if (flag_btn_2)
			{
				sequentialBlink(pins,4,TIME);
			}else{
				internBlink(pins,4,TIME);
				farEndBlink(pins,4,TIME);
			}
		}
	}

	return(0);
}




