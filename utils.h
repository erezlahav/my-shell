#pragma once
#include "commands.h"
int handle_command(char** args_command);
func_pointer check_in_internals(const char* command);
char* check_command_in_PATH_env(char* command);
int execute_external_command(char* full_path_command,char** const argv);
char* find_delim_operator(char** args);
