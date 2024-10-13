#ifndef BUILTINS_H
# define BUILTINS_H


#include "ast.h"
#include "envlst.h"
#include <unistd.h>
#include <limits.h> //check is it allowed


typedef enum e_builtins {
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT,
    NONE
} t_builtins_type;

t_builtins_type    builtin_check(char *cmd);
bool    cd(char **args, t_envlst *envlst);
bool    mshell_export(t_envlst **envlst, t_ast *node);
bool    mshell_env(t_envlst *envlst);
bool    mshell_exit(char **arg);
bool    mshell_pwd(char **args);
bool    mshell_echo(char **args);


void    display_error(char *intro, char *body, char *conclusion);
#endif