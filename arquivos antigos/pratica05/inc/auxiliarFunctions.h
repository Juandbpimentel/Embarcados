#ifndef __AUXILIAR_FUNCTIONS_H
    #define __AUXILIAR_FUNCTIONS_H
    #include "timers.h"
    typedef enum _pinNum{
        PIN1=1,
        PIN2,
        PIN3,
        PIN4
    }pinNum;

    typedef enum _btnPinNum{
        btnPIN1=1,
        btnPIN2
    }btnPinNum;

    void disableWdt(void);
    void putCh(char c);
    char getCh();
    int putString(char *str, unsigned int length);
    int getString(char *buf, unsigned int length);
    void ledON(pinNum pin);
    void ledOFF(pinNum pin);
    int readButton(btnPinNum pin);

    void intercalatedBlink(pinNum pin[], int n, unsigned int TIME);
    void sequentialBlink(pinNum pin[], int n, unsigned int TIME);
    void allBlink(pinNum pin[], int n, unsigned int TIME);
    void farEndBlink(pinNum pin[], int n, unsigned int TIME);
    void internBlink(pinNum pin[], int n, unsigned int TIME);
    void goOnGoOutBlink(pinNum pins[], int n,unsigned int TIME);
    void setLedsOFF(pinNum pins[], int n);
    void delay(unsigned int mSec);
    void timerIrqHandler(void);
#endif // 	__AUXILIAR_FUNCTIONS_H