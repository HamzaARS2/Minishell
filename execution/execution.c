/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:11:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/26 10:40:19 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int count = 0;

void    exec_command(t_ast *node, t_context *ctx)
{
    pid_t pid;

    pid = fork();
    if (pid != 0)
    {
        count++;
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

void    exec_pipe(t_ast *node, t_context *ctx)
{
    int p[2];
    t_context lctx;
    t_context rctx;
    
    pipe(p);
    lctx = *ctx;
    lctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
    lctx.fd_close = p[STDIN_FILENO];
    exec_node(node->left, &lctx);
    rctx = *ctx;
    rctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
    rctx.fd_close = p[STDOUT_FILENO];
    exec_node(node->right, &rctx);
    close(p[STDIN_FILENO]);
    close(p[STDOUT_FILENO]);
}

void    exec_node(t_ast *node, t_context *ctx)
{
    if (node->type == AST_COMMAND)
        exec_command(node, ctx);
    else
        exec_pipe(node, ctx);
}

void    exec_ast(t_ast *ast)
{
    t_context ctx;
    
    ctx = (t_context) {{STDIN_FILENO, STDOUT_FILENO}, -1};
    exec_node(ast, &ctx);
    // printf("count: %i\n", count);
    // while (count--)
    // {
    //     printf("waiting...\n");
        wait(NULL);
        wait(NULL);
        wait(NULL);
    // }
}