#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"
#include "parser.h"

struct internal_command{
	char* func_name;
	func_pointer function;

};
struct internal_command internals[] = {
	{"cd",my_cd},
	{"ls",my_ls},
	{"whoami",my_whoami},
	{"pwd",my_pwd},
	{NULL,NULL}
};

func_pointer check_command_in_PATH_env(char* command){
	char* path_string = getenv("PATH");
	char** array_of_paths = parser(path_string,":");
	char full_path_command[1024];
	for(int i = 0;array_of_paths[i] != NULL;i++){
		sprintf(full_path_command,"%s/%s\n",array_of_paths[i],command);
		printf("%s",full_path_command);
	}


}


func_pointer check_in_internals(const char* command){
	int current_index = 0;
	struct internal_command current_internal;
	while(1){
		current_internal = internals[current_index];
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

int main(){
	check_command_in_PATH_env("ls");
}
