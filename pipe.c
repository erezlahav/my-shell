#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipe.h"


int my_pipe(const char** first_process_args,const char** second_process_args){
	int pipefd[2];
	int res = pipe(pipefd);
	pid_t first_command_pid;
	pid_t second_command_pid;
	first_command_pid = fork();
	if(first_command_pid == 0){
		printf("first command excuting...\n");
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[1]);
		execvp(first_process_args[0], first_process_args);

	}

	else{
		second_command_pid = fork();
		if(second_command_pid == 0){
			printf("second command excuting...\n");
			dup2(pipefd[0],STDIN_FILENO);
			close(pipefd[0]);
			execvp(second_process_args[0], second_process_args);
		}
	}
	waitpid(first_command_pid,NULL,0);
	waitpid(second_command_pid,NULL,0);

}


