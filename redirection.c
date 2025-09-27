#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "utils.h"


int my_write_redirection(char** process_args,char* filename){
	int pipefd[2];
	pipe(pipefd);

	int fd = open(filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
	if(fd==-1){return 0;}

	pid_t first_child_pid = fork();
	if(first_child_pid == 0){
		dup2(pipefd[1],1);
		close(pipefd[1]);
		close(pipefd[0]);
		close(fd);
		int res = handle_command(process_args);
		if(res == 0){printf("%s:command not found",process_args[0]);}
		exit(0);
	}

	pid_t second_child_pid = fork();
	unsigned char read_buf[1000];

	if(second_child_pid == 0){
		size_t n;
		close(pipefd[1]);
		while((n = read(pipefd[0],read_buf,1000)) != 0){
			int res = write(fd,read_buf,n);
			if(res == -1){break;}
		}
		close(pipefd[0]);
		close(fd);
		exit(0);
	}


	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	waitpid(first_child_pid,NULL,0);
	waitpid(second_child_pid,NULL,0);
	return 1;
}
