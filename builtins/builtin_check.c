/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:30:45 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/14 20:38:15 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

t_builtins_type	builtin_check(char *cmd)
{
	uint32_t	length;

	length = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "cd", length) && ft_strlen(cmd) == 2)
		return (CD);
	else if (!ft_strncmp(cmd, "export", length) && ft_strlen(cmd) == 6)
		return (EXPORT);
	else if (!ft_strncmp(cmd, "env", length) && ft_strlen(cmd) == 3)
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", length) && ft_strlen(cmd) == 4)
		return (EXIT);
	else if (!ft_strncmp(cmd, "pwd", length) && ft_strlen(cmd) == 3)
		return (PWD);
	else if (!ft_strncmp(cmd, "echo", length) && ft_strlen(cmd) == 4)
		return (ECHO);
    else if (!ft_strncmp(cmd, "unset", length))
        return (UNSET);
	return (NONE);
}
