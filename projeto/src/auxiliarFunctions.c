#include "auxiliarFunctions.h"

#ifndef _FLAG_TIMERS
        #define _FLAG_TIMERS
        static bool flag_timers;
    #endif

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


void intercalatedBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 2;
    // leds on
    ////ledON(pinAD15);
    ledON(gpio,pins[0]);
    ledON(gpio,pins[2]);
    delay(TIME);
    ////ledOFF(pinAD15);
    ledON(gpio,pins[1]);
    ledON(gpio,pins[3]);
    delay(TIME);

    // leds off
    ////ledOFF(pinAD15);
    ledOFF(gpio,pins[0]);
    ledOFF(gpio,pins[2]);
    delay(TIME);
    ////ledOFF(pinAD15);
    ledOFF(gpio,pins[1]);
    ledOFF(gpio,pins[3]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void sequentialBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 4;
    // leds on
    // ledON(pinAD15);
    ledON(gpio,pins[0]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledON(gpio,pins[1]);
    delay(TIME);

    // ledON(pinAD15);
    ledON(gpio,pins[2]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledON(gpio,pins[3]);
    delay(TIME);

    // leds off
    // ledON(pinAD15);
    ledOFF(gpio,pins[3]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledOFF(gpio,pins[2]);
    delay(TIME);

    // ledON(pinAD15);
    ledOFF(gpio,pins[1]);
    delay(TIME);

    // ledOFF(pinAD15);
    ledOFF(gpio,pins[0]);
    delay(TIME);
    // led(GPIO1,pinExtern);
}
void allBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    // led(GPIO1,pinExtern);
    // delay();
    // ledON(pinAD15);
    for (int i = 0; i < n; i++)
    {
        ledON(gpio,pins[i]);
    }

    delay(TIME);

    for (int i = n - 1; i >= 0; i--)
    {
        ledOFF(gpio,pins[i]);
    }
    // ledOFF(pinAD15);
    delay(TIME);
    // led(GPIO1,pinExtern);
}

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

unsigned int readBut (unsigned int gpio,btnPinNum pin){
	unsigned int temp;
	temp = HWREG(gpio+GPIO_DATAIN)&1<<pin;
	
	
	
	return(temp);
}/* -----  end of function readBut  ----- */


void ledOFF(unsigned int gpio,pinNum pin){
	HWREG(gpio+GPIO_DATAOUT) &= ~(1<<pin);

}


void ledON(unsigned int gpio,pinNum pin){

    HWREG(gpio+GPIO_DATAOUT) |= (1<<pin);

}

void farEndBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    TIME /= 2;
    ledON(gpio,pins[0]);
    ledON(gpio,pins[3]);
    delay(TIME);
    ledOFF(gpio,pins[0]);
    ledOFF(gpio,pins[3]);
    delay(TIME);
    ledON(gpio,pins[0]);
    ledON(gpio,pins[3]);
    delay(TIME);
    ledOFF(gpio,pins[0]);
    ledOFF(gpio,pins[3]);
    delay(TIME);
}

void internBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    ledON(gpio,pins[1]);
    ledON(gpio,pins[2]);
    delay(TIME);
    ledOFF(gpio,pins[1]);
    ledOFF(gpio,pins[2]);
    delay(TIME);
    ledON(gpio,pins[1]);
    ledON(gpio,pins[2]);
    delay(TIME);
    ledOFF(gpio,pins[1]);
    ledOFF(gpio,pins[2]);
    delay(TIME);
}

void goOnGoOutBlink(unsigned int gpio,pinNum pins[], int n, unsigned int TIME)
{
    for (int i = 0; i < n; i++){
        delay(TIME);
        ledON(gpio,pins[i]);
    }
    for (int i = 0; i < n; i++){
        delay(TIME);
        ledOFF(gpio,pins[i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        delay(TIME);
        ledON(gpio,pins[i]);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        delay(TIME);
        ledOFF(gpio,pins[i]);
    }
}

void setLedsOFF(unsigned int gpio,pinNum pins[], int n){
    for (int i = 0; i < n; i++){
		ledOFF(gpio,pins[i]);
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
#if DELAY_USE_INTERRUPT
    unsigned int countVal = TIMER_OVERFLOW - (mSec * TIMER_1MS_COUNT);

   	/* Wait for previous write to complete */
	DMTimerWaitForWrite(0x2);

    /* Load the register with the re-load value */
	HWREG(DMTIMER_TCRR) = countVal;
	
	flag_timers = false;

    /* Enable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_SET) = 0x2; 

    /* Start the DMTimer */
	timerEnable();

    while(flag_timers == false);

    /* Disable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_CLR) = 0x2; 
#else
    while(mSec != 0){
        /* Wait for previous write to complete */
        DMTimerWaitForWrite(0x2);

        /* Set the counter value. */
        HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TCRR) = 0x0;

        timerEnable();

        while(HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TCRR) < TIMER_1MS_COUNT);

        /* Stop the timer */
        HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TCLR) &= ~(0x00000001u);

        mSec--;
    }
#endif
}
void timerIrqHandler(void){

    /* Clear the status of the interrupt flags */
	HWREG(SOC_DMTIMER_7_REGS+DMTIMER_IRQSTATUS) = 0x2; 

	flag_timers = true;

    /* Stop the DMTimer */
	timerDisable();

}

void clearScreen()
{
  char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  putString(CLEAR_SCREEN_ANSI,12);
}

