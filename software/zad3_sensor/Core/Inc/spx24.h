/*
 * spx24.h
 *
 *  Created on: Oct 27, 2024
 *      Author: kamil
 */

#ifndef INC_SPX24_H_
#define INC_SPX24_H_

#include<stm32g4xx_hal.h>
#include<math.h>
#include<stdbool.h>


#include"main.h"
#include "tim.h"


//values for data conversion

#define V_CC 3.3f

//soil moisture
#define V_MAX V_CC
#define V_MIN 0.0f
#define THETA_MIN 0.0f
#define THETA_MAX 100.0f

//soil pH
#define pH_REF 7
#define V_REF V_CC/2

//soil temperature
#define V0 0.0f
#define T0 273.0f
#define K 0.25/V_CC // can be calibrated !!!






typedef enum{
	spx24_busy = 0,
	spx24_ok
}spx_status_typedef;



typedef enum{
	moisture = 0,
	pH,
	temperature
}soil_parameter_typedef;



spx_status_typedef spx_measure(soil_parameter_typedef soil_parameter);

float convert_adc_to_soil_parameter(soil_parameter_typedef soil_parameter, uint32_t adc_val);















#endif /* INC_SPX24_H_ */
