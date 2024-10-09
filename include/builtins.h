#ifndef BUILTINS_H
# define BUILTINS_H


#include "ast.h"
#include "envlst.h"

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

bool    cd(char **args, t_envlst *envlst);
t_builtins_type    builtin_check(char *cmd);

#endif