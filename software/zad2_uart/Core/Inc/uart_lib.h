/*
 * uart_lib.h
 *
 *  Created on: Oct 31, 2024
 *      Author: kamil
 */

#ifndef INC_UART_LIB_H_
#define INC_UART_LIB_H_



#define COMMAND_MAX_LENGHT 60
#define FUNCTION_CODE_MAX_LENGHT 15
#define MAX_NUM_ARGS 5
#define ARG_MAX_LENGHT 10



void command_buffer_append(uint8_t value);
int parse_command(void);
int callback(char* function_code, char args[MAX_NUM_ARGS][ARG_MAX_LENGHT], int num_args);
void help();


typedef struct {
    char function_code[FUNCTION_CODE_MAX_LENGHT];
    int num_args;
}command_typedef;










#endif /* INC_UART_LIB_H_ */
