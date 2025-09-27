#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipe.h"
#include "utils.h"


int my_pipe(char** const first_process_args,char** const second_process_args){
	int pipefd[2];
	int res = pipe(pipefd);
	if(res == -1){return 0;}
	pid_t first_command_pid;
	pid_t second_command_pid;
	first_command_pid = fork();
	if(first_command_pid == 0){
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		handle_command(first_process_args);
		exit(0);
	}

	else{
		second_command_pid = fork();
		if(second_command_pid == 0){
			dup2(pipefd[0],STDIN_FILENO);
			close(pipefd[1]);
			close(pipefd[0]);
			handle_command(second_process_args);
			exit(0);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(first_command_pid,NULL,0);
	waitpid(second_command_pid,NULL,0);
	return 1;
}


