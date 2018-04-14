#include "Convolucion.h"
#include "botonesSw.h"
#include "fsl_pit.h"

#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define Rmax 15000
uint32 R = 15000;
float Volumen = 1;
float a = 0.9;
uint32 n = 0;
float Echo[Rmax] = {};
float y = 0;

void efectoBotones(uint8_t valor) {
	/* Entramos en un case para encontrar el valor del boton presionado */
	switch(valor) {
		/* Caso boton C0, con la funcion de incrementar el valor R */
		case Boton_C0:
			/* El valor R se incrementa */
			R = R + 1000;
			/* Verificamos que R no exceda 15000 */
			if(R > 15000){
				/* Si se llega a exceder, se mantiene en 15000 */
				R = 15000;
			}
		break;

		/* Caso boton C1, con la funcion de decrementar el valor R */
		case Boton_C1:
				/* Se decrementa el valor de R */
				R = R - 1000;
				/* Verificamos que no este por debajo de 1000 */
				if(R < 1000){
					/* Se mantiene en 1000 de ser verdadero */
					R = 1000;
				}
			break;

		/* Caso boton C2, con la funcion de atenuar el volumen */
		case Boton_C2:
			/* Decrementamos el valor del volumen */
			Volumen -= 0.1;
			/* Verificamos que el volumen no sea menor de 0.1, de ser así, lo mantenemos en 0.1 */
			if(Volumen <= 0.1){
				Volumen = 0.1;
			}else if(Volumen < 0.1){
				Volumen = 0.1;
			}
			break;

		/* Caso boton C3, con la funcion de incrementar el volumen */
		case Boton_C3:
			/* Incrementamos el volumen */
			Volumen += 0.1;
			/* Verificamos que el volumen no exceda del valor 1, de ser así, lo mantenemos en 1 */
			if(Volumen  >= 1){
				Volumen = 1;
			} else if(Volumen  > 1){
				Volumen = 1;
			}
			break;

		/* Caso boton C4, incrementa el valor de alpha */
		case Boton_C4:
			/* Incrementamos alpha*/
			a = a + 0.1;
			/* Hacemos una verificación para que alpha no exceda el valor de 1 */
			if(a > 1){
				a = 1;
			}
			break;

		/* Caso boton C5, decrementa el valor de alpha */
		case Boton_C5:
			/* Decrementamos alpha */
			a = a - 0.1;
			/* Verificamos que alpha nunca sea menor a 0.1 */
			if(a < 0.1){
				a = 0.1;
			}
			break;
		default:

			break;
	}
}

/* Funcion para almacenar los valores del ADC, donde creamos Eco */
void Eco(float *x) { /* El valor x de entrada es la muestra tomada directamente del ADC */

	/* El arreglo Echo de n valores comienza en el punto 0, expandiendose hasta limite n(R = 15000) */
	Echo[n] = a*Echo[n]; /* Cuando entre por primera vez este punto sera 0 */

	/* Ecuacion representante de la creación de ecos, donde esta entrando el valor actual de la sumación del eco
	 * mostrada en la linea superior, donde las primeras 3 muestras no crearán mucho impacto, es a partir de la
	 * muestra 4, donde las 3 muestras previas (1 ->), comienzan a funcionar, ya que valores previos en 0 y numeros
	 * negativos no pueden funcionar */
	y = (-1)*(a*(*x))+(1-(((a)*(a))*Echo[n]));

	/* El valor actual del ADC es añadido a la posición del arreglo de eco actual */
	Echo[n] += *x;

	/* Verificamos que el tamaño del arreglo de n valores n exceda el retardo R */
	if(n > R){
		/* Si es así, lo volvemos a convertir en 0 para evitar problemas con el audio */
		n = 0;
	}else{
		/* De lo contrario, incrementamos el valor para la muestra */
		n++;
	}
}

float Respuesta(void){
	return Volumen*(y+1.8);
}
