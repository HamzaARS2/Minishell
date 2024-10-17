/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:35:51 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:36:56 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

extern int	g_signal;

char	*hrdoc_expand(t_envlst *envlst, char *line, int *ex_status)
{
	t_lexer		*lexer;
	t_resolver	*resolver;
	char		*newline;

	if (!uhrdoc_env_exist(line))
		return (line);
	lexer = init_lexer(line, false);
	lxr_generate_tokens(lexer);
	resolver = init_resolver(lexer, envlst, ex_status);
	rslv_expand(resolver, false);
	newline = uhrdoc_join_tokens(lexer->tokens, uhrdoc_get_size(lexer->tokens));
	uhrdoc_clear(lexer, resolver, line);
	return (newline);
}

int	hrdoc_prepare(t_redirect *heredoc, int p[2], int *ex_status)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (pipe(p) == -1)
		return (print_error(ex_status, 2,
				"minishell: maximum here-document count exceeded\n"));
	pid = fork();
	if (pid == -1)
		return (print_error(ex_status, 1,
				"minishell: fork: Resource temporarily unavailable\n"));
	if (pid != 0)
	{
		waitpid(pid, ex_status, 0);
		*ex_status = WEXITSTATUS(*ex_status);
		if (*ex_status)
			g_signal = 1;
		close(p[1]);
		heredoc->heredoc_fd = p[0];
		return (pid);
	}
	signal(SIGINT, uhrdoc_sig_handler);
	return (0);
}

int	hrdoc_run(t_redirect *heredoc, t_envlst *envlst, int *ex_status)
{
	int		p[2];
	char	*line;
	int		result;

	result = hrdoc_prepare(heredoc, p, ex_status);
	if (result != 0)
		return (result);
	while (true)
	{
		line = readline("heredoc > ");
		if (!line)
			break ;
		if (!ft_strcmp(line, heredoc->content))
			break ;
		line = strcombine(line, ft_strdup("\n"), true);
		if (!line)
			break ;
		if (heredoc->type == AST_HEREDOC)
			line = hrdoc_expand(envlst, line, ex_status);
		write(p[1], line, ft_strlen(line));
		free(line);
	}
	ft_close_pipe(p);
	exit(0);
	return (0);
}

void	hrdoc_search(t_redirect *redirect, t_envlst *envlst, int *ex_status)
{
	t_redirect	*current;

	current = redirect;
	while (current)
	{
		if (current->type == AST_HEREDOC || current->type == AST_INQ_HEREDOC)
		{
			if (hrdoc_run(current, envlst, ex_status) == -1)
				break ;
		}
		if (g_signal)
			break ;
		current = current->next;
	}
}

bool	hrdoc_collect(t_ast *node, t_envlst *envlst, int *ex_status)
{
	if (node->type == AST_PIPE)
	{
		if (!hrdoc_collect(node->left, envlst, ex_status))
			return (false);
		if (!hrdoc_collect(node->right, envlst, ex_status))
			return (false);
	}
	else if (node->type == AST_COMMAND)
		hrdoc_search(node->redirect, envlst, ex_status);
	if (*ex_status && g_signal)
	{
		g_signal = 0;
		return (false);
	}
	return (true);
}
