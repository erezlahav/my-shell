#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include "commands.h"

#define CWD_SIZE 50



struct internal_command implemented_internals[] = {
    {"cd", my_cd},
    {"ls", my_ls},
    {"whoami", my_whoami},
    {"pwd", my_pwd},
    {"exit",my_exit},
    {NULL, NULL}
};


int my_exit(char** args){
	exit(0);
}


int my_ls(char** args){
	if(strcmp(args[0],"ls") != 0){printf("error calling ls");return 0;}
	if(args[1] != NULL){printf("error, in internal ls there is no parameters");}
        char cwd[CWD_SIZE];
        getcwd(cwd,CWD_SIZE);
        DIR* dp = opendir(cwd);
        if(dp == NULL){
                printf("error\n");
                return 0;
        }

        while(1){
                struct dirent* curr_f = readdir(dp);
                if(curr_f == NULL){
                        break;
                }
                printf("%s\n",curr_f->d_name);
        }

}


int my_pwd(char** args){
	if(strcmp(args[0],"pwd") != 0){printf("error calling pwd");return 0;}
        if(args[1] != NULL){printf("error, in internal pwd there is no parameters");return 0;}
        char cwd[CWD_SIZE];
        getcwd(cwd,CWD_SIZE);
        if(cwd == NULL){
                printf("errno = %d, %s\n",errno,strerror(errno));
                return 0;
        }
        printf("%s\n",cwd);
        return 1;
}



int my_whoami(char** args){
        if(strcmp(args[0],"whoami") != 0){printf("error calling whoami");return 0;}
        if(args[1] != NULL){printf("error, in internal whoami there is no parameters");return 0;}
        uid_t uid = getuid();

        struct passwd* pwuid = getpwuid(uid);
        if(pwuid == NULL){
                printf("errno = %d, %s\n",errno,strerror(errno));
        }

        printf("%s\n",pwuid->pw_name);
}

int my_cd(char** args){
        if(strcmp(args[0],"cd") != 0){printf("error calling cd");return 0;}
        if(args[2] != NULL){printf("error, in internal cd there is too many parameters");return 0;}
	if(chdir(args[1]) != 0){
		printf("error no %d, %s\n",errno,strerror(errno));
	}
}



