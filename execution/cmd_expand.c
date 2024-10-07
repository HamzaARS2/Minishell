#include "../include/execution.h"

int i = 0;

int check_access(char *path, char *cmd)
{
    int status;

    status = 0;
    printf("%d\n", i++);
    if (access(path, F_OK) == 0)
    {
        if (access(path, X_OK) == 0)
            return (status);
        else
        {
            status = 1;
            return (status);
        }
    }
    else
    {
        status = 2;
        return (status);
    }
}

char    *check_cmd(char **paths, char *cmd)
{
    int     i = 0;
    int     status = 0;
    char    *cmd_tmp = ft_strdup(cmd);

    while(paths && (paths)[i])
    {
        (paths)[i] = strcombine(strcombine((paths)[i], ft_strdup("/")), cmd_tmp);
        printf("*paths: %s\n", (paths)[i]);
        cmd_tmp = ft_strdup(cmd); //TODO : NEEDS OPTIMISATION
        //access_check ----
        status = check_access((paths)[i], cmd);
        if (!status)
        {
            free(cmd_tmp);
            return (paths[i]);
        }
        i++;
    }
    free(cmd_tmp);
    if (status == 1)
        perror("bash: ");
    else if (status == 2)
        perror("bash1:");
    // system("leaks -q minishell"); //**LEAKS TEST**//
    return(NULL);
}

char    *cmd_expand(char *cmd, char **paths)
{
    char    *check_return = 0;

    if (!paths)
        return (NULL);


    check_return = check_cmd(paths, cmd);
    // system("leaks -q minishell"); //**LEAKS TEST**//=
    return(check_return);  //add "/"  //add CMD
}
