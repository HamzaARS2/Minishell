/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:44:53 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 20:06:04 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/resolver.h"

void	rslv_clean(t_resolver *resolver)
{
	t_token	*current;
	t_token	*temp;

	current = *resolver->tokens;
	while (current)
	{
		free(current->value);
		current->value = NULL;
		temp = current;
		current = current->next;
		free(temp);
		temp = 0;
	}
}

void	save_expand(t_resolver *resolver, char *env)
{
	free(resolver->current->value);
	if (!env[0] || is_only_spaces(env))
	{
		free(env);
		resolver->current->value = NULL;
	}
	else
		resolver->current->value = env;
}
