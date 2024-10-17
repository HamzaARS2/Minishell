/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:25:23 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 18:35:53 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	free_env_rm(t_envlst *env_rm)
{
	free(env_rm->key);
	free(env_rm->value);
	free(env_rm);
}

static bool	validate_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) || !arg[0])
	{
		display_error("minishell: unset: `", arg,
			"': not a valid identifier\n");
		return (false);
	}
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			display_error("minishell: unset: `", arg,
				"': not a valid identifier\n");
			return (false);
		}
		i++;
	}
	return (true);
}

t_envlst	*find_env(t_envlst **envlst, char *key)
{
	t_envlst	*current;

	current = *envlst;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	remove_env(t_envlst **envlst, t_envlst *env_rm)
{
	if (*envlst == env_rm)
	{
		*envlst = env_rm->next;
		if (*envlst)
			(*envlst)->prev = NULL;
		free_env_rm(env_rm);
		return (true);
	}
	env_rm->prev->next = env_rm->next;
	if (env_rm->next)
		env_rm->next->prev = env_rm->prev;
	free_env_rm(env_rm);
	return (true);
}

bool	mshell_unset(t_envlst **envlst, t_ast *node)
{
	t_envlst	*env_rm;
	int			i;
	bool		error;

	error = false;
	i = 0;
	while (node->args[++i])
	{
		if (!validate_arg(node->args[i]))
		{
			error = true;
			continue ;
		}
		env_rm = find_env(envlst, node->args[i]);
		if (!env_rm)
			continue ;
		if (remove_env(envlst, env_rm))
			break ;
	}
	return (!error);
}
