
#include "../include/builtins.h"

bool    mshell_export(t_envlst **envlst, t_ast *node)
{
    t_envlst    *new_env;
    int         i;

    i = 1;
    while (node->args[i])
    {
        new_env = create_envlst(node->args[i]);
        if (!new_env)
            return (false);
        add_envlst(envlst, new_env);
        i++;
    }
    t_envlst *current;

    current = *envlst;
    while (current)
    {
        printf("%s\n", current->variable);
        current = current->next;
    }
    return (true);
}