#include "../include/execution.h"



void    join_cmd(char ***dirs, t_ast *ast)
{
    int i = 0;

    while((*dirs)[i])
    {
        (*dirs)[i] = strcombine(strcombine(((*dirs)[i]), ft_strdup("/")), ast->args[0]);
        //access_check ----
        printf("**dirs: %s\n", (*dirs)[i]);
        i++;
    }
}
// void    rplace_tree_args(char **dirs, t_ast **ast)
// {
//     if ((*ast)->left->type == AST_PIPE)
//         rplace_tree_args(dirs, )


// }

// char    **get_paths(t_envlst *envlst)
// {
//     char    *path;
//     char    **dirs;

//     // print_envlst(envlst);


//     path = get_path(envlst);
//     printf("path:%s\n", path);
    
//     //split with ":";
//     dirs = ft_split(path, ':');
//     if (dirs == NULL) {
//         fprintf(stderr, "Error: Failed to split path.\n");
//         return NULL;
//     }
//     return (dirs);
//     // printf("before join\n");
//     // join_cmd(&dirs, *ast);  //add "/"  //add CMD
//     // print_dpointer(dirs); //TEST
//     //check cmd access


//     //replace the tree args;
//     // rplace_tree_args(dirs, ast);

// }
