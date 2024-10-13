#include "../include/builtins.h" 

bool    mshell_env(t_envlst *envlst)
{
    print_env(envlst, true);
    return (true);
}