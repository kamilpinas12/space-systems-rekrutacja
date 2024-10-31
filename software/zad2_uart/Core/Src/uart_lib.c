/*
 * uart_lib.c
 *
 *  Created on: Oct 31, 2024
 *      Author: kamil
 */


#include "usart.h"


#include"uart_lib.h"
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


command_typedef command_list[] = {
    {"komenda", 5},
    {"komenda1", 4},
    {"set_speed", 2}
};

int command_list_size = sizeof(command_list) / sizeof(command_list[0]);


static char command_buffer[COMMAND_MAX_LENGHT + 1];
static uint32_t command_size;




void command_buffer_append(uint8_t value){
	if (value == '\n') {
		if (command_size > 0) {
			command_buffer[command_size] = '\0';
			parse_command();
			command_size = 0;
		}
	}
	else {
		if (command_size >= COMMAND_MAX_LENGHT) {
			command_size = 0;
		}
		command_buffer[command_size++] = value;
	}
}



int parse_command(){
    char function_code[FUNCTION_CODE_MAX_LENGHT];
    char args[MAX_NUM_ARGS][ARG_MAX_LENGHT];

    int function_code_idx = 0;
    for(int i = 0; i< command_size && i < FUNCTION_CODE_MAX_LENGHT; i++){
        if(command_buffer[i] == '['){
            function_code_idx = i;
            strncpy(function_code, command_buffer, function_code_idx);
            function_code[function_code_idx] = '\0';
            break;
        }
    }

    int arg_idx = -1;
    int data_idx = 0;

    bool close_bracket = 0;

    for(int i = function_code_idx + 1; i < command_size; i++){
        if(i == function_code_idx + 1){
            if(command_buffer[i] != '='){
                return 0;
            }
            continue;
        }
        if(command_buffer[i] == ']') {
            close_bracket = 1;
            args[arg_idx][data_idx] = '\0';
            break;
        }
        if(command_buffer[i] == ';'){
            args[arg_idx][data_idx] = '\0';
            arg_idx ++;
            data_idx = 0;
        }
        else{
            if(arg_idx == -1) arg_idx = 0;
            args[arg_idx][data_idx] = command_buffer[i];
            data_idx += 1;
        }
    }

    if(!close_bracket) return 0;

    return callback(function_code, args, arg_idx + 1);

}



int callback(char* function_code, char args[MAX_NUM_ARGS][ARG_MAX_LENGHT], int num_args)
{
    command_typedef command;
    bool is_command_found = 0;

    for(int i = 0; i < command_list_size; i++){
        if(strcmp(function_code, command_list[i].function_code) == 0){
            command = command_list[i];
            if(num_args != command.num_args){
                return 0;
            }
            is_command_found = 1;
        }
    }
    if(!is_command_found) return 0;


    if(strcmp(function_code, "komenda") == 0){

        // do something
    }


    if(strcmp(function_code, "komenda1") == 0){

        // do something
    }


    if(strcmp(function_code, "set_speed") == 0){

        // do something
    }

    return 1;
}

