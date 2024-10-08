

#include "../include/builtins.h"

bool    cd(char **args)
{
    if (args[2])
    {
        printf("minishell: cd: too many arguments\n");
        return (false);
    }
    if (chdir(args[1]) != 0)
    {
        perror("minishell: ");
        return (false);
    }
    char *cwd = getcwd(NULL, 0);
    printf("cwd: %s\n", cwd);
    return (true);
}