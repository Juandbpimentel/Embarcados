#ifndef _TIMERS_H
    #define _TIMERS_H

    #include "hw_types.h"
    #include "address_regs.h"

    #define DELAY_USE_INTERRUPT			0

    /**
     * \brief   This macro will check for write POSTED status
     *
     * \param   reg          Register whose status has to be checked
     *
     *    'reg' can take the following values \n
     *    DMTIMER_WRITE_POST_TCLR - Timer Control register \n
     *    DMTIMER_WRITE_POST_TCRR - Timer Counter register \n
     *    DMTIMER_WRITE_POST_TLDR - Timer Load register \n
     *    DMTIMER_WRITE_POST_TTGR - Timer Trigger register \n
     *    DMTIMER_WRITE_POST_TMAR - Timer Match register \n
     *
     **/

    #define DMTimerWaitForWrite(reg)   \
                if(HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TSICR) & 0x4)\
                while((reg & HWREG(SOC_DMTIMER_7_REGS+DMTIMER_TWPS)));

    void timerEnable();
    void timerDisable();

#endif //TIMER_H