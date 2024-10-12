#include "../include/builtins.h" 

bool    mshell_env(t_envlst *envlst)
{
    t_envlst    *current;

    current = envlst;
    if (!current)
        return (false);
    while (current)
    {
        printf("%s%s\n", current->key, current->value);
        current = current->next;
    }
    return (true);
}