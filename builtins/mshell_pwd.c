/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:40:03 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 22:42:22 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

bool	mshell_pwd(t_executor *executor)
{
	char	*path;
	int		outfd;

	outfd = executor->ctx.fd[STDOUT_FILENO];
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("minishell : pwd");
		return (false);
	}
	ft_putstr_fd(path, outfd);
	ft_putstr_fd("\n", outfd);
	free(path);
	return (true);
}
