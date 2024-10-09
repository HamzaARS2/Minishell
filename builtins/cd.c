

#include "../include/builtins.h"

bool    cd(char **args)
{
    if (args[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (false);
    }
    if (chdir(args[1]) != 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(args[1], 2);
        perror("");
        return (false);
    }
    char *cwd = getcwd(NULL, 0);
    printf("cwd: %s\n", cwd);
    return (true);
}