void failStrikePrint(unsigned int gpio,pinNum pins[],int n,int score){
    
    clearScreen();
    putString("\n\r\n\r\n\r",6);
    putString("  _______                             _________          ______                 _________   ________     |     \n\r",119);
    putString(" /       \\       ^      |\\        /| |                  /      \\  \\          / |           |        \\    |     \n\r",119);
    putString(" |       |      / \\     | \\      / | |                 |        |  \\        /  |           |         |   |     \n\r",119);
    putString(" |             /   \\    |  \\    /  | |_________        |        |   \\      /   |_________  |________/    |     \n\r",119);
    putString(" |    _____   /_____\\   |   \\  /   | |                 |        |    \\    /    |           |      \\      |     \n\r",119);
    putString(" |       |   /       \\  |    \\/    | |                 |        |     \\  /     |           |       \\           \n\r",119);
    putString(" \\_______/  /         \\ |          | |_________         \\______/       \\/      |_________  |        \\    o     \n\r",119);
    putString("\n\r\n\r\n\r",6);
    putString("--------------------------  Your Final Score is: ",49);
    
    int aux = (score/10);
    putCH(aux+'0');

    aux = (score%10);
    putCH(aux+'0');
    putString("  --------------------------\n\r\n\r\n\r",34);
    putString("----------------------  PRESS THE BUTTON 1 FOR CONTINUE OR BUTTON 2 FOR END THE GAME  ----------------------\n\r",110);
    
    ledON(SOC_GPIO_1_REGS,pins[0]);
    ledON(SOC_GPIO_1_REGS,pins[n-1]);
}




void gameStartPrint(){
    clearScreen();
    putString("                ___________      ___________             _________                     ______                _________  \n\r",122);
    putString(" |        |  o       |                |      |        | |               |\\        /|  /      \\  |           |           \n\r",122);
    putString(" |        |          |                |      |        | |               | \\      / | |        | |           |           \n\r",122);
    putString(" |________|  |       |                |      |________| |_________      |  \\    /  | |        | |           |_________  \n\r",122);
    putString(" |        |  |       |                |      |        | |               |   \\  /   | |        | |           |           \n\r",122);
    putString(" |        |  |       |                |      |        | |               |    \\/    | |        | |           |           \n\r",122);
    putString(" |        |  |       |                |      |        | |_________      |          |  \\______/  |__________ |_________  \n\r",122);
}




void successStrikePrint(unsigned int gpio,pinNum buzzer,int score){
    clearScreen();
    putString("  | | |   ______   ___________   ________                    _________  | | |  \n\r",81);
    putString("  | | |  /      \\       |       |        \\    o   |      /  |           | | |  \n\r",81);
    putString("  | | |  |              |       |         |       |    /    |           | | |  \n\r",81);
    putString("  | | |  \\______        |       |________/    |   |  /      |_________  | | |  \n\r",81);
    putString("  | | |         \\       |       |      \\      |   |  \\      |           | | |  \n\r",81);
    putString("                |       |       |       \\     |   |    \\    |                  \n\r",81);
    putString("  o o o   ______/       |       |        \\    |   |      \\  |_________  o o o  \n\r",81);

    putString("\n\r\n\r\n\r",6);

    putString("--------------------------  Your Score is now: ",47);
    
    int aux = (score/10);
    putCH(aux+'0');

    aux = (score%10);
    putCH(aux+'0');
    putString("  --------------------------\n\r\n\r\n\r",34);
    
    ledON(SOC_GPIO_1_REGS,buzzer);
    delay(100);
    ledOFF(SOC_GPIO_1_REGS,buzzer);   
}

void winStrikePrint(unsigned int gpio,pinNum pins[], int n, pinNum buzzer, unsigned int TIME,int score){
    clearScreen();

    putString("  | | | | | |                  ______                                                              | | | | | |   \n\r",115);
    putString("  | | | | | |   \\         /   /      \\  |          |        \\                  /  o |\\          |  | | | | | |   \n\r",115);
    putString("  | | | | | |     \\     /    |        | |          |         \\                /     |  \\        |  | | | | | |   \n\r",115);
    putString("  | | | | | |       \\ /      |        | |          |          \\      /\\      /    | |    \\      |  | | | | | |   \n\r",115);
    putString("  | | | | | |        |       |        | |          |           \\    /  \\    /     | |      \\    |  | | | | | |   \n\r",115);
    putString("                     |       |        | |          |            \\  /    \\  /      | |        \\  |                \n\r",115);
    putString("  o o o o o o        |        \\______/   \\________/              \\/      \\/       | |          \\|  o o o o o o   \n\r",115);
    
    
    putString("\n\r\n\r\n\r",6);
    putString("--------------------------  Your Final Score is: ",49);
    
    int aux = (score/10);
    putCH(aux+'0');

    aux = (score%10);
    putCH(aux+'0');
    putString("  --------------------------\n\r\n\r\n\r",34);
    
    
    
    ledON(gpio,buzzer);
    allBlink(gpio,pins,n,TIME/4);
    ledOFF(gpio,buzzer);

    ledON(gpio,buzzer);
    allBlink(gpio,pins,n,TIME/4);
    ledOFF(gpio,buzzer);
    
    ledON(gpio,buzzer);
    allBlink(gpio,pins,n,TIME/4);
    ledOFF(gpio,buzzer);
    
    ledON(gpio,buzzer);
    allBlink(gpio,pins,n,TIME/4);
    ledOFF(gpio,buzzer);

    putString("----------------------  PRESS THE BUTTON 1 FOR CONTINUE OR BUTTON 2 FOR END THE GAME  ----------------------\n\r",110);
    ledON(SOC_GPIO_1_REGS,pins[0]);
    ledON(SOC_GPIO_1_REGS,pins[n-1]);
}