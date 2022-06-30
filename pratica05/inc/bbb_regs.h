#ifndef _BBB_REGS_H_
#define _BBB_REGS_H_

/*
 * =====================================================================================
 *
 *       Filename:  bb_regs
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/05/2018 17:47:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */




/* Interrupt */
#define INTC_BASE       						0x48200000
#define INTC_SIR_IRQ    						0x48200040
#define INTC_CONTROL    						0x48200048
#define INTC_ILR        						0x48200100
#define INTC_MIR_CLEAR2 						0x482000C8
#define INTC_SYSCONFIG							0x48200010
#define INTC_SYSSTATUS							0x48200014
#define INTC_THRESHOLD							0x48200068
	
/* UART0 */
#define UART0_BASE 								0x44E09000
#define UART0_RHR  								0x44E09000
#define UART0_THR  								0x44E09000
#define UART0_LSR  								0x44E09014

/* Watch Dog Timer */
#define  WDT_BASE 								0x44E35000
#define  WDT_WSPR 								0x44E35048
#define  WDT_WWPS 								0x44E35034

/* Clock */
#define CM_PER_GPIO1_CLKCTRL 					0x44E000AC
#define CM_PER_RTC_RTC_CLKCTRL   				0x44E00800
#define CM_PER_RTC_CLKSTCTRL     				0x44E00804
#define CM_PER_TIMER7_CLKCTRL					0x44E0007C
#define SOC_CM_DPLL_CLKSEL_TIMER7_CLK          	0x44E00504

/* CM_PER_GMPCA6 */
#define CM_PER_GMPCA6_REGS                      0x44E10818

/* GPIO */
#define GPIO1_OE            					0x4804C134
#define GPIO1_SETDATAOUT   				 		0x4804C194
#define GPIO1_CLEARDATAOUT  					0x4804C190


/* The Input clock is selected as 24MHz. So for 1ms set the count to 0x5DC0. 
 *If the input clock is changed to different source this value has to be updated 
 *accordingly.	
*/
#define TIMER_1MS_COUNT                 		0x5DC0u
#define TIMER_OVERFLOW                  		0xFFFFFFFFu


/* DMTIMER */
#define SOC_DMTIMER_7_REGS                   	0x4804A000
#define DMTIMER_TIDR   							0x4804A000
#define DMTIMER_TIOCP_CFG   					0x4804A010
#define DMTIMER_IRQ_EOI   						0x4804A020
#define DMTIMER_IRQSTATUS_RAW   				0x4804A024
#define DMTIMER_IRQSTATUS   					0x4804A028
#define DMTIMER_IRQENABLE_SET   				0x4804A02C
#define DMTIMER_IRQENABLE_CLR   				0x4804A030
#define DMTIMER_IRQWAKEEN  	 					0x4804A034
#define DMTIMER_TCLR   							0x4804A038
#define DMTIMER_TCRR   							0x4804A03C
#define DMTIMER_TLDR   							0x4804A040
#define DMTIMER_TTGR   							0x4804A044
#define DMTIMER_TWPS   							0x4804A048
#define DMTIMER_TMAR   							0x4804A04C
#define DMTIMER_TCAR(n)   						(0x50 + (((n) - 1) * 8))
#define DMTIMER_TSICR  		 					0x4804A054



/* RTC */
#define RTC_BASE           						0x44E3E000
#define SECONDS_REG        						0x44E3E000
#define MINUTES_REG        						0x44E3E004
#define HOURS_REG          						0x44E3E008
#define RTC_CTRL_REG       						0x44E3E040
#define RTC_STATUS_REG     						0x44E3E044
#define RTC_INTERRUPTS_REG 						0x44E3E048
#define RTC_OSC_REG        						0x44E3E054
#define KICK0R             						0x44E3E06C
#define KICK1R             						0x44E3E070


#endif //__BB_REGS_H__

