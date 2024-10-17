/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:38:46 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:48:51 by ajbari           ###   ########.fr       */
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
		else
			ft_putstr_fd("ambiguous redirect\n", 2);
		return (-1);
	}
	return (fd);
}

int	update_ctx(int *ctx_fd, int fd)
{
	if (*ctx_fd != STDOUT_FILENO && *ctx_fd != STDIN_FILENO && *ctx_fd != fd)
	{
		close(*ctx_fd);
	}
	*ctx_fd = fd;
	return (fd);
}

int	check_redirect(t_context *ctx, t_redirect *redirect)
{
	int	fd;
	int	in_red;
	int	out_red;
	int	append;

	fd = 0;
	in_red = O_RDONLY;
	out_red = O_CREAT | O_TRUNC | O_RDWR;
	append = O_CREAT | O_APPEND | O_RDWR;
	if (redirect->type == AST_IN_RED)
		fd = update_ctx(&(ctx->fd[0]), open_redirect(redirect->content,
					in_red));
	else if (redirect->type == AST_OUT_RED)
		fd = update_ctx(&(ctx->fd[1]), open_redirect(redirect->content,
					out_red));
	else if (redirect->type == AST_APPEND)
		fd = update_ctx(&(ctx->fd[1]), open_redirect(redirect->content,
					append));
	else if (redirect->type == AST_HEREDOC || redirect->type == AST_INQ_HEREDOC)
		fd = update_ctx(&(ctx->fd[0]), redirect->heredoc_fd);
	return (fd);
}

int	hndl_redirect(t_ast *ast, t_context *ctx)
{
	t_redirect	*redirect;
	int			fd;

	fd = -2;
	redirect = ast->redirect;
	while (redirect)
	{
		fd = check_redirect(ctx, redirect);
		if (fd == -1)
			break ;
		redirect = redirect->next;
	}
	return (fd);
}
