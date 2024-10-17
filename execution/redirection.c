/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:38:46 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 16:36:39 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

int	open_redirect(char *path, int flag)
{
	int	fd;

    fd = open(path, flag, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        if (path)
            perror("");
        return (-1);
    }
    return (fd);
}


int	check_redirect(t_context *ctx, t_redirect *redirect)
{
	int	fd;
	int	in_red;
	int	out_red;
	int	append;

    in_red = O_RDONLY;
    out_red = O_CREAT | O_TRUNC | O_RDWR;
    append = O_CREAT | O_APPEND | O_RDWR;
    fd = -1;
    if (redirect->type == AST_IN_RED)
        fd = open_redirect(redirect->content, in_red);
    else if (redirect->type == AST_OUT_RED)
        fd = open_redirect(redirect->content, out_red);
    else if (redirect->type == AST_APPEND)
        fd = open_redirect(redirect->content, append);
    else if (redirect->type == AST_HEREDOC || redirect->type == AST_INQ_HEREDOC)
        fd = redirect->heredoc_fd;
    if (redirect->type == AST_OUT_RED || redirect->type == AST_APPEND)
        ctx->fd[1] = fd;
    else
        ctx->fd[0] = fd;
    return (fd);
}

void    check_closing_fds(t_context *ctx, t_ast_type last_type, t_ast_type current_type)
{
    if (ctx->fd[1] != 1 && (current_type == AST_OUT_RED || current_type == AST_APPEND)
            && (last_type == AST_OUT_RED || last_type == AST_APPEND))
            close(ctx->fd[1]);
    if (ctx->fd[0] != 0 && (current_type == AST_IN_RED || current_type == AST_HEREDOC || current_type == AST_INQ_HEREDOC)
        && (last_type == AST_IN_RED || last_type == AST_HEREDOC || last_type == AST_INQ_HEREDOC))
            close(ctx->fd[0]);
}

t_context   hndl_redirect(t_ast *ast, t_context *ctx)
{
    t_redirect  *redirect;
    int         fd;
    t_context   red_ctx;
    t_ast_type last_type;

    last_type = AST_PIPE;
    red_ctx = (t_context) {{-2, -2}, -1};
    redirect = ast->redirect;
    while (redirect)
    {
        check_closing_fds(ctx, last_type, redirect->type);
        fd = check_redirect(ctx, redirect);
        last_type = redirect->type;
        if (redirect->type == AST_OUT_RED || redirect->type == AST_APPEND)
            red_ctx.fd[1] = fd;
        else
            red_ctx.fd[0] = fd;
        if (red_ctx.fd[1] == -1 || red_ctx.fd[0] == -1)
            break;
        redirect = redirect->next;
    }
    return (red_ctx);
}
