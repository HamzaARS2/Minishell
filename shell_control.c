/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:49:02 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 20:24:23 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"
#include "include/minishell.h"

extern int	g_signal;

void	init_mshell(t_mshell *mshell, char **env)
{
	mshell->envlst = init_envlst(env);
	mshell->ast = NULL;
	mshell->lexer = NULL;
	mshell->handler = NULL;
	mshell->resolver = NULL;
	mshell->parser = NULL;
	mshell->ex_status = 0;
}

bool	mshell_parse(t_mshell *mshell, char *line)
{
	mshell->lexer = init_lexer(line, true);
	lxr_generate_tokens(mshell->lexer);
	mshell->handler = init_handler(mshell->lexer, &mshell->ex_status);
	if (!hdl_run_quotes_check(mshell->handler))
		return (false);
	if (!hdl_run_pipe_check(mshell->handler))
		return (false);
	if (!hdl_run_redirects_check(mshell->handler))
		return (false);
	mshell->resolver = init_resolver(mshell->lexer, mshell->envlst,
			&mshell->ex_status);
	rslv_expand(mshell->resolver, true);
	rslv_optimize(mshell->resolver);
	mshell->parser = init_parser(mshell->lexer->tokens);
	mshell->parser->ast = prsr_parse(mshell->parser);
	return (true);
}

void	mshell_execute(t_mshell *mshell)
{
	init_executor(&mshell->executor, &mshell->envlst, &mshell->ex_status);
	if (!hrdoc_collect(mshell->parser->ast, mshell->envlst, &mshell->ex_status))
	{
		mshell->ex_status = 1;
		return ;
	}
	if (mshell->ex_status == -2)
	{
		mshell_clean(mshell);
		exit(2);
	}
	exec(mshell->parser->ast, &(mshell->executor));
	ft_wait(&mshell->executor);
}

void	mshell_clean(t_mshell *mshell)
{
	free(mshell->lexer->content);
	rslv_clean(mshell->resolver);
	prsr_clean(mshell->parser);
	exec_clean(&mshell->executor);
	free(mshell->lexer);
	free(mshell->handler);
	free(mshell->resolver);
	free(mshell->parser);
}
