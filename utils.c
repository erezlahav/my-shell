#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"
#include "parser.h"
#include "pipe.h"
#include "utils.h"
#include "redirection.h"


char* check_command_in_PATH_env(char* command){
	char* path_string = getenv("PATH");
	char** array_of_paths = parser(path_string,":");
	char* full_path_command = malloc(1024);
	for(int i = 0;array_of_paths[i] != NULL;i++){
		sprintf(full_path_command,"%s/%s",array_of_paths[i],command);
		if(access(full_path_command,X_OK) == 0){
			return full_path_command;
		}
	}
	return NULL;
}


func_pointer check_in_internals(const char* command){
	int current_index = 0;
	struct internal_command current_internal;
	while(1){
		current_internal = implemented_internals[current_index];
		if(current_internal.func_name == NULL || current_internal.function == NULL){
			break;
		}

		if(strcmp(current_internal.func_name,command) == 0){
			return current_internal.function;
		}
		else{
			current_index++;
		}
	}
	return NULL;

}

char* is_char_exists_in_args(char** args,char* target){
	for(int i = 0; args[i] != NULL;i++){
		if(strcmp(args[i],target) == 0){
			return target;
		}
	}
	return NULL;
}

char*** split_args_by_operators(char** args, char* delim_operator) {
    char*** splitted_args = malloc(3 * sizeof(*splitted_args));
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], delim_operator) == 0) {
            args[i] = NULL;
            splitted_args[0] = args;
            splitted_args[1] = args + i + 1;
            splitted_args[2] = NULL;
            return splitted_args;
        }
    }

    splitted_args[0] = args;
    splitted_args[1] = NULL;
    splitted_args[2] = NULL;
    return splitted_args;
}

char* find_delim_operator(char** args){
	char* delim_operator;
	char* operators[] = {"|",">","<"};
        size_t arr_length = sizeof(operators)/sizeof(operators[0]);
        for(int i = 0; i < arr_length;i++){
                delim_operator = is_char_exists_in_args(args,operators[i]);
                if(delim_operator != NULL){
                        break;
                }
        }
	return delim_operator;
}



int handle_command(char** args_command){
	char* delim_operator;
	char*** splitted_args;
	func_pointer internal_func_pointer;
	char* external_function_path;
	delim_operator = find_delim_operator(args_command);
	if(delim_operator != NULL){
		splitted_args = split_args_by_operators(args_command,delim_operator);

		if(strcmp(delim_operator,"|") == 0){

			my_pipe(splitted_args[0],splitted_args[1]);
			return 1;
		}

		else if(strcmp(delim_operator,">") == 0){
			my_write_redirection(splitted_args[0],splitted_args[1][0]);
			return 1;
		}

                else if(strcmp(delim_operator,"<") == 0){
                        my_read_redirection(splitted_args[0],splitted_args[1][0]);
                        return 1;
                }
		else{
			printf("invalid operator");
			return 0;
		}
	}
	else if(delim_operator == NULL){
		char* command = args_command[0];
		//searching in internal commands
		internal_func_pointer = check_in_internals(command);
		if(internal_func_pointer != NULL){
			internal_func_pointer(args_command);
			return 1;
		}
		//searching in external commands
		else{
			external_function_path = check_command_in_PATH_env(command);
			if(external_function_path != NULL){
				pid_t pid = fork();
				if(pid == 0){
					execve(external_function_path, args_command,NULL);
		            		perror("execvp failed");
            				exit(1);
				}
				else{
					waitpid(pid,NULL,0);
					return 1;
				}
			}

		}

	}

	return 0;
}


