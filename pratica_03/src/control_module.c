/*
 * =====================================================================================
 *
 *       Filename:  control_module.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/02/2017 19:43:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "control_module.h"
#include "soc_AM335x.h"
#include "hw_types.h" 

void cmSetCtrlModule(CONTROL_MODULE module, unsigned int value){
   	HWREG(SOC_CONTROL_REGS + module) |= value;
}

unsigned int cmGetCtrlModule(CONTROL_MODULE module){
   	return(HWREG(SOC_CONTROL_REGS + module));
}

