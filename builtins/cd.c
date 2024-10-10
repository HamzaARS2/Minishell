

#include "../include/builtins.h"



static void    print_errors(char flag, char *path)
{
    if (flag == 'H')
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
    else if (flag == 'T')
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
    else if (flag == 'P')
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(path, 2);
        perror(" ");
    }
}

char    *get_home_path(t_envlst *envlst)
{
    char *home_path;

    home_path = get_env_value(envlst, "HOME");
    if (!home_path)
        print_errors('H', NULL);
    return (home_path);
}

bool    cd(char **args, t_envlst *envlst)
{
    char *path;

    if (args[1] && args[2])
    {
        print_errors('T', NULL);
        return (false);
    }
    if (!args[1])
        path = get_home_path(envlst);
    else
        path = args[1];
    if (!path)
        return (false);
    if (chdir(path) != 0)
    {
        print_errors('P', path);
        return (false);
    }
    return (true);
}