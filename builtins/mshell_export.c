/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:39:55 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 20:08:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str && str[i] != '=')
		return (-1);
	return (i);
}

bool	validate_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg[0] || arg[0] == '=' || ft_isdigit(arg[0]))
	{
		display_error("minishell: export: `", arg,
			"': not a valid identifier\n");
		return (false);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			display_error("minishell: export: `", arg,
				"': not a valid identifier\n");
			return (false);
		}
		i++;
	}
	return (true);
}

t_envlst	*env_is_exist(t_envlst *envlst, char *new_env)
{
	t_envlst	*current;
	int			keylen;
	int			newlen;

	current = envlst;
	while (current)
	{
		keylen = ft_strlen(current->key);
		newlen = find_equal(new_env);
		if (newlen == -1)
			newlen = ft_strlen(new_env);
		if (keylen == newlen && !ft_strncmp(current->key, new_env, newlen))
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	env_update(t_envlst *env, char *new_env)
{
	char	*update_value;

	if (!env)
		return (false);
	if (find_equal(new_env) == -1)
		return (true);
	update_value = ft_strchr(new_env, '=');
	if (!update_value)
		return (false);
	update_value = ft_strdup(update_value);
	free(env->value);
	env->value = update_value;
	return (true);
}

bool	mshell_export(t_executor *executor, t_ast *node)
{
	t_envlst	*new_env;
	int			i;
	bool		error;

	error = false;
	i = 0;
	if (!node->args[1])
		print_env(*executor->envlst, executor->ctx.fd[STDOUT_FILENO], false);
	while (node->args[++i])
	{
		if (!validate_arg(node->args[i]))
		{
			error = true;
			continue ;
		}
		if (env_update(env_is_exist(*executor->envlst, node->args[i]),
				node->args[i]))
			continue ;
		new_env = create_envlst(node->args[i]);
		if (!new_env)
			return (false);
		add_envlst(executor->envlst, new_env);
	}
	return (!error);
}
