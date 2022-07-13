#include "auxiliarFunctions.h"

#define TIME timeVar

int timeVar = 1000; 

bool flag_btn_1 = false;
bool flag_btn_2 = false;
bool flag_btn_3 = false;
bool flag_btn_4 = false;

static molePosition actualPositionMole = role1;

void timerSetup(void){
	HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) |= MODULEMODE_ENABLE;

	while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) & 0x3) != MODULEMODE_ENABLE);


#if DELAY_USE_INTERRUPT
    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR2) |= (1<<31);//(95 --> Bit 31 do 3º registrador (MIR CLEAR2))
#endif
}


//Configurado com os novos registadores
void gpioSetup(){
  /* Set clock for GPIO1 and GPIO2 */
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1) |= OPTFCLKEN_GPIO_GDBCLK_FCLK_EN + MODULEMODE_ENABLE;
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO2) |= OPTFCLKEN_GPIO_GDBCLK_FCLK_EN + MODULEMODE_ENABLE;

	/* Interrupt mask */
	HWREG(INTC_BASE + INTC_MIR_CLEAR3) |= INT_CONFIG_BIT(GPIO_INT_1_A) | INT_CONFIG_BIT(GPIO_INT_1_B);
	HWREG(INTC_BASE + INTC_MIR_CLEAR2) |= INT_CONFIG_BIT(TINT7);
	HWREG(INTC_BASE + INTC_MIR_CLEAR1) |= INT_CONFIG_BIT(GPIO_INT_2_A) | INT_CONFIG_BIT(GPIO_INT_2_B);
}


void butConfig ( ){
    HWREG(SOC_CONTROL_REGS + CONF_GPMC_BEN_1) |= GPIO_FUNC + PAD_PULLUP_PULLDOWN_EN + PAD_INPUT_VALUE_EN;
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_A0)   |= GPIO_FUNC + PAD_PULLUP_PULLDOWN_EN + PAD_INPUT_VALUE_EN;
	HWREG(SOC_CONTROL_REGS + CONF_LCD_VSYNC) |= GPIO_FUNC + PAD_PULLUP_PULLDOWN_EN + PAD_INPUT_VALUE_EN;
	HWREG(SOC_CONTROL_REGS + CONF_LCD_PCLK)  |= GPIO_FUNC + PAD_PULLUP_PULLDOWN_EN + PAD_INPUT_VALUE_EN;

	HWREG(SOC_GPIO_1_REGS + GPIO_OE) |= (1<<16) | (1<<28);
	HWREG(SOC_GPIO_2_REGS + GPIO_OE) |= (1<<22) | (1<<24);

	/* Enabling IRQ generation on these GPIO pins. */
	HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) |= 1<<16;
	HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_1) |= 1<<28;
	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET_0) |= 1<<22;
	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET_1) |= 1<<24;

	/* Debounce enabling */
	HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE) |= (1<<16) | (1<<28);
	HWREG(SOC_GPIO_2_REGS + GPIO_DEBOUNCENABLE) |= (1<<22) | (1<<24);

	/* Enable interrupt generation on detection of a rising edge.*/
	HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= (1<<16) | (1<<28);
	HWREG(SOC_GPIO_2_REGS + GPIO_RISINGDETECT) |= (1<<22) | (1<<24);	
}/* -----  end of function butConfig  ----- */


void ledConfig ( ){
   /* Configure pin mux for output GPIO */
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD2) |= GPIO_FUNC;
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD3) |= GPIO_FUNC;
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD6) |= GPIO_FUNC;
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD7) |= GPIO_FUNC;

	/* clear pins 2, 3, 6 and 7 for output */
	HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7);
	/* clear bit field that will be used */
	HWREG(SOC_GPIO_1_REGS + GPIO_DATAOUT) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7);

}/* -----  end of function ledConfig  ----- */


void gpioIsrHandler(int btn){

    /* Clear the status of the interrupt flags */
	switch(btn){
		case 1:
			HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_0) |= 1<<16; 
			flag_btn_1 = !(flag_btn_1) ;
			break;
		case 2:
			HWREG(SOC_GPIO_1_REGS+GPIO_IRQSTATUS_1) |= 1<<28; 
			flag_btn_2 = !(flag_btn_2) ;
			break;
		case 3:
			HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_0) |= 1<<22; 
			flag_btn_3 = !(flag_btn_3) ;
			break;
		case 4:
			HWREG(SOC_GPIO_2_REGS+GPIO_IRQSTATUS_1) |= 1<<24; 
			flag_btn_4 = !(flag_btn_4) ;
			break;
	}

}


void ISR_Handler(void){
	/* Verifica se é interrupção do DMTIMER7 */
	unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 95)
		timerIrqHandler();
	
	if(irq_number == GPIO_INT_1_A){
		putString("button 1 pressed!\n\r",19);
		gpioIsrHandler(1);
	}

	if(irq_number == GPIO_INT_1_B){
		putString("button 2 pressed!\n\r",19);
		gpioIsrHandler(2);
	}

	if(irq_number == GPIO_INT_2_A){
		putString("button 3 pressed!\n\r",19);
		gpioIsrHandler(3);
	}

	if(irq_number == GPIO_INT_2_B){
		putString("button 4 pressed!\n\r",19);
		gpioIsrHandler(4);
	}
    
	/* Reconhece a IRQ */
	HWREG(INTC_CONTROL) = 0x1;
}


int main(void){
	pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
	
	/* Hardware setup */

	gpioSetup();

	timerSetup();

	butConfig();

	ledConfig();
	//Randomic gerenation setup
	////time_t t;
	//srand((unsigned) time(&t));
	//internBlink(pins,4,TIME);
#if DELAY_USE_INTERRUPT 
	putString("Timer Interrupt: ",17);
#else
	putString("Timer: ",7);
#endif

	while(true){
		//actualPositionMole = (rand()%4)+1;
		//putCh(actualPositionMole+'0');
		//putString(" - Actual position\n\r",20);
		if(flag_btn_2){
			if (flag_btn_1)
			{
				if(TIME!= 25)
				TIME = 25;
				putString("superfast\n\r",11);
				goOnGoOutBlink(SOC_GPIO_1_REGS, ledPins,4,TIME);
			}else{
				putString("fast\n\r",6);
				if(TIME!= 75)
				TIME = 50;
				goOnGoOutBlink(SOC_GPIO_1_REGS,ledPins,4,TIME);
			}

		}else{
			if (flag_btn_1)
			{
				putString("normal\n\r",8);
				if(TIME!= 150)
				TIME = 200;
				goOnGoOutBlink(SOC_GPIO_1_REGS,ledPins,4,TIME);
			}else{
				putString("slow!\n\r",7);
				if(TIME!= 250)
					TIME = 250;
				goOnGoOutBlink(SOC_GPIO_1_REGS,ledPins,4,TIME);
			}
		}
	}

	return(0);
}




