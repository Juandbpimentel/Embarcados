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

// https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2


#include "auxiliarFunctions.h"
#include "address_regs.h"

#define TIME timeVar

int timeVar = 1000; 

bool flag_btn_1;
bool flag_btn_2;


void timerSetup(void){
     /*  Clock enable for DMTIMER7 TRM 8.1.12.1.25 */
    HWREG(CM_PER_BASE+CM_PER_TIMER7_CLKCTRL) |= 0x2;

	/*  Check clock enable for DMTIMER7 TRM 8.1.12.1.25 */    
    while((HWREG(CM_PER_TIMER7_CLKCTRL) & 0x3) != 0x2);

#ifdef DELAY_USE_INTERRUPT
    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR2) |= (1<<31);//(95 --> Bit 31 do 3º registrador (MIR CLEAR2))
#endif
}


//Configurado com os novos registadores
void gpioSetup(){
  /* set clock for GPIO1, TRM 8.1.12.1.31 */
  HWREG(CM_PER_BASE+CM_PER_GPIO1_CLKCTRL_REGS) = MODULEMODE_ENABLE+OPTFCLKEN_GPIO_1_GDBCLK_FCLK_EN;

  /* clear pin 21 for output, led USR0, TRM 25.3.4.3 */
  HWREG(SOC_GPIO_1_REGS+GPIO_OE_REGS) &= ~(1<<21);
  HWREG(INTC_BASE +INTC_MIR_CLEAR3) |= (1<<2)|(1<<3);// (98 --> Bit 2 do 4º registrador (MIR CLEAR3)) e (99 --> Bit 3 do 4º registrador (MIR CLEAR3))
}


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


void ISR_Handler(void){
	/* Verifica se é interrupção do DMTIMER7 */
	unsigned int irq_number = HWREG(INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 95)
		timerIrqHandler();
	
	if(irq_number == 98){
		putString("button 1 pressed!\n\r",19);
		gpioIsrHandler(btnPIN1);
	}

	if(irq_number == 99){
		putString("button 2 pressed!\n\r",19);
		gpioIsrHandler(btnPIN2);
	}
    
	/* Reconhece a IRQ */
	HWREG(INTC_CONTROL) = 0x1;
}


int main(void){
	pinNum pins[] = {PIN1,PIN2,PIN3,PIN4};
	
	/* Hardware setup */
	gpioSetup();
	timerSetup();
	butConfig();
	ledConfig();
	disableWdt();
	//internBlink(pins,4,TIME);
#ifdef DELAY_USE_INTERRUPT 
	putString("Timer Interrupt: ",17);
#else
	putString("Timer: ",7);
#endif

	while(true){
		if(flag_btn_2){
			if (flag_btn_1)
			{
				if(TIME!= 25)
				TIME = 25;
				putString("superfast\n\r",11);
				goOnGoOutBlink(pins,4,TIME);
			}else{
				putString("fast\n\r",6);
				if(TIME!= 75)
				TIME = 50;
				goOnGoOutBlink(pins,4,TIME);
			}

		}else{
			if (flag_btn_1)
			{
				putString("normal\n\r",8);
				if(TIME!= 150)
				TIME = 200;
				goOnGoOutBlink(pins,4,TIME);
			}else{
				putString("slow!\n\r",7);
				if(TIME!= 250)
					TIME = 250;
				goOnGoOutBlink(pins,4,TIME);
			}
		}
	}

	return(0);
}




