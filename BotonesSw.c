#include "botonesSw.h"
#include "Convolucion.h"
void PushButtonsInit(void){
	gpio_pin_config_t Port_config = {
	      kGPIO_DigitalInput
	};

	port_pin_config_t config =
	{
			kPORT_PullUp,
			kPORT_FastSlewRate,
			kPORT_PassiveFilterDisable,
			kPORT_OpenDrainDisable,
			kPORT_LowDriveStrength,
			kPORT_MuxAsGpio,
			kPORT_UnlockRegister
	};

	PORT_SetPinInterruptConfig(PuertoC, PinC0_GPIO, kPORT_InterruptFallingEdge); //C0
	PORT_SetPinInterruptConfig(PuertoC, PinC1_GPIO, kPORT_InterruptFallingEdge); //C1
	PORT_SetPinInterruptConfig(PuertoC, PinC2_GPIO, kPORT_InterruptFallingEdge); //C2
	PORT_SetPinInterruptConfig(PuertoC, PinC3_GPIO, kPORT_InterruptFallingEdge); //C3
	PORT_SetPinInterruptConfig(PuertoC, PinC4_GPIO, kPORT_InterruptFallingEdge); //C4
	PORT_SetPinInterruptConfig(PuertoC, PinC5_GPIO, kPORT_InterruptFallingEdge); //C5

	GPIO_PinInit(Puerto_GPIOC,PinC0_GPIO , &Port_config);
	GPIO_PinInit(Puerto_GPIOC,PinC1_GPIO , &Port_config);
	GPIO_PinInit(Puerto_GPIOC,PinC2_GPIO , &Port_config);
	GPIO_PinInit(Puerto_GPIOC,PinC3_GPIO , &Port_config);
	GPIO_PinInit(Puerto_GPIOC,PinC4_GPIO , &Port_config);
	GPIO_PinInit(Puerto_GPIOC,PinC5_GPIO , &Port_config);

	NVIC_SetPriority( PuertoC_IRQ, 4);
	NVIC_EnableIRQ( PuertoC_IRQ );

}


uint8_t RetornaBotones(){
	static uint8_t Botones = 0;
	Botones = GPIO_GetPinsInterruptFlags(Puerto_GPIOC);
	efectoBotones(Botones);
	return Botones;
}

uint8_t PinGPIOForClear(){
	static uint8_t dato = 0;
	dato = RetornaBotones();
	switch(dato){
	case Boton_C0:
		return PinC0_GPIO;
	break;
	case Boton_C1:
		return PinC1_GPIO;
	break;
	case Boton_C2:
		return PinC2_GPIO;
	break;
	case Boton_C3:
		return PinC3_GPIO;
	break;
	case Boton_C4:
		return PinC4_GPIO;
	break;
	case Boton_C5:
		return PinC5_GPIO;
	break;
	default:
	break;
	}
}

void PORTC_IRQHandler( void ){
	GPIO_ClearPinsInterruptFlags(Puerto_GPIOC, 1U << PinGPIOForClear());
}
