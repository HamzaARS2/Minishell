/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/29 21:53:46 by ajbari           ###   ########.fr       */
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

void    init_executor(t_executor *executor)
{
    executor->context.fd[0] = STDIN_FILENO;
    executor->context.fd[1] = STDOUT_FILENO;
    executor->context.close_fd = -1;
    executor->pids = NULL;

}
int    exec_cmd(t_ast *node, t_executor *executor)
{
    pid_t   pid;

    pid = fork();  
    //**TO DO: better protection for the execve (access());
    //
    if (pid == 0)
    {
        printf("CHILD executor->context.fd[0]: %d\n", executor->context.fd[STDIN_FILENO]);
        printf("CHILD executor->context.fd[1]: %d\n", executor->context.fd[STDOUT_FILENO]);
        printf("CHILD executor->context.close_fd : %d\n", executor->context.close_fd);
        
        dup2(executor->context.fd[STDIN_FILENO], STDIN_FILENO);
        dup2(executor->context.fd[STDOUT_FILENO], STDOUT_FILENO);

        if (executor->context.close_fd != -1)
            close(executor->context.close_fd);
        int retur = execve(node->args[0], node->args, NULL);
        printf("execve failef\n");
        return 0 ;
    }
    // if (pid != 0)
    //     wait(NULL);
    return 1;
}
int    exec_pipe(t_ast *ast, t_executor *executor)
{
    //assigning left 
    //assigning right
    t_ast   *left;
    t_ast   *right;

    t_context l_ctx = executor->context;
    t_context r_ctx = executor->context;

    int child = 0;
    int p[2];

    left  = ast->left;
    right = ast->right;
        //pipe()
    pipe(p);
    
    //asign in CONTEXT  
    l_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    if (l_ctx.close_fd != STDOUT_FILENO && l_ctx.close_fd != STDIN_FILENO)
    l_ctx.close_fd = p[STDIN_FILENO];
    executor->context = l_ctx;
    
    //execute LEFT  by calling EXEC_TREE()
    child += exec_tree(left, executor); 

    //reinitializing the context
    r_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    r_ctx.close_fd = p[STDOUT_FILENO];
    executor->context = r_ctx;

    //execute RIGHT by calling EXEC_TREE()
    child += exec_tree(right, executor);

    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
    return child;
}


int    exec_tree(t_ast *ast, t_executor *executor)
{
    if (ast->type == AST_COMMAND)
        return (exec_cmd(ast, executor));
    if (ast->type == AST_PIPE)
        return (exec_pipe(ast, executor));
    else 
        return 0;

}
void   exec(t_ast *ast)
{
    t_executor  executor;

    init_executor(&executor);
    
    int childs = exec_tree(ast, &executor);
    int i = 0 ;
    while (i++ < childs)
    {
        printf("i :%d\n", i);
        printf("childs : %d\n", childs);
        wait(NULL);
    }
}