#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "utils.h"


int my_write_redirection(char** process_args,char* filename){
	int fd = open(filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
	if(fd==-1){return 0;}

	pid_t pid = fork();
	if(pid == 0){
		dup2(fd,1);
		close(fd);
		int res = handle_command(process_args);
		if(res == 0){return 0;}
		exit(0);
	}
	waitpid(pid,NULL,0);
	close(fd);
	return 1;
}
int my_read_redirection(char** process_args,char* filename){

	int fd = open(filename,O_RDONLY);
	if(fd == -1){return 0;}
	pid_t pid = fork();
        if(pid == 0){
                dup2(fd,0);
                close(fd);
                int res = handle_command(process_args);
                if(res == 0){return 0;}
		exit(0);
        }
	waitpid(pid,NULL,0);
        close(fd);
	return 1;
}
