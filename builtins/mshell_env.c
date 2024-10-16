/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:19:39 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/15 09:51:22 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

bool	mshell_env(t_executor *executor)
{
	t_envlst	*envlst;
	int			outfd;

	envlst = *executor->envlst;
	outfd = executor->ctx.fd[STDOUT_FILENO];
	print_env(envlst, outfd, true);
	return (true);
}
