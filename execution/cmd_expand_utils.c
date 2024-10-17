/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:20:50 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:26:26 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include <errno.h>

void	err_write(char *minishell, char *cmd, char *err, int status)
{
	if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	else
	{
		ft_putstr_fd(minishell, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(err, 2);
	}
	exit(status);
}
