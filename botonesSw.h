#ifndef SOURCE_BOTONES_H_
#define SOURCE_BOTONES_H_

#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "MK64F12.h"
#include "stdint.h"

/** Definiciones para saber cual boton fue precionado **/
#define Boton_C0 0x1	//C0
#define Boton_C1 0x2	//C1
#define Boton_C2 0x4	//C2
#define Boton_C3 0x8	//C3
#define Boton_C4 0x10	//C4
#define Boton_C5 0x20	//C5

/** Definiciones para configurar los puertos */
#define Puerto_GPIOC GPIOC
#define PuertoC_IRQ PORTC_IRQn
#define PuertoC PORTC

/** Pin del GPIO del puerto */
#define PinC0_GPIO 0U
#define PinC1_GPIO 1U
#define PinC2_GPIO 2U
#define PinC3_GPIO 3U
#define PinC4_GPIO 4U
#define PinC5_GPIO 5U

/** Funcion para inicializacion del puerto */
void PushButtonsInit(void);

/** una funcion para saber que boton se preciono */
uint8_t RetornaBotones();

/** retorna para limpiar la interruocion de el pin que fue utilizado */
uint8_t PinGPIOForClear();

#endif /* SOURCE_BOTONES_H_ */
