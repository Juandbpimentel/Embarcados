/*
 * =====================================================================================
 *
 *       Filename:  start.s
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

_start:
   mrs r0, cpsr
   bic r0, r0, #0x1F @ clear mode bits
   orr r0, r0, #0x13 @ set SVC mode
   orr r0, r0, #0xC0 @ disable FIQ and IRQ
   msr cpsr, r0

   mrc p15,0,r0,c1,c0,2    ;@ read cp access register
   orr r0,r0,#0x00F00000   ;@ enable full access to neon/vfp (coproc 10&11)
   mcr p15,0,r0,c1,c0,2    ;@ write cp access register
   isb                     ;@ instruction synchronization barrier
   mov r0,#0x40000000      ;@ switch on vfp & neon
   vmsr fpexc,r0           ;@ set EN bit in fpexc

   ldr sp, =0x4030CDFC  @6kB public stack  TMR 26.1.3.2

   bl main


.loop: b .loop

