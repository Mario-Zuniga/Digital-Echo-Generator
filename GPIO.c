#include "MK64F12.h"
#include "GPIO.h"

static uint8 FlagPortA =FALSE;
static uint8 FlagPortB = FALSE;
static uint8 FlagPortC = FALSE;
static uint8 FlagPortD = FALSE;
static uint8 FlagPortE = FALSE;

uint8 GPIO_irqStatus(GPIO_portNameType portName){
	switch(portName)/** Selecting the GPIO for clock enabling*/
				{
					case GPIO_A: /** GPIO A is selected*/
						return FlagPortA;
						break;
					case GPIO_B: /** GPIO B is selected*/
						return FlagPortB;
						break;
					case GPIO_C: /** GPIO C is selected*/
						return FlagPortC;
						break;
					case GPIO_D: /** GPIO D is selected*/
						return FlagPortD;
						break;
					case GPIO_E: /** GPIO E is selected*/
						return FlagPortE;
						break;
					default: /**If doesn't exist the option*/
						return(FALSE);
				}// end switch
		/**Successful configuration*/
		return(TRUE);
	}// end function

void PORTA_IRQHandler()
{
	FlagPortA = TRUE;
	GPIO_clearInterrupt(GPIO_A);
}

void PORTB_IRQHandler()
{
	FlagPortB = TRUE;
	GPIO_clearInterrupt(GPIO_B);
}

void PORTC_IRQHandler()
{
	FlagPortC = TRUE;
	GPIO_clearInterrupt(GPIO_C);
}


void PORTD_IRQHandler()
{
	FlagPortD = TRUE;
	GPIO_clearInterrupt(GPIO_D);
}

void PORTE_IRQHandler()
{
	FlagPortE = TRUE;
	GPIO_clearInterrupt(GPIO_E);
}

uint8 FALSEPortA(){
	return FlagPortA = FALSE;
}

uint8 FALSEPortB(){
	return FlagPortB = FALSE;
}

uint8 FALSEPortC(){
	return FlagPortC = FALSE;
}

uint8 FALSEPortD(){
	return FlagPortD = FALSE;
}

uint8 FALSEPortE(){
	return FlagPortE = FALSE;
}

uint8 GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			return PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			return PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			return PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			return PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			return PORTE->ISFR=0xFFFFFFFF;
			break;
	}// end switch
}

uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	/*!
	 * \dot
	digraph G {
	main -> parse -> execute;
	main -> init;
	main -> cleanup;
	execute -> make_string;
	execute -> printf
	init -> make_string;
	main -> printf;
	execute -> compare;
	 }
	 \enddot
	*/
	switch(portName)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,GPIO_pinControlRegisterType*  pinControlRegister)
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin]= *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin]= *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin]= *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin]= *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
			break;
		default:/**If doesn't exist the option*/
			return(FALSE);
			break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data ){
	/*Escribe el puerto para asignarle un valor que quiere escribir*/
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR = Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR = Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR = Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR = Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR = Data;
			break;
		default:/**If doesn't exist the option*/
			break;
		}
}
uint32 GPIO_readPORT(GPIO_portNameType portName){
	/*seleciona el puerto PDIR para poder leer que hay en ese puerto*/
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			return GPIOA->PDIR;
			break;
		case GPIO_B:/** GPIO B is selected*/
			return GPIOB->PDIR;
			break;
		case GPIO_C:/** GPIO C is selected*/
			return GPIOC->PDIR;
			break;
		case GPIO_D:/** GPIO D is selected*/
			return GPIOD->PDIR;
			break;
		case GPIO_E: /** GPIO E is selected*/
			return GPIOE->PDIR;
			break;
		default:/**If doesn't exist the option*/
			return(FALSE);
			break;
		}
	return(TRUE);
}
uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin){
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			return (GPIOA->PDIR&(1<<pin)?1:0);
			break;
		case GPIO_B:/** GPIO B is selected*/
			return (GPIOB->PDIR&(1<<pin)?1:0);
			break;
		case GPIO_C:/** GPIO C is selected*/
			return (GPIOC->PDIR&(1<<pin)?1:0);
			break;
		case GPIO_D:/** GPIO D is selected*/
			return (GPIOD->PDIR&(1<<pin)?1:0);
			break;
		case GPIO_E: /** GPIO E is selected*/
			return (GPIOE->PDIR&(1<<pin)?1:0);
			break;
		default:/**If doesn't exist the option*/
			return(FALSE);
			break;
		}
	return(TRUE);
}

void GPIO_setPIN(GPIO_portNameType portName, uint8 pin){
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
			    GPIOA->PSOR |= 1<<pin;//PSOR
				break;
			case GPIO_B:/** GPIO B is selected*/
				 GPIOB->PSOR |=  1<<pin;
				break;
			case GPIO_C:/** GPIO C is selected*/
				 GPIOC->PSOR |=  1<<pin;
				break;
			case GPIO_D:/** GPIO D is selected*/
				 GPIOD->PSOR |=  1<<pin;
				break;
			case GPIO_E: /** GPIO E is selected*/
				 GPIOE->PSOR |=  1<<pin;
				break;
			default:/**If doesn't exist the option*/
				break;
			}
}

void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin){
	uint32 Mask=0;
	Mask= 1<<pin;
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PCOR = Mask;
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PCOR = Mask;
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PCOR = Mask;
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PCOR = Mask;
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PCOR = Mask;
				break;
			default:/**If doesn't exist the option*/
				break;
			}
}

void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){

	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
				    GPIOA->PTOR |= 1<<pin;
					break;
				case GPIO_B:/** GPIO B is selected*/
					 GPIOB->PTOR |= 1<<pin;
					break;
				case GPIO_C:/** GPIO C is selected*/
					 GPIOC->PTOR |= 1<<pin;
					break;
				case GPIO_D:/** GPIO D is selected*/
					 GPIOD->PTOR |= 1<<pin;
					break;
				case GPIO_E: /** GPIO E is selected*/
					 GPIOE->PTOR |= 1<<pin;
					break;
				default:/**If doesn't exist the option*/
					break;
				}
}

void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction){
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
				    GPIOA->PDDR = direction;
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDDR = direction;
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDDR = direction;
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDDR = direction;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR = direction;
					break;
				default:/**If doesn't exist the option*/
					break;
				}
}

void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin){
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
				   if(GPIO_OUTPUT == State){
					GPIOA->PDDR |= 1<<pin;
				   }else{
					GPIOA->PDDR &= ~(1<<pin);
				   }
					break;
				case GPIO_B:/** GPIO B is selected*/
					if(GPIO_OUTPUT == State){
					GPIOB->PDDR |= 1<<pin;
					}else{
					GPIOB->PDDR &= ~(1<<pin);
					}
					break;
				case GPIO_C:/** GPIO C is selected*/
				    if(GPIO_OUTPUT == State){
      			    GPIOC->PDDR |= 1<<pin;
					}else{
					GPIOC->PDDR &= ~(1<<pin);
				    }
					break;
				case GPIO_D:/** GPIO D is selected*/
					if(GPIO_OUTPUT == State){
					GPIOD->PDDR |= 1<<pin;
					}else{
					GPIOD->PDDR &= ~(1<<pin);
					 }
					break;
				case GPIO_E: /** GPIO E is selected*/
					if(GPIO_OUTPUT == State){
					GPIOE->PDDR |= 1<<pin;
					}else{
					GPIOE->PDDR &= ~(1<<pin);
					}
					break;
				default:/**If doesn't exist the option*/
					break;
				}
}
