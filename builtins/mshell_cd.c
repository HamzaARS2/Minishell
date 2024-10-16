/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:37:13 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/15 17:20:10 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	print_errors(char flag, char *path)
{
	if (flag == 'H')
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (flag == 'P')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		perror(" ");
	}
}

char	*get_home_path(t_envlst *envlst)
{
	char	*home_path;

	home_path = get_env_value(envlst, "HOME");
	if (!home_path)
		print_errors('H', NULL);
	return (home_path);
}

void	change_pwd_env(t_envlst *envlst, char *key, char *pwd)
{
	t_envlst	*current;

	current = envlst;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = strcombine("=", pwd, false);
			free(pwd);
			break ;
		}
		current = current->next;
	}
}

bool	mshell_cd(char **args, t_envlst *envlst)
{
	char	*path;
	char	*old_path;

	if (!args[1])
		path = get_home_path(envlst);
	else
		path = args[1];
	if (!path)
		return (false);
	old_path = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		print_errors('P', path);
		free(old_path);
		return (false);
	}
	change_pwd_env(envlst, "OLDPWD", old_path);
	change_pwd_env(envlst, "PWD", getcwd(NULL, 0));
	return (true);
}
