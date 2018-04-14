#include "NVIC.h"
#include "senal.h"
#include "GPIO.h"

void InterrupcionesFTM(void){
	NVIC_enableInterruptAndPriotity(FTM1_IRQ, PRIORITY_6);
	
}

