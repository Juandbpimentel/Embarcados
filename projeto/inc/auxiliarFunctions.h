#ifndef __AUXILIAR_FUNCTIONS_H
    #define __AUXILIAR_FUNCTIONS_H
    #include "timers.h"
    
//enum macros
    typedef enum _pinNum{
        PIN0,  PIN1,  PIN2,  PIN3,  PIN4,  PIN5,  PIN6,  PIN7,
        PIN8,  PIN9, PIN10, PIN11, PIN12, PIN13, PIN14, PIN15,
        PIN16, PIN17, PIN18, PIN19, PIN20, PIN21, PIN22, PIN23,
        PIN24, PIN25, PIN26, PIN27, PIN28, PIN29, PIN30, PIN31,
    }pinNum;

    typedef enum _btnPinNum{
        BTN_PIN0,  BTN_PIN1,  BTN_PIN2,  BTN_PIN3,  BTN_PIN4,  BTN_PIN5,  BTN_PIN6,  BTN_PIN7,
        BTN_PIN8,  BTN_PIN9, BTN_PIN10, BTN_PIN11, BTN_PIN12, BTN_PIN13, BTN_PIN14, BTN_PIN15,
        BTN_PIN16, BTN_PIN17, BTN_PIN18, BTN_PIN19, BTN_PIN20, BTN_PIN21, BTN_PIN22, BTN_PIN23,
        BTN_PIN24, BTN_PIN25, BTN_PIN26, BTN_PIN27, BTN_PIN28, BTN_PIN29, BTN_PIN30, BTN_PIN31,
    }btnPinNum;

    typedef enum _molePosition{
        role1=1,role2,role3,role4
    }molePosition;
    /*                       Functionalities                            */

// operational intern functions
    void disableWdt(void);
    void putCh(char c);
    char getCh();
    int putString(char *str, unsigned int length);
    int getString(char *buf, unsigned int length);
    void ledON(unsigned int gpio,pinNum pin);
    void ledOFF(unsigned int gpio,pinNum pin);
    int readButton(unsigned int gpio,btnPinNum pin);

//blinks functions
    void intercalatedBlink(unsigned int gpio,pinNum pin[], int n, unsigned int TIME);
    void sequentialBlink(unsigned int gpio,pinNum pin[], int n, unsigned int TIME);
    void allBlink(unsigned int gpio,pinNum pin[], int n, unsigned int TIME);
    void farEndBlink(unsigned int gpio,pinNum pin[], int n, unsigned int TIME);
    void internBlink(unsigned int gpio,pinNum pin[], int n, unsigned int TIME);
    void goOnGoOutBlink(unsigned int gpio,pinNum pins[], int n,unsigned int TIME);
    void setLedsOFF(unsigned int gpio,pinNum pins[], int n);

// timer auxiliar functions
    void delay(unsigned int mSec);
    void timerIrqHandler(void);

//interruption auxiliar functions
    #define INT_CONFIG_BIT(irq_num)					(1<<(irq_num & 0x1F))
    void failStrike(unsigned int gpio,pinNum pin);
    void successStrike(unsigned int gpio,pinNum pin);
    void winStrike(unsigned int gpio,pinNum pins[], int n, pinNum buzzer, unsigned int TIME);

#endif // 	__AUXILIAR_FUNCTIONS_H