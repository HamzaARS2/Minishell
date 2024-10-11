
#include "../include/builtins.h"


int find_equal(char *str)
{
    int i;

    i = 0;
    while (str && str[i] && str[i] != '=')
        i++;
    if (str && str[i] != '=')
        return (-1);
    return (i);
}

bool    validate_arg(char *arg)
{
    int i;

    i = 0;
    if (arg[0] == '=' || ft_isdigit(arg[0]))
    {
        display_error("minishell: export: `", arg, "': not a valid identifier\n");
        return (false);
    }
    while (arg[i] && arg[i] != '=')
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
        {
            display_error("minishell: export: `", arg, "': not a valid identifier\n");
            return (false);
        }
        i++;
    }
    return (true);
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
    t_envlst    *new_env = NULL;
    int         i;

    i = 0;
    while (node->args[++i])
    {
        if (!validate_arg(node->args[i]))
            continue;
        if (env_update(env_is_exist(*envlst, node->args[i]), node->args[i]))
            continue;
        new_env = create_envlst(node->args[i]);
        if (!new_env)
            return (false);
        add_envlst(envlst, new_env);
    }
    return (true);
}