
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "ADC.h"
#include "botonesSw.h"
#include "senal.h"
#include "DAC.h"
#include "stdio.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_pit.h"
#include "PIT.h"
#include "botonesSw.h"
#include "Convolucion.h"

// ADC configuration
const ADC_ConfigType ADC_Config={
	ADC_0,
	BITMODE_12_13,
	DADP1,
	SAMPLES_32,
	AVERAGE_ENABLE,
	INTERRUPT_ENABLE
};

extern volatile bool pitIsrFlag;
volatile bool Ready = false;

int main(void){
	 /* Init board hardware. */
	 BOARD_InitPins();
	 BOARD_BootClockRUN();
	 BOARD_InitDebugConsole();
	 float ADC_Datos = 0;		
	 float SalidadDAC = 0;		
	 ADC_init(&ADC_Config);		
	 ActviaDAC();				
	 PIT_init();				
	 PushButtonsInit();  
	 EnableInterrupts;		

    for (;;) {
        if (true == pitIsrFlag){
    		pitIsrFlag = false;
    	
    	    ADC_Datos = ADC_read(ADC_Config.ADC_Channel);
    		PIT_StartTimer(PIT, kPIT_Chnl_0);
    		ADC_Datos = ADC_Datos - 2000;
    		Eco(&ADC_Datos);
    		SalidadDAC = Respuesta();
    		DAC_Update(SalidadDAC);
    	}
    }
    return 0;
}
