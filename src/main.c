#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include "parser.h"
#include "commands.h"
#include "pipe.h"
#include "utils.h"

#define DELIM_CHARS " \n\t\r"
int main(){
	while(1){
		printf(">");
		char user_input[50];
		fgets(user_input,sizeof(user_input),stdin);
		user_input[strcspn(user_input, "\n")] = '\0';

		char** input_commands = parser(user_input,DELIM_CHARS);
		int is_command_found;
		is_command_found = handle_command(input_commands);
		if(is_command_found == 0){
			printf("%s: command not found\n",user_input);
		}
	}
}
