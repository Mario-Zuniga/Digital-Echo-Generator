#include "NVIC.h"
#include "GPIO.h"
#include "SIGNAL.h"
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "DAC.h"

/**The following function initializes the DAC module*/
void DAC_Initialize(void) {
	/**The following sentences are executed to initialize the DAC module*/
	SIM->SCGC2 = SIM_SCGC2_DAC0_MASK;				/**The clock-gating for the DAC is turned on*/
	/**The DAC is enabled*/
	DAC0->C0 |= DAC_ENABLE;
	DAC0->C0 |= DAC_RFS;
}

/**This function writes the input values to the DAC for them to be outputed*/
void DAC_Update(uint32 DAC_Data) {
	//en DAC_DAT0L primero elimina los bits que no necesitas para dejar los 8 bits que se ocupan de la parte baja
	DAC0->DAT[0].DATL = DAC_Data & (DACH);
	//en DAC0_DAT0H luego hace el recorrimeinto para quedarte con los 4 bits que ocupas de la parte alta
	DAC0->DAT[0].DATH = (DAC_Data & (DACC)) >> 8; //Configura el DAC en 4 bits
}

void ActviaDAC(){
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;//prende el clock gating del DAC
	DAC0->C0 |= ENABLE; //prender el DAC para poderlo utilizar
	DAC0->C0 |= RFS;//Le da una referencia al DAC
}
