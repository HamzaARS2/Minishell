/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:11:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/30 10:12:19 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int count = 0;

void    exec_command(t_ast *node, t_executor *executor)
{
    pid_t pid;
    t_context *ctx;

    ctx = executor->ctx;
    pid = fork();
    if (pid != 0)
    {
        executor->status++;
        return ;
    }
    dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
    if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
        close(ctx->fd[STDIN_FILENO]);
    dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
    if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
        close(ctx->fd[STDOUT_FILENO]);
    if (ctx->fd_close >= 0)
        close(ctx->fd_close);
    execve(node->args[0], node->args, NULL);
    exit(1);
}

void    exec_pipe(t_ast *node, t_executor *executor)
{
    int p[2];
    t_context lctx;
    t_context rctx;
    
    pipe(p);
    lctx = *executor->ctx;
    rctx = *executor->ctx;
    lctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    if (lctx.fd_close >= 0)
        close(lctx.fd_close);
    lctx.fd_close = p[STDIN_FILENO];
    executor->ctx = &lctx;
    exec_node(node->left, executor);
    rctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    rctx.fd_close = p[STDOUT_FILENO];
    executor->ctx = &rctx;
    exec_node(node->right, executor);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
}

void    exec_node(t_ast *node, t_executor *executor)
{
    if (node->type == AST_COMMAND)
        exec_command(node, executor);
    else
        exec_pipe(node, executor);
}

void    exec_ast(t_ast *ast)
{
    t_context ctx;
    t_executor executor;
    
    ctx = (t_context) {{STDIN_FILENO, STDOUT_FILENO}, -1};
    executor = (t_executor) {&ctx, 0};
    exec_node(ast, &executor);

    while (executor.status--)
        wait(NULL);
    
}