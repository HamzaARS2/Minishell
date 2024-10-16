/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:59:16 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 07:59:17 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ast.h"
# include "envlst.h"
# include "execution.h"
# include <limits.h> //check is it allowed
# include <unistd.h>

typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE
}				t_builtins_type;

t_builtins_type	builtin_check(char *cmd);
bool			mshell_cd(char **args, t_envlst *envlst);
bool			mshell_export(t_executor *executor, t_ast *node);
bool			mshell_env(t_executor *executor);
bool			mshell_exit(t_executor *executor, char **arg);
bool			mshell_unset(t_envlst **envlst, t_ast *node);
bool			mshell_pwd(t_executor *executor);
bool			mshell_echo(t_executor executor, char **args);

bool			exec_builtin(t_executor *executor, t_ast *node,
					t_builtins_type type);

void			display_error(char *intro, char *body, char *conclusion);
#endif