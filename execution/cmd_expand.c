#include "../include/execution.h"

int i = 0;

int check_access(char *path)
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
        cmd_tmp = ft_strdup(cmd); //TODO : NEEDS OPTIMISATION

        printf("*paths: %s\n", (paths)[i]);



        //access_check ----
        status = check_access((paths)[i]);
        printf("status :%d\n", status);
        if (!status)
        {
            free(cmd_tmp);
            return (paths[i]);
        }
        else if(status == 1)
        {
            printf("bash: %s: Permission denied\n", paths[i]);
            exit(126);
        }
        i++;
    }
    free(cmd_tmp);
    if (!status)
    {
        printf("bash: %s: No such file or directory\n", cmd);
        exit(127);
    }
    printf("TEST\n");
    if (status == 2)
    {
        printf("bash: %s: command not found\n", cmd);//************* HERE SHOULD PRINT COMMAND NOT FOUND
        exit(127);
    }
    // system("leaks -q minishell"); //**LEAKS TEST**//
    return(NULL);
}

char    *cmd_expand(char *cmd, char **paths)
{
    char    *check_return = 0;

    check_return = check_cmd(paths, cmd);
    // system("leaks -q minishell"); //**LEAKS TEST**//=
    return(check_return);  //add "/"  //add CMD
}
