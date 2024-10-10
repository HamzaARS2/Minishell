
#include "../include/builtins.h"


int find_equal(char *str)
{
    int i;

    i = 0;
    while (str && str[i] && str[i] != '=')
        i++;
    return (i);
}

t_envlst    *env_is_exist(t_envlst *envlst, char *new_env)
{
    t_envlst *current;

    current = envlst;
    while (current)
    {
        if (!ft_strncmp(current->key, new_env, find_equal(new_env)))
            return (current);
        current = current->next;
    }
    return (NULL);
}

bool    env_update(t_envlst *env, char *new_env)
{
    char    *update_value;

    if (!env)
        return (false);
    update_value = ft_strchr(new_env, '=');
    if (!update_value)
        return (false);
    update_value = ft_strdup(update_value);
    free(new_env);
    env->value = update_value;
    return (true);
}

bool    mshell_export(t_envlst **envlst, t_ast *node)
{
    t_envlst    *new_env;
    int         i;

    i = 0;
    while (node->args[++i])
    {
        if (env_update(env_is_exist(*envlst, node->args[i]), node->args[i]))
            continue;
        new_env = create_envlst(node->args[i]);
        if (!new_env)
            return (false);
        add_envlst(envlst, new_env);
    }
    t_envlst *current;

    current = *envlst;
    while (current)
    {
        printf("%s%s\n", current->key, current->value);
        current = current->next;
    }
    return (true);
}