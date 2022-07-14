#include "auxiliarFunctions.h"

#define TIME timeVar

int timeVar = 1000;
int score =   0;
bool running = true;

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
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD8) |= GPIO_FUNC;


	/* clear pins 2, 3, 6 and 7 for output */
	HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7) & ~(1<<8);
	/* clear bit field that will be used */
	HWREG(SOC_GPIO_1_REGS + GPIO_DATAOUT) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7) & ~(1<<8);

}/* -----  end of function ledConfig  ----- */

void strikeChecker(unsigned int gpio, unsigned int irqStatus, pinNum pin, molePosition role){
	if (actualPositionMole == -1 && role == role1){
		actualPositionMole = 1;//substituir por rand()%4 +1
		gameStartPrint();
		HWREG(gpio+irqStatus) |= 1<<pin;
		return;
	}

	if (actualPositionMole == -1 && role == role4){
		running = false;
		HWREG(gpio+irqStatus) |= 1<<pin;
		return;
	}

	if (actualPositionMole == role){
		score++;
		if(score == 70){
			pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
			winStrikePrint(gpio,ledPins,4,PIN8,1000,score);
			TIME = 1000;
			score = 0;
			HWREG(gpio+irqStatus) |= 1<<pin;
			return;
		}

		successStrikePrint(gpio,PIN8,score);
		if (TIME>700){
			TIME -= 30;
		}else if(TIME>250){
			TIME -= 15;
		}else{
			TIME -= 5;
		}
		
	}else{
		pinNum ledPins[] = {PIN2,PIN7};
		failStrikePrint(gpio,ledPins,2,score);
		TIME = 1000;
		score = 0;
		actualPositionMole = -1;
	}
	HWREG(gpio+irqStatus) |= 1<<pin;
}

void gpioIsrHandler(int btn){

    /* Clear the status of the interrupt flags */
	switch(btn){
		case 1:
			strikeChecker(SOC_GPIO_1_REGS,GPIO_IRQSTATUS_0,16,role1);
			break;
		case 2:
			strikeChecker(SOC_GPIO_1_REGS,GPIO_IRQSTATUS_1,28,role2);
			break;
		case 3:
			strikeChecker(SOC_GPIO_2_REGS,GPIO_IRQSTATUS_0,22,role3);
			break;
		case 4:
			strikeChecker(SOC_GPIO_2_REGS,GPIO_IRQSTATUS_1,24,role4);
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

	internBlink(SOC_GPIO_1_REGS,ledPins,4,TIME);
	internBlink(SOC_GPIO_1_REGS,ledPins,4,TIME);
	
	gameStartPrint();
	
	while(running){
		actualPositionMole = 1; // substituir por rand()%4+1 
		setLedsOFF(SOC_GPIO_1_REGS,ledPins,4);
		switch (actualPositionMole)
		{
			case role1:
				ledON(SOC_GPIO_1_REGS,ledPins[0]);
				break;
			
			case role2:
				ledON(SOC_GPIO_1_REGS,ledPins[1]);
				break;
			
			case role3:
				ledON(SOC_GPIO_1_REGS,ledPins[2]);
				break;
			
			case role4:
				ledON(SOC_GPIO_1_REGS,ledPins[3]);
				break;
			
			default:
				break;
		}
		delay(TIME);
	}

	return(0);
}




