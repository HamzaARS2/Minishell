/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:33:12 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:33:13 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/execution.h"

void	init_executor(t_executor *executor, t_envlst **envlst, int *ex_status)
{
	t_context	ctx;

	ctx = (t_context){{STDIN_FILENO, STDOUT_FILENO}, -1};
	executor->ctx = ctx;
	executor->ex_status = ex_status;
	executor->pids = NULL;
	executor->paths = get_paths(*envlst);
	executor->envlst = envlst;
}

void	dup_fds(t_context ctx)
{
	if (ctx.fd[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(ctx.fd[STDIN_FILENO], STDIN_FILENO);
		close(ctx.fd[STDIN_FILENO]);
	}
	if (ctx.fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(ctx.fd[STDOUT_FILENO], STDOUT_FILENO);
		close(ctx.fd[STDOUT_FILENO]);
	}
	if (ctx.close_fd != -1)
		close(ctx.close_fd);
}

void	run_command(t_ast *node, t_executor *executor)
{
	char			*path;
	t_builtins_type	type;

	type = builtin_check(node->args[0]);
	if (type == NONE)
	{
		dup_fds(executor->ctx);
		path = cmd_expand(node->args[0], executor->paths);
		execve(path, node->args, get_env(*executor->envlst));
		exit(EXIT_FAILURE);
	}
	else
	{
		if (exec_builtin(executor, node, type))
			exit(EXIT_SUCCESS);
		add_pid(&executor->pids, -1);
		exit(EXIT_FAILURE);
	}
}

void	exec_clean(t_executor *executor)
{
	int	i;

	i = 0;
	while (executor->paths[i])
		free(executor->paths[i++]);
	free(executor->paths);
}
