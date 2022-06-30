#ifndef __AUXILIAR_FUNCTIONS_H
    #define __AUXILIAR_FUNCTIONS_H
    #include "bbb_regs.h"
    #include "hw_types.h"

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
    void delay(unsigned int mSec);
    void putCh(char c);
    char getCh();
    int putString(char *str, unsigned int length);
    int getString(char *buf, unsigned int length);
    void ledON(_pinNum);
    void ledOFF(_pinNum);
    int readButton(_btnPinNum);

    void intercalatedBlink(int pin[], int n, unsigned int TIME);
    void sequentialBlink(int pin[], int n, unsigned int TIME);
    void allBlink(int pin[], int n, unsigned int TIME);
    void farEndBlink(int pin[], int n, unsigned int TIME);
    void internBlink(int pin[], int n, unsigned int TIME);

#endif // 	__AUXILIAR_FUNCTIONS_H