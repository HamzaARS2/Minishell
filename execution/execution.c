/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 12:09:26 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/execution.h"

extern int	g_signal;

void	child_sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_signal = 131;
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 130;
	}
}

bool	exec_cmd(t_ast *node, t_executor *executor)
{
	pid_t	pid;

	signal(SIGQUIT, &child_sig_handler);
	// signal(SIGINT, &child_sig_handler);
	pid = fork();
	if (pid == -1)
	{
		add_pid(&(executor->pids), -1);
		perror("minishell: fork: Resource temporarily unavailable");
		return (false);
	}
	if (pid != 0)
	{
		add_pid(&(executor->pids), pid);
		return (true);
	}
	run_command(node, executor);
	return (true);
}

void	exec_pipe(t_ast *ast, t_executor *executor)
{
	t_context	l_ctx;
	t_context	r_ctx;
	int			p[2];

	l_ctx = executor->ctx;
	r_ctx = executor->ctx;
	if (pipe(p) == -1)
	{
		*executor->ex_status = EXIT_FAILURE;
		perror("minishell: pipe error:");
		return ;
	}
	l_ctx.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	// if (r_ctx.close_fd != -1)
	//     close (r_ctx.close_fd);
	l_ctx.close_fd = p[STDIN_FILENO];
	executor->ctx = l_ctx;
	if (!exec_tree(ast->left, executor))
		return ;
	r_ctx.fd[STDIN_FILENO] = p[STDIN_FILENO];
	r_ctx.close_fd = p[STDOUT_FILENO];
	executor->ctx = r_ctx;
	exec_tree(ast->right, executor);
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);
}

bool	exec_tree(t_ast *ast, t_executor *executor)
{
	int	fd;

	if (ast->type == AST_COMMAND)
	{
		fd = hndl_redirect(ast, &executor->ctx);
		if (fd == -1)
		{
			add_pid(&executor->pids, -1);
			return (false);
		}
		if (!exec_cmd(ast, executor))
			return (false);
		if (fd != -2)
			close(fd);
	}
	else if (ast->type == AST_PIPE)
		exec_pipe(ast, executor);
	return (true);
}

void	exec(t_ast *ast, t_executor *executor)
{
	t_builtins_type type;
	int fd;

	type = NONE;
	if (ast->type == AST_COMMAND)
		type = builtin_check(ast->args[0]);
	if (type != NONE)
	{
		fd = hndl_redirect(ast, &executor->ctx);
		if (fd == -1)
			add_pid(&executor->pids, -1);
		else
		{
			if (!exec_builtin(executor, ast, type))
				add_pid(&executor->pids, -1);
			else
				*executor->ex_status = 0;
			if (fd > 0)
				close(fd);
		}
	}
	else
		exec_tree(ast, executor);
	ft_wait(executor);
}