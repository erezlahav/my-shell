#ifndef COMMANDS_H
#define COMMANDS_h
typedef int (*func_pointer)(char** args);
int my_ls();
int my_pwd();
int my_whoami();
int my_cd();
#endif
