#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"
//#include "MK64F12.h"
/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {PIT_0,PIT_1,PIT_2,PIT_3} PIT_TimerType;

void PIT_init(void);

#endif /* PIT_H_ */
