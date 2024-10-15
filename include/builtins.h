#ifndef BUILTINS_H
# define BUILTINS_H


#include "ast.h"
#include "envlst.h"
#include <unistd.h>
#include <limits.h> //check is it allowed
#include "execution.h"


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
bool    mshell_export(t_executor *executor, t_ast *node);
bool    mshell_env(t_executor *executor);
bool    mshell_exit(char **arg);
bool    mshell_unset(t_envlst **envlst, t_ast *node);
bool    mshell_pwd(t_executor *executor);
bool    mshell_echo(char **args);

bool    exec_builtin(t_executor *executor, t_ast *node, t_builtins_type type);

void    display_error(char *intro, char *body, char *conclusion);
#endif