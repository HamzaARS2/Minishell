/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:14:33 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:26:42 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <errno.h>
#include <sys/stat.h>

int	is_directory(char *path)
{
	struct stat	p_stat;

	stat(path, &p_stat);
	if (S_ISDIR(p_stat.st_mode))
		return (1);
	return (0);
}

int	check_access(char *path)
{
	int	status;

	status = 0;
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (status);
		else
		{
			status = 1;
			return (status);
		}
	}
	else
	{
		status = 2;
		return (status);
	}
}

char	*expand_cmd_path(char *path, char *cmd)
{
	char	*cmd_slash;
	char	*rtrn_path;
	int		status;

	if (!cmd[0])
		return (NULL);
	if ((ft_strchr(cmd, '/') && is_directory(cmd)) || is_directory(cmd))
		err_write("minishell: ", cmd, ": is a directory\n", 126);
	if (ft_strchr(cmd, '/'))
	{
		status = check_access(cmd);
		if (status == 2)
			err_write("minishell: ", cmd, ": No such file or directory\n", 127);
		else if (status == 1)
			err_write("minishell: ", cmd, ": Permission denied\n", 126);
		return (cmd);
	}
	if (!path)
		return (NULL);
	cmd_slash = strcombine(path, "/", false);
	rtrn_path = strcombine(cmd_slash, cmd, false);
	free(cmd_slash);
	return (rtrn_path);
}

char	*check_cmd(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;
	int		status;

	i = 0;
	status = 0;
	cmd_path = NULL;
	if (!paths)
		cmd_path = expand_cmd_path(NULL, cmd);
	while (paths && (paths)[i])
	{
		cmd_path = expand_cmd_path(paths[i++], cmd);
		status = check_access(cmd_path);
		if (!status)
			return (cmd_path);
		else if (status == 1)
			err_write("minishell: ", cmd_path, ": Permission denied\n", 126);
	}
	if (status == 0 && !ft_strchr(cmd, '/'))
		err_write("minishell: ", cmd, ": No such file or directory\n", 127);
	if (status == 2)
		err_write("minishell: ", cmd, ": command not found\n", 127);
	return (cmd_path);
}

char	*cmd_expand(char *cmd, char **paths)
{
	char	*check_return ;

	check_return = 0;
	if (!cmd)
		exit(0);
	check_return = check_cmd(paths, cmd);
	return (check_return);
}
