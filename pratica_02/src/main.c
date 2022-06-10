		/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include	"hw_types.h"
#include	"soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME									1000000
#define TOGGLE          							(0x01u)

#define HIGH									1
#define LOW                                                                  0

#define CM_PER_GPIO1								(0xAC)
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			(0x00040000u)

#define CM_conf_gpmc_ben1      	 					(0x0878)
#define CM_conf_gpmc_a5         						(0x0854)
#define CM_conf_gpmc_a6                                                      (0x0858)
#define CM_conf_gpmc_a7                                                      (0x085C)
#define CM_conf_gpmc_a8                                                      (0x0860)
//#define CM_conf_gpmc_a9                                                      (0x0864)

#define GPIO_OE                 						(0x134)
#define GPIO_DATAIN                                                          (0x190)
#define GPIO_CLEARDATAOUT       						(0x190)
#define GPIO_SETDATAOUT         						(0x194)
#define GPIO_PIN_MODE                                                        (0x07u)

/* bits  */
#define LED_INTERNO_01                                                       (1<<21)
#define LED_INTERNO_02                                                       (1<<22)
#define LED_INTERNO_03                                                       (1<<23)
#define LED_INTERNO_04                                                       (1<<24)
#define BUTTON                                                               (1<<28)


unsigned int flagBlink;
unsigned int HIGH_LEVEL;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void ledInit();
//static void ledToggle();
static void led_seq_1();
static void led_seq_2();


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(void){

	flagBlink=0;	//init flag
	HIGH_LEVEL = 0;  //init high_level
  	
	/* Configure the green LED control pin. */
  	ledInit();
  
  	while (1){
    	if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<28)) && !HIGH_LEVEL) 
    		HIGH_LEVEL = HIGH;
    	else if((HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<28)) && HIGH_LEVEL) 
    		HIGH_LEVEL = HIGH;
    		
    	if(HIGH_LEVEL)
    		led_seq_1();
    	else
    		led_seq_2();
	}

	return(0);
} /* ----------  end of function main  ---------- */


/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */
void ledInit( ){
	
	unsigned int val_temp; 	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
	/*
	   (4804C000 + 000000AC) |= 00000002 | 00040000 
	   (4804C000 + 000000AC) = 01001000000001001100000010101100 = 4804C0AC
	   (00000002 | 00040000) = 00000000000001000000000000000010 = 00040002
	   4804C0AC |= 00040002  = 01001000000001001100000010101110 = 4804C0AE
	*/
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
	 
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_ben1) |= 7;
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5)   |= 7;
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6)   |= 7;
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7)   |= 7;
   	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8)   |= 7;
   	
 
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/ 
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
	/*configurando leds como entrada*/
	// val_temp &= ~(LED_EXT);
	val_temp &= ~(LED_INTERNO_01);
	val_temp &= ~(LED_INTERNO_02);
	val_temp &= ~(LED_INTERNO_03);
	val_temp &= ~(LED_INTERNO_04);
	
	/* configurando o butão como entrada */
	HWREG(SOC_GPIO_1_REGS+GPIO_OE) |= (BUTTON);
		
}/* -----  end of function ledInit  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:  
 * =====================================================================================
 */
 /*
void ledToggle( ){
		
		flagBlink ^= TOGGLE;

		if(flagBlink) {
			// HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (LED_EXT);
			
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = (LED_INTERNO_04);
		}
		else {
			// HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (LED_EXT);
			
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = (LED_INTERNO_04);
		}

*/

void led_seq_1() {
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_01);
                       HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_04);
                       delay();
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_04);
			delay();
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_03);
			delay();
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_04);
			delay();
}

void led_seq_2() {
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_01);
			delay();
			
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_01);
			delay();
			
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_01);
			delay();
			
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_04);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) |= (LED_INTERNO_01);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_04);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_03);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_02);
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) |= (LED_INTERNO_01);
			delay();
			
}










