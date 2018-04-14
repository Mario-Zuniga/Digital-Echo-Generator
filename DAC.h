#ifndef SOURCES_DAC_H_
#define SOURCES_DAC_H_

#include "DataTypeDefinitions.h"
#include "MK64F12.h"

/**The following macros are needed to initialize the DAC module*/
#define DAC_ENABLE      0x80
#define DAC_RFS         0x40

#define DACH 0x00FF
#define DACC 0x0F00
#define ENABLE 0x80
#define RFS 0x40
#define sw3 0
#define GPIO_PULLUP_ENABLE	0x00000103
#define SW3_MASK			0x00000010
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
		This function initializes the DAC module.
 	 \param[in]
		Function is VOID.
 	 \return
		VOID
 */
void DAC_Initialize(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief
		This function writes the input values to the DAC for them to be outputed.
 	 \param[in]
		DAC_Data 	Value to be outputed by the DAC.
 	 \return
		VOID
 */
void DAC_Update(uint32 DAC_Data);

void dac_funtion();
void ActviaDAC();
void ConfiguraSw3();

#endif /* SOURCES_DAC_H_ */
