/*****************************************************************************
* bsp.h for Lab2A of ECE 153a at UCSB
* Date of the Last Update:  October 23,2014
*****************************************************************************/
#ifndef bsp_h
#define bsp_h


                                              


/* bsp functions ..........................................................*/

void BSP_init(void);
void ISR_gpio(void);
void ISR_timer(void);

#define BSP_showState(prio_, state_) ((void)0)

#define ENCODER_INTERRUPT XGPIO_IR_MASK

extern int prevstate;


#endif                                                             /* bsp_h */


