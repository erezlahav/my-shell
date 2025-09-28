#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ARGS_NUMBER 64
#define MAX_COMMAND_LENGTH 256

char** parser(char* str,char* delim_chars){
	char temp_command[MAX_COMMAND_LENGTH];
	strncpy(temp_command,str,sizeof(temp_command));
	char** parsed_commands = malloc(sizeof(char*) * ARGS_NUMBER);
	char* curr_string = strtok(temp_command, delim_chars);
	int current_index = 0;

	while(curr_string != NULL && current_index < ARGS_NUMBER) {
    		parsed_commands[current_index] = malloc(MAX_COMMAND_LENGTH);
    		strncpy(parsed_commands[current_index], curr_string, MAX_COMMAND_LENGTH - 1);
    		parsed_commands[current_index][MAX_COMMAND_LENGTH-1] = '\0';

    		current_index++;
    		curr_string = strtok(NULL, delim_chars);
	}

	parsed_commands[current_index] = NULL;
	return parsed_commands;
}
