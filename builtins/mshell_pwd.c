#include "../include/builtins.h"

bool    mshell_pwd(char **args)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
    {
        perror("getwcd:");
        return (false); /* OR UPDATE THE EXIT_STATUS HERE */
    }
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
    free(path);
    return (true);
}