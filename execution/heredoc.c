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

pid_t	hrdoc_prepare(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid != 0)
	{
		wait(NULL);
		return (pid);
	}
	signal(SIGINT, uhrdoc_sig_handler);
	return (0);
}

void	hrdoc_run(t_redirect *heredoc, t_envlst *envlst, int *ex_status)
{
	int		p[2];
	char	*line;

	if (hrdoc_prepare() != 0)
		return ;
	pipe(p);
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
	close(p[1]);
	heredoc->heredoc_fd = p[0];
}

void	hrdoc_search(t_redirect *redirect, t_envlst *envlst, int *ex_status)
{
	t_redirect	*current;

	current = redirect;
	while (current)
	{
		if (current->type == AST_HEREDOC || current->type == AST_INQ_HEREDOC)
			hrdoc_run(current, envlst, ex_status);
		current = current->next;
	}
}

void	hrdoc_collect(t_ast *node, t_envlst *envlst, int *ex_status)
{
	if (node->type == AST_PIPE)
	{
		hrdoc_collect(node->left, envlst, ex_status);
		hrdoc_collect(node->right, envlst, ex_status);
	}
	else if (node->type == AST_COMMAND)
		hrdoc_search(node->redirect, envlst, ex_status);
}
