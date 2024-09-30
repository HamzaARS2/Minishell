/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/30 13:12:49 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"


void    init_executor(t_executor *executor)
{
    t_pids *pids = NULL;
    executor->context.fd[0] = STDIN_FILENO;
    executor->context.fd[1] = STDOUT_FILENO;
    executor->context.close_fd = -1;
    executor->pids = NULL;

}
void    exec_cmd(t_ast *node, t_executor *executor)
{
    pid_t   pid;

    pid = fork();  
    if (pid != 0)
    {
        
        executor->status++;
        return ;
    }
    if (executor->context.fd[STDIN_FILENO] != STDIN_FILENO) {
        dup2(executor->context.fd[STDIN_FILENO], STDIN_FILENO);
        close(executor->context.fd[STDIN_FILENO]);
    }
    if (executor->context.fd[STDOUT_FILENO] != STDOUT_FILENO) {
        dup2(executor->context.fd[STDOUT_FILENO], STDOUT_FILENO);
        close(executor->context.fd[STDOUT_FILENO]);
    }
    if (executor->context.close_fd != -1)
        close(executor->context.close_fd);
    execve(node->args[0], node->args, NULL);
    perror("execve failed\n");
}
void    exec_pipe(t_ast *ast, t_executor *executor)
{
    t_context l_ctx;
    t_context r_ctx;
    int p[2];

    l_ctx = executor->context;
    r_ctx = executor->context;
    pipe(p);
    l_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    if (r_ctx.close_fd != -1)
        close (r_ctx.close_fd);
    l_ctx.close_fd = p[STDIN_FILENO];
    executor->context = l_ctx;
    exec_tree(ast->left, executor); 
    r_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    r_ctx.close_fd = p[STDOUT_FILENO];
    executor->context = r_ctx;
    exec_tree(ast->right, executor);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
}


void    exec_tree(t_ast *ast, t_executor *executor)
{
    if (ast->type == AST_COMMAND)
        exec_cmd(ast, executor);
    if (ast->type == AST_PIPE)
        exec_pipe(ast, executor);

}
void   exec(t_ast *ast)
{
    t_executor  executor;

    init_executor(&executor);
    
    exec_tree(ast, &executor);
    while (executor.status--)
    {
        wait(NULL);
    }
}