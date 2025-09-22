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




int main(){
	while(1){
		printf(">");


		char user_input[50];
		fgets(user_input,sizeof(user_input),stdin);
		user_input[sizeof(user_input)-1] = '\x00';
		char** input_commands = parser(user_input);
		char* first_command = input_commands[0];
		if(strcmp(first_command,"pwd") == 0){
			my_pwd();
		}

		else if(strcmp(first_command,"ls") == 0){
			my_ls();
		}

		else if(strcmp(first_command,"whoami") == 0){
			my_whoami();
		}

		else if(strcmp(first_command,"exit") == 0){
			exit(0);
		}

		else if(strcmp(first_command,"cd") == 0){
			if(input_commands[1] != NULL){
				my_cd(input_commands[1]);
			}

		}



		else{
			printf("%s: command not found\n",user_input);
		}
	}
}
