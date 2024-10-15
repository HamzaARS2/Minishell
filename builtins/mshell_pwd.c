#include "../include/builtins.h"

bool    mshell_pwd(t_executor *executor)
{
    char    *path;
    int     outfd;

    outfd = executor->ctx.fd[STDOUT_FILENO];
    path = getcwd(NULL, 0);
    if (!path)
    {
        perror("minishell : pwd");
        return (false); /* OR UPDATE THE EXIT_STATUS HERE */
    }
    ft_putstr_fd(path, outfd);
    ft_putstr_fd("\n", outfd);
    free(path);
    return (true);
}