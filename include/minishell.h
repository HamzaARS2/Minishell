/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:04:21 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:04:22 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ast.h"
# include "envlst.h"
# include "execution.h"
# include "handler.h"
# include "lexer.h"
# include "parser.h"
# include "resolver.h"
# include "token.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_mshell
{
	t_envlst	*envlst;
	t_ast		*ast;
	t_lexer		*lexer;
	t_handler	*handler;
	t_resolver	*resolver;
	t_parser	*parser;
	t_executor	executor;
	int			ex_status;
}				t_mshell;

void			init_mshell(t_mshell *mshell, char **env);

bool			mshell_parse(t_mshell *mshell, char *line);

void			mshell_execute(t_mshell *mshell);

void			mshell_clean(t_mshell *mshell);

void			display_prompt(t_mshell *mshell);

#endif