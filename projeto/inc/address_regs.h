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
#define SOC_CONTROL_REGS									(0x44E10000)
#define SOC_CM_PER_REGS										(0x44E00000)

/*                       GPIO register offsets                        */
#define CM_PER_GPIO1							            (0x000000AC)
#define CM_PER_GPIO2							            (0x000000B0)
#define GPIO_IRQSTATUS_0								    (0x0000002C)
#define GPIO_IRQSTATUS_1								    (0x00000030)
#define GPIO_IRQSTATUS_SET_0							    (0x00000034)
#define GPIO_IRQSTATUS_SET_1							    (0x00000038)
#define GPIO_IRQSTATUS_CLR_0							    (0x0000003C)
#define GPIO_IRQSTATUS_CLR_1							    (0x00000040)
#define GPIO_OE										        (0x00000134)
#define GPIO_DATAIN									        (0x00000138)
#define GPIO_DATAOUT									    (0x0000013C)
#define GPIO_RISINGDETECT								    (0x00000148)
#define GPIO_DEBOUNCENABLE									(0x00000150)

/*                       Control module GPIO registers                */
//buttons gpio1
#define CONF_GPMC_BEN_1							            (0x00000878)
#define CONF_GPMC_A0					    			    (0x00000840)
//buttons gpio2
#define CONF_LCD_VSYNC							            (0x000008E0)
#define CONF_LCD_PCLK							            (0x000008E8)
//buzzer gpio1
#define CONF_GPMC_AD14								        (0x00000838) // EHRPWM2A
//leds gpio1
#define CONF_GPMC_AD2								        (0x00000808)
#define CONF_GPMC_AD3								        (0x0000080C)
#define CONF_GPMC_AD6								        (0x00000818)
#define CONF_GPMC_AD7								        (0x0000081C)

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
#define INTC_BASE											(0x48200000)
#define INTC_MIR_CLEAR1										(0x000000A8)
#define INTC_MIR_CLEAR2										(0x000000C8)
#define INTC_MIR_CLEAR3										(0x000000E8)
#define INTC_CONTROL    						            (0x00000048)
#define INTC_SIR_IRQ    						            (0x00000040)

/*                    	  Interrupt acronyns		                  */
#define GPIO_INT_1_A    						            (0x00000062)
#define GPIO_INT_1_B    						            (0x00000063)
#define GPIO_INT_2_A    						            (0x00000020)
#define GPIO_INT_2_B    						            (0x00000021)
#define TINT7		    						            (0x0000005F)

/*                   Watch dog registers offsets                      */
#define WDT_WWPS											(0x00000034)
#define WDT_WSPR											(0x00000048)

/*                       UART registers offsets                       */
#define UART0_BASE 								            (0x44E09000)
#define UART_RHR											(0x00000000)
#define UART_THR											(0x00000000)
#define UART_LSR											(0x00000014)

/*                        Pin module config                           */
#define GPIO_FUNC											(0x00000007)
#define PAD_PULLUP_PULLDOWN_EN								(0x00000008)
#define PAD_INPUT_VALUE_EN									(0x00000020)

/*                       Clock module config                          */
#define MODULEMODE_ENABLE									(0x00000002)
#define OPTFCLKEN_GPIO_GDBCLK_FCLK_EN						(0x00040000)

/*                         Timer constants                            */

#define CM_RTC_RTC_CLKCTRL                                  (0x00000800)
#define CM_RTC_CLKSTCTRL                                    (0x00000804)

#define RTC_BASE                                            (0x44E3E000)
#define KICK0R                                              (0x0000006C)
#define KICK1R                                              (0x00000070)
#define SECONDS_REG                                         (0x00000000)
#define TIMER_1MS_COUNT										(0x00005DC0)
#define TIMER_OVERFLOW										(0xFFFFFFFF)

#ifdef __cplusplus
}
#endif /* extern C */

#endif /* ADDRESS_REGS_H */
