#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ARGS_NUMBER 64
#define MAX_COMMAND_LENGTH 20
#define DELIM_CHARS " \n\t\r"
char** parser(char* command){
	char** parsed_commands = malloc(sizeof(char*) * ARGS_NUMBER);
	char* curr_string = strtok(command, DELIM_CHARS);
	int current_index = 0;

	while(curr_string != NULL && current_index < ARGS_NUMBER) {
    	parsed_commands[current_index] = malloc(MAX_COMMAND_LENGTH);
    	strncpy(parsed_commands[current_index], curr_string, MAX_COMMAND_LENGTH - 1);
    	parsed_commands[current_index][MAX_COMMAND_LENGTH-1] = '\0';

    	current_index++;
    	curr_string = strtok(NULL, DELIM_CHARS);
	}

	parsed_commands[current_index] = NULL;
	return parsed_commands;
}
