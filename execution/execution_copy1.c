/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/29 20:16:57 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"


// int    add_pid(t_executor *executor, pid_t pid)
// {
    
//     t_pids  *head;

//     t_pids  *new_node;

//     head = executor->pids;
    
//     new_node->pid = pid;
//     printf("test\n");

//     while (head)
//         head = head->next;

//     head = new_node;
//     new_node->next = NULL;
// }

// int i  = 0;

void    init_context(t_context *ctx)
{
    ctx->fd[0] = STDIN_FILENO;
    ctx->fd[1] = STDOUT_FILENO;
    ctx->close_fd = -1;
}
int    exec_cmd(t_ast *node, t_context *ctx)
{
    pid_t   pid;

    pid = fork();  
    //**TO DO: better protection for the execve (access());
    //
    if (pid == 0)
    {
        printf("ctx->fd[STDIN_FILENO]: %d\n", ctx->fd[STDIN_FILENO]);
        printf("ctx->fd[STDOUT_FILENO]: %d\n", ctx->fd[STDOUT_FILENO]);
        // Set up pipes
        if (ctx->fd[STDIN_FILENO] != STDIN_FILENO) {
            dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
            close(ctx->fd[STDIN_FILENO]);
        }
        if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO) {
            dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
            close(ctx->fd[STDOUT_FILENO]);
        }
        if (ctx->close_fd >= 0)
            close(ctx->close_fd);
        int retur = execve(node->args[0], node->args, NULL);
        printf("execve failef\n");
        return 0 ;
    }
    // if (pid != 0)
    //     wait(NULL);
    return 1;
}
int    exec_pipe(t_ast *ast, t_context *ctx)
{
    //assigning left 
    //assigning right
    t_ast   *left;
    t_ast   *right;

    t_context l_ctx = *ctx;
    t_context r_ctx = *ctx;

    int child = 0;
    int p[2];

    left  = ast->left;
    right = ast->right;
        //pipe()
    pipe(p);
    
    //asign in CONTEXT  
    l_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    if (l_ctx.close_fd != 0 && l_ctx.close_fd != 1)
        close(l_ctx.close_fd);
    l_ctx.close_fd = p[STDIN_FILENO];
    
    //execute LEFT  by calling EXEC_TREE()
    child += exec_tree(left, &l_ctx); 

    //reinitializing the context
    r_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];

    
    r_ctx.close_fd = p[STDOUT_FILENO];

    //execute RIGHT by calling EXEC_TREE()
    child += exec_tree(right, &r_ctx);
    close(p[STDOUT_FILENO]);
    close(p[STDIN_FILENO]);

    return child;
}


int    exec_tree(t_ast *ast,  t_context *ctx)
{
    if (ast->type == AST_COMMAND)
        return (exec_cmd(ast, ctx));
    if (ast->type == AST_PIPE)
        return (exec_pipe(ast, ctx));
    else 
        return 0;

}
void   exec(t_ast *ast)
{
    t_context   ctx;

    init_context(&ctx);
    
    int childs = exec_tree(ast, &ctx);
    for (int i = 0; i < childs ; ++i)
    {

        wait(NULL);
        printf("childs : %d\n", childs);
    }



}