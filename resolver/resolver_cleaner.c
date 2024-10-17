/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:44:53 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 13:42:48 by ajbari           ###   ########.fr       */
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
