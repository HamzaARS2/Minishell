/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:19:39 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/14 12:19:40 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

bool	mshell_env(t_envlst *envlst)
{
	t_envlst	*current;

	current = envlst;
	if (!current)
		return (false);
	while (current)
	{
		printf("%s%s\n", current->key, current->value);
		current = current->next;
	}
	return (true);
}
