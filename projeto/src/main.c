#include "auxiliarFunctions.h"

#define TIME (timeVar)
#define SEED (0xF012CCA5)

int timeVar = 1000;
unsigned int score;
unsigned int countRand, pos, nVetSeq = 63;
const unsigned int vetSeq[] = {1,3,2,4,1,3,2,4,2,
							3,1,3,2,4,1,3,2,4,
							1,3,2,4,1,3,2,1,3,
							2,4,1,3,2,4,2,3,1,
							3,2,4,1,3,2,4,1,3,
							2,4,1,3,2,4,1,3,2,
							2,3,3,1,4,4,2,1,3}; 

static int running = 1;
static int actualPositionMole = role1;

unsigned int randNumGen(){
	int pos = ((SEED >> 2) ^ (SEED >> 7) ^ (SEED >> 13) ^ (SEED >> 22) ) & countRand;
	return (((SEED >> 1) | (pos >> 15)))%4;
}

void timerSetup(void){
	HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) |= MODULEMODE_ENABLE;

	while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) & 0x3) != MODULEMODE_ENABLE);


#if DELAY_USE_INTERRUPT
	/* Interrupt mask */
	HWREG(INTC_BASE + INTC_MIR_CLEAR2) |= INT_CONFIG_BIT(TINT7);
#endif
}


//Configurado com os novos registadores
void gpioSetup(){
  /* Set clock for GPIO1 and GPIO2 */
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1) |= OPTFCLKEN_GPIO_GDBCLK_FCLK_EN + MODULEMODE_ENABLE;
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO2) |= OPTFCLKEN_GPIO_GDBCLK_FCLK_EN + MODULEMODE_ENABLE;

	/* Interrupt mask */
	HWREG(INTC_BASE + INTC_MIR_CLEAR3) |= INT_CONFIG_BIT(GPIO_INT_1_A) | INT_CONFIG_BIT(GPIO_INT_1_B);
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
	HWREG(SOC_CONTROL_REGS + CONF_GPMC_AD14) |= GPIO_FUNC;


	/* clear pins 2, 3, 6 and 7 for output */
	HWREG(SOC_GPIO_1_REGS + GPIO_OE) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7) & ~(1<<14);
	/* clear bit field that will be used */
	HWREG(SOC_GPIO_1_REGS + GPIO_DATAOUT) &= ~(1<<2) & ~(1<<3) & ~(1<<6) & ~(1<<7) & ~(1<<14);

}/* -----  end of function ledConfig  ----- */

void rtcSetup(){
	HWREG(SOC_CM_PER_REGS+CM_RTC_CLKSTCTRL) = 0x2;	
	HWREG(SOC_CM_PER_REGS+CM_RTC_RTC_CLKCTRL) = 0x2;
	
	HWREG(RTC_BASE+KICK0R) = 0x83E70B13;	
	HWREG(RTC_BASE+KICK1R) = 0x95A4F1E0;

	HWREG(RTC_BASE+0x054) = 0x48;

	HWREG(RTC_BASE+0x40) = 0x1;


		
}

void strikeChecker(unsigned int gpio, unsigned int irqStatus, pinNum pin, molePosition role){
	if (actualPositionMole == roleStop && role == role1){
		countRand += 7;
		actualPositionMole = (countRand%4)+1;
		gameStartPrint();
		score = 0;
		HWREG(gpio+irqStatus) |= 1<<pin;
		return;
	}
	
	if (actualPositionMole == roleStop){
		HWREG(gpio+irqStatus) |= 1<<pin;
		return;
	}
	

	if (actualPositionMole == role){// success strike
		score++;
		if(score == 50){ // win
			pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
			setLedsOFF(SOC_GPIO_1_REGS,ledPins,4);
			winStrikePrint(SOC_GPIO_1_REGS,ledPins,4,PIN14,500,score);
			TIME = 1000;
			actualPositionMole = roleStop;
			HWREG(gpio+irqStatus) |= 1<<pin;
			return;
		}

		successStrikePrint(SOC_GPIO_1_REGS,PIN14,score);
		if(TIME > 500){
			TIME -= 25;
		}else if(TIME > 250){
			TIME -= 20;
		}else if (TIME>200){
			TIME -= 10;
		}
	}else{ // game over
		pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
		setLedsOFF(SOC_GPIO_1_REGS,ledPins,4);
		failStrikePrint(SOC_GPIO_1_REGS,ledPins,2,score, PIN14);
		TIME = 1000;
		actualPositionMole = roleStop;
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
	//	pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
	/* Verifica se é interrupção do DMTIMER7 */
	unsigned int irq_number = HWREG(INTC_BASE+INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == TINT7)
		timerIrqHandler();
	
	if(irq_number == GPIO_INT_1_A){
		//putString("button 1 pressed!\n\r",19);
		gpioIsrHandler(1);
	}

	if(irq_number == GPIO_INT_1_B){
		//putString("button 2 pressed!\n\r",19);
		gpioIsrHandler(2);
	}

	if(irq_number == GPIO_INT_2_A){
		//putString("button 3 pressed!\n\r",19);
		gpioIsrHandler(3);
	}

	if(irq_number == GPIO_INT_2_B){
		//putString("button 4 pressed!\n\r",19);
		gpioIsrHandler(4);
	}
    
	/* Reconhece a IRQ */
	HWREG(INTC_BASE+INTC_CONTROL) = 0x1;
}


int main(void){
	pinNum ledPins[] = {PIN2,PIN3,PIN6,PIN7};
	score = 0;
	countRand = 0;
	running = 1;
	pos = 0;
	/* Hardware setup */
	gpioSetup();
	timerSetup();
	butConfig();
	ledConfig();

	internBlink(SOC_GPIO_1_REGS,ledPins,4,125);
	internBlink(SOC_GPIO_1_REGS,ledPins,4,125);
	countRand = SEED << 21;
	
	gameStartPrint();
	
	while(true){

		if (actualPositionMole != roleStop){
			actualPositionMole = vetSeq[pos];
			setLedsOFF(SOC_GPIO_1_REGS,ledPins,4);
		}
		switch (actualPositionMole){
			case role1:
				pinON(SOC_GPIO_1_REGS,ledPins[0]);
				break;
			
			case role2:
				pinON(SOC_GPIO_1_REGS,ledPins[1]);
				break;
			
			case role3:
				pinON(SOC_GPIO_1_REGS,ledPins[2]);
				break;
			
			case role4:
				pinON(SOC_GPIO_1_REGS,ledPins[3]);
				break;
		}
		delay(TIME);
		pos = (pos+1)%63;
		
	}

	return(0);
}
