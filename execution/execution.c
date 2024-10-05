/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/03 15:53:18 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"


void    init_executor(t_executor *executor)
{
    t_context ctx;

    ctx = (t_context) {{STDIN_FILENO, STDOUT_FILENO}, -1};
    executor->ctx = ctx;
    executor->status = 0;
    executor->pids = NULL;

}

void    exec_cmd(t_ast *node, t_executor *executor)
{
    pid_t   pid;

    pid = fork();  
    if (pid != 0)
    {
        add_pid(&(executor->pids), pid);
        return ;
    }
    if (executor->ctx.fd[STDIN_FILENO] != STDIN_FILENO) {
        dup2(executor->ctx.fd[STDIN_FILENO], STDIN_FILENO);
        close(executor->ctx.fd[STDIN_FILENO]);
    }
    if (executor->ctx.fd[STDOUT_FILENO] != STDOUT_FILENO) {
        dup2(executor->ctx.fd[STDOUT_FILENO], STDOUT_FILENO);
        close(executor->ctx.fd[STDOUT_FILENO]);
    }
    if (executor->ctx.close_fd != -1)
        close(executor->ctx.close_fd);
    execve(node->args[0], node->args, NULL);
    perror("EXECVE FAILED");
    exit(23);
}
void    exec_pipe(t_ast *ast, t_executor *executor)
{
    t_context l_ctx;
    t_context r_ctx;
    int p[2];

    l_ctx = executor->ctx;
    r_ctx = executor->ctx;
    pipe(p);
    l_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    if (r_ctx.close_fd != -1)
        close (r_ctx.close_fd);
    l_ctx.close_fd = p[STDIN_FILENO];
    executor->ctx = l_ctx;
    exec_tree(ast->left, executor); 
    r_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    r_ctx.close_fd = p[STDOUT_FILENO];
    executor->ctx = r_ctx;
    exec_tree(ast->right, executor);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
}


void    exec_tree(t_ast *ast, t_executor *executor)
{
    int fd;
    if (ast->type == AST_COMMAND)
    {
        fd = hndl_redirect(ast, &executor->ctx); //HANDLE REDIRECTIONS
        exec_cmd(ast, executor);
        if (fd != -1)
            close (fd);
    }
    if (ast->type == AST_PIPE)
        exec_pipe(ast, executor);

}
void   exec(t_ast *ast, t_executor *executor)
{

    exec_tree(ast, executor);

    // print_pids(executor->pids, 2);    //TESTING : printing the pids list;
    ft_wait(executor);

    printf("STATUS: %d\n", executor->status);
}