#ifndef ADDRESS_REGS_H
#define ADDRESS_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/*                Memory mapped registers base address                */
#define SOC_GPIO_1_REGS										(0x4804C000)
#define SOC_GPIO_2_REGS										(0x481AC000)
#define SOC_WDT_0_REGS										(0x44E33000)
#define SOC_UART_0_REGS										(0x44E09000)
#define SOC_DMTIMER_7_REGS									(0x4804A000)
#define INTC_BASE											(0x48200000)
#define CM_PER_BASE                                         (0x44E00000)

/*                       GPIO register offsets                        */
#define CM_PER_GPIO1_CLKCTRL_REGS							(0x000000AC)
#define CM_PER_GPIO2_CLKCTRL_REGS							(0x000000B0)
#define GPIO_IRQSTATUS_0_REGS								(0x0000002C)
#define GPIO_IRQSTATUS_1_REGS								(0x00000030)
#define GPIO_IRQSTATUS_SET_0_REGS							(0x00000034)
#define GPIO_IRQSTATUS_SET_1_REGS							(0x00000038)
#define GPIO_IRQSTATUS_CLR_0_REGS							(0x0000003C)
#define GPIO_IRQSTATUS_CLR_1_REGS							(0x00000040)
#define GPIO_OE_REGS										(0x00000134)
#define GPIO_DATAIN_REGS									(0x00000138)
#define GPIO_DATAOUT_REGS									(0x0000013C)
#define GPIO_RISINGDETECT_REGS								(0x00000148)
#define GPIO_DEBOUNCENABLE									(0x00000150)

/*                          Timer registers                           */
#define CM_PER_TIMER7_CLKCTRL								(0x0000007C)
#define DMTIMER_TCRR										(0x0000003C)
#define DMTIMER_IRQSTATUS									(0x00000028)
#define DMTIMER_IRQENABLE_SET								(0x0000002C)
#define DMTIMER_IRQENABLE_CLR								(0x00000030)
#define DMTIMER_TCLR										(0x00000038)
#define DMTIMER_TSICR										(0x00000054)
#define DMTIMER_TWPS										(0x00000048)

/*                    Interrupt registers offsets                     */
#define INTC_MIR_CLEAR1										(0x000000A8)
#define INTC_MIR_CLEAR2										(0x000000C8)
#define INTC_MIR_CLEAR3										(0x000000E8)

/*                   Watch dog registers offsets                      */
#define WDT_WWPS											(0x00000034)
#define WDT_WSPR											(0x00000048)

/*                       UART registers offsets                       */
#define UART_RHR											(0x00000000)
#define UART_THR											(0x00000000)
#define UART_LSR											(0x00000014)

/*                            Constants                               */
#define MODULEMODE_ENABLE									(0x00000002)
#define OPTFCLKEN_GPIO_1_GDBCLK_FCLK_EN						(0x00040000)
#define TIMER_1MS_COUNT										(0x00005DC0)
#define TIMER_OVERFLOW										(0xFFFFFFFF)

#ifdef __cplusplus
}
#endif /* extern C */

#endif /* ADDRESS_REGS_H */
