#include "../include/execution.h"

void print_envlst(t_envlst *envlst)
{
    t_envlst *current  = envlst;
    int i  = 0;
    while (current)
    {
        printf("envlst%d: %s\n", i++, current->variable);
        current = current->next;
    }
}
char    *is_path(char *envvar)
{
    return (ft_strnstr(envvar, "PATH=", 5));
}
char    *get_path(t_envlst *envlst)
{
    t_envlst    *current;
    char *path;

    current = envlst;
    while (current)
    {
        path = is_path(current->variable);
        if (path)
            return (path + 5);
        current = current->next;
    }
    perror("$PATH not found\n");
    return (NULL);
}
void    ast_advance(t_ast **ast)
{
    t_ast *current;
    t_ast *left;
    t_ast *right;


    current = *ast;
    printf("ast->type%u\n", (*ast)->type);



}
void    join_cmd(char ***dirs, t_ast *ast)
{
    int i = 0;

    while((*dirs)[i])
    {
        (*dirs)[i] = strcombine(cmd_strcombine(((*dirs)[i]), "/"), ast->args[0]);
        printf("**dirs: %s\n", (*dirs)[i]);
        i++;
    }
}
void    expand_cmd(t_ast **ast, t_envlst *envlst)
{
    char    *path;
    char    **dirs;

    // print_envlst(envlst);


    path = get_path(envlst);
    printf("path:%s\n", path);
    
    //split with ":";
    dirs = ft_split(path, ':');
    if (dirs == NULL) {
        fprintf(stderr, "Error: Failed to split path.\n");
        return ;
    }
    char **str = dirs;
    int i = 0;
    while (*str)
    {
        printf("str:%s\n", *str);
        str++;
    }
    printf("before join\n");
    //add "/"
    join_cmd(&dirs, *ast);

    //add CMD
    //replace the tree args;
    //check cmd access




}
