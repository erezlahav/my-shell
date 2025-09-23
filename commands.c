#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>

#include "commands.h"
#define CWD_SIZE 50









int my_ls(){
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


int my_pwd(){
        char cwd[CWD_SIZE];
        getcwd(cwd,CWD_SIZE);
        if(cwd == NULL){
                printf("errno = %d, %s\n",errno,strerror(errno));
                return 0;
        }
        printf("%s\n",cwd);
        return 1;
}



int my_whoami(){
        uid_t uid = getuid();

        struct passwd* pwuid = getpwuid(uid);
        if(pwuid == NULL){
                printf("errno = %d, %s\n",errno,strerror(errno));
        }

        printf("%s\n",pwuid->pw_name);
}

int my_cd(char* target_dir){
	if(chdir(target_dir) != 0){
		printf("error no %d, %s\n",errno,strerror(errno));
	}
}



