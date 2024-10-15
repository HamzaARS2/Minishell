/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:45 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/15 13:21:43 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

t_builtins_type	builtin_check(char *cmd)
{
	uint32_t	length;

	if (!cmd)
		return (NONE);
	length = ft_strlen(cmd);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	else if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	else if (!ft_strcmp(cmd, "env"))
		return (ENV);
	else if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	else if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	else if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
    else if (!ft_strcmp(cmd, "unset"))
        return (UNSET);
	return (NONE);
}
