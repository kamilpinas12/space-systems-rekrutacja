/*
 * spx24.c
 *
 *  Created on: Oct 27, 2024
 *      Author: kamil
 */

#include "spx24.h"



volatile bool spx_data_ready = 0;
volatile bool spx_busy = 0;



spx_status_typedef spx_measure(soil_parameter_typedef soil_parameter){
	if(spx_busy) return spx24_busy;

	spx_data_ready = 0;
	spx_busy = 1;

	//set CTRL0 and CTRL1 depends on soil parameter
	switch(soil_parameter){
		case moisture:
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_RESET);
			break;
		case pH:
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_SET);
			break;
		case temperature:
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CTRL0_GPIO_Port, CTRL0_Pin, GPIO_PIN_RESET);
			break;
	}

	// set TRG to high then start timer then reset TRG in timer interrupt after 13 ms (min time = 10ms)
	HAL_GPIO_WritePin(TRG_GPIO_Port, TRG_Pin, GPIO_PIN_SET);
	__HAL_TIM_SET_COUNTER(&htim15, 0);
	__HAL_TIM_CLEAR_IT(&htim15 ,TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim15);

	return spx24_ok;

}




float convert_adc_to_soil_parameter(soil_parameter_typedef soil_parameter, uint32_t adc_val){
	float voltage = V_CC * adc_val / 4096.0f;
	float result = 0;

	switch(soil_parameter){
	case moisture:
		result = ((voltage - V_MIN)/(V_MAX - V_MIN)) * (THETA_MAX - THETA_MIN) + THETA_MIN;

	case pH:
		result = pH_REF + log10(voltage / V_REF);

	case temperature:
		result = T0 * exp(K * (voltage - V0));

	}
	return result;


}
