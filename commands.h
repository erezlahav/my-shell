#ifndef COMMANDS_H
#define COMMANDS_H

typedef int (*func_pointer)(char** args);

int my_ls(char** args);
int my_pwd(char** args);
int my_whoami(char** args);
int my_cd(char** args);


struct internal_command{
        char* func_name;
        func_pointer function;

};

extern struct internal_command implemented_internals[];
#endif
