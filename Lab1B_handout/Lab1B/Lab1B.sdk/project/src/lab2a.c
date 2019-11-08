/*****************************************************************************
* lab2a.c for Lab2A of ECE 153a at UCSB
* Date of the Last Update:  October 23,2014
*****************************************************************************/

#define AO_LAB2A

#include "qpn_port.h"
#include "bsp.h"
#include "lab2a.h"




typedef struct Lab2ATag  {               //Lab2A State machine
	QActive super;
}  Lab2A;

/* Setup state machines */
/**********************************************************************/
static QState Lab2A_initial (Lab2A *me);
static QState Lab2A_on      (Lab2A *me);
static QState Lab2A_stateA  (Lab2A *me);
static QState Lab2A_stateB  (Lab2A *me);
static void dispatch (QSignal sig);
void debounce(Xuint32 data,int prevstate);
/**********************************************************************/

int counter = 0;

Lab2A AO_Lab2A;


void Lab2A_ctor(void)  {
	Lab2A *me = &AO_Lab2A;
	QActive_ctor(&me->super, (QStateHandler)&Lab2A_initial);
}


QState Lab2A_initial(Lab2A *me) {
	xil_printf("\n\rInitialization");
    return Q_TRAN(&Lab2A_on);
}

QState Lab2A_on(Lab2A *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			xil_printf("\n\rOn");
			}
			
		case Q_INIT_SIG: {
			return Q_TRAN(&Lab2A_stateA);
			}
	}
	
	return Q_SUPER(&QHsm_top);
}


/* Create Lab2A_on state and do any initialization code if needed */
/******************************************************************/

QState Lab2A_stateA(Lab2A *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			xil_printf("Startup State A\n");
			return Q_HANDLED();
		}
		
		case ENCODER_UP: {
			xil_printf("Encoder Up from State A\n");
			return Q_HANDLED();
		}

		case ENCODER_DOWN: {
			xil_printf("Encoder Down from State A\n");
			return Q_HANDLED();
		}

		case ENCODER_CLICK:  {
			xil_printf("Changing State\n");
			return Q_TRAN(&Lab2A_stateB);
		}

	}

	return Q_SUPER(&Lab2A_on);

}

QState Lab2A_stateB(Lab2A *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			xil_printf("Startup State B\n");
			return Q_HANDLED();
		}
		
		case ENCODER_UP: {
			xil_printf("Encoder Up from State B\n");
			return Q_HANDLED();
		}

		case ENCODER_DOWN: {
			xil_printf("Encoder Down from State B\n");
			return Q_HANDLED();
		}

		case ENCODER_CLICK:  {
			xil_printf("Changing State\n");
			return Q_TRAN(&Lab2A_stateA);
		}

	}

	return Q_SUPER(&Lab2A_on);

}

static void dispatch (QSignal sig){
	Q_SIG((QHsm *) &AO_Lab2A) = sig;
	QHsm_dispatch((QHsm *)&AO_Lab2A);
}

void debounce(Xuint32 data,int prevstate){

	switch (data)
	{
	case 0:
		if(prevstate == 1){counter += 1;}
		else if(prevstate == 2){counter -= 1;}
		break;
	case 1:
		if(prevstate == 3){counter += 1;}
		else if(prevstate == 0){counter -= 1;}
		break;
	case 2:
		if(prevstate == 0){counter += 1;}
		else if(prevstate == 3){counter -= 1;}
		break;
	case 3:
		if(prevstate == 2){counter += 1;}
		else if(prevstate == 1){counter -= 1;}
		else if(prevstate == 3){counter = 0;}
		break;
	case 7:
		if(prevstate == 3){
			dispatch(ENCODER_CLICK);
			for (int j=0; j<5000; j++){};
		}
	}
	switch(counter)
	{
	case -4:
		counter = 0;
		dispatch(ENCODER_DOWN);
		break;
	case 4:
		counter = 0;
		dispatch(ENCODER_UP);
		break;
	}
	prevstate = data;
}

