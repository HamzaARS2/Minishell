// TODO: search adapter

// (1) *fix the structure with the strcombine thing : (√)
// (2) *Using relative paths.                       : (√)
// (3) *xecuting directories.                       : ()                    
// (4) *check LEAKS(),                              : ()
// Checking commands without a path or when PATH is empty.


#include "../include/execution.h"
#include <sys/stat.h>





int i = 0;

int check_access(char *path)
{
    int status;

    status = 0;
    //check dir :return 3;
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

char    *expnd_cmd_path(char *path, char *cmd)
{
    //  i have PATH;

    //  check is it already a relitive_path
    if (ft_strchr(cmd, '/'))
        return cmd;

    //  need to join CMD 2 PATH
    char    *cmd_slash;
    char    *rtrn_path;

    cmd_slash = strcombine(path, "/", false); // (|) *FREE CMD_SLASH ////****// *FREE() (1) FREE_PATH  (2) FREE_CMD(AST->ARG)
    printf("cmd_slash :%s\n", cmd_slash);
    
    rtrn_path = strcombine(cmd_slash, cmd, false);
    
    free(cmd_slash);

    //  return the CMD_PATH(to check it with ACCESS())

    return(rtrn_path);


}

void    err_write(char *bash, char *cmd, char *err, int status)
{
    // ft_write(bash);
    write(2, bash, ft_strlen(bash));
    write(2, cmd, ft_strlen(cmd));
    write(2, err, ft_strlen(err));
    exit(status);

}
// int is_directory(char *path)
// {
//     struct stat p_stat;

//     if stat(path, stat);

    

// }

char    *check_cmd(char **paths, char *cmd)
{
    char    *cmd_path;
    int     i = 0;
    int     status;

    status = 0;
    while(paths && (paths)[i])
    {
        cmd_path = expnd_cmd_path(paths[i], cmd);
        printf("cmd_path :%s\n", cmd_path);
        // if (is_directory(cmd_path))
        //     err_wirte();
        status = check_access(cmd_path);
        printf("status :%d\n", status);
        if (!status)
            return (cmd_path);
        else if(status == 1)
            err_write("bash: ", cmd_path, ": Permission denied\n", 126);
        i++;
    }
    if (status == 4)
        err_write("bash: ", cmd, ": No such file or directory\n", 127);
    printf("TEST\n");
    if (status == 2)
        err_write("bash: ", cmd, ": command not found\n", 127);
    return(NULL);
}

char    *cmd_expand(char *cmd, char **paths)
{
    char    *check_return = 0;

    check_return = check_cmd(paths, cmd);
    // system("leaks -q minishell"); //**LEAKS TEST**//=
    return(check_return);  //add "/"  //add CMD
}
