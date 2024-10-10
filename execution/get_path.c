#include "../include/execution.h"


void print_dpointer(char **dirs)
{
    while (*dirs)
    {
        printf("dp :%s\n", *dirs);
        dirs++;
    }
}
void print_envlst(t_envlst *envlst)
{
    t_envlst *current  = envlst;
    int i  = 0;
    while (current)
    {
        printf("envlst%d: %s\n", i++, current->value);
        current = current->next;
    }
}

//***** ^TOOLS ******************************************
//*******************************************************
char    *is_path(t_envlst *env)
{
    if (ft_strcmp(env->key, "PATH"))
        return (NULL);
    return (env->value + 1);
}


char    *get_path(t_envlst *envlst)
{
    t_envlst    *current;
    char *path;

    current = envlst;
    while (current)
    {
        path = is_path(current);
        if (path)
            return (path + 5);
        current = current->next;
    }
    perror("$PATH not found");//
    return (NULL);
}


char    **get_paths(t_envlst *envlst)
{
    char    *path;
    char    **dirs;

    // print_envlst(envlst);


    path = get_path(envlst);
    if (!path)
        return(NULL);

    // printf("path:%s\n", path);
    
    //split with ":";
    dirs = ft_split(path, ':');
    if (dirs == NULL) {
        fprintf(stderr, "Error: Failed to split path.\n");
        return NULL;
    }
    return (dirs);
    // print_dpointer(dirs); //TEST
    //check cmd access


    //replace the tree args;
    // rplace_tree_args(dirs, ast);

}