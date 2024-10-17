/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:23:28 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 20:23:29 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <signal.h>

int		g_signal;

void	on_new_line(t_mshell *mshell, char *line)
{
	if (!mshell_parse(mshell, line))
	{
		free(mshell->lexer->content);
		free_token_list(mshell->lexer->tokens);
		free(mshell->lexer);
		free(mshell->handler);
		return ;
	}
	mshell_execute(mshell);
	mshell_clean(mshell);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_signal = 131;
	}
}

void	display_prompt(t_mshell *mshell)
{
	char	*line;

	while (true)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell > ");
		if (g_signal)
		{
			mshell->ex_status = g_signal;
			g_signal = 0;
		}
		if (line)
		{
			add_history(line);
			on_new_line(mshell, line);
		}
		else
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_mshell	mshell;

	(void)ac;
	(void)av;
	init_mshell(&mshell, env);
	display_prompt(&mshell);
	return (mshell.ex_status);
}
