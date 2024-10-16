/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:21:27 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 22:05:23 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/resolver.h"

extern int	g_signal;

void	urslv_remove_spaces(t_resolver *resolver)
{
	t_token	**head;
	t_token	*current;
	t_token	*temp;

	head = resolver->tokens;
	current = *head;
	while (current)
	{
		if (current->type == SSPACE && current->state == DEFAULT)
		{
			if (!current->prev)
			{
				*head = current->next;
				if (current->next)
					current->next->prev = NULL;
			}
			else
				change_links(current);
			temp = current;
			current = current->next;
			free_token(temp);
			continue ;
		}
		current = current->next;
	}
}

void	urslv_insert_token(t_resolver *resolver, t_token *token)
{
	t_token	*current;

	current = resolver->current;
	token->prev = current;
	token->next = current->next;
	if (current->next)
		current->next->prev = token;
	current->next = token;
	resolver->next = token;
}

char	**urslv_get_env_value(char *value)
{
	char	**env;

	env = NULL;
	if (value || !value[0] || is_only_spaces(value))
	{
		env = malloc(2 * sizeof(char *));
		env[0] = ft_strdup(value);
		env[1] = NULL;
	}
	else
		env = ft_split(value, 32);
	return (env);
}

void	urslv_handle_expanding(t_resolver *resolver, char *value)
{
	uint32_t	i;
	char		**env;

	i = 0;
	env = urslv_get_env_value(value);
	if (!env)
		return ;
	while (env[i])
	{
		if (i == 0)
		{
			save_expand(resolver, env[i]);
			i++;
			continue ;
		}
		urslv_insert_token(resolver, tkn_create_token(env[i], SPLIT_VAR));
		rslv_advance(resolver);
		i++;
	}
	free(env);
	env = 0;
}

void	urslv_expand_exstatus(t_resolver *resolver)
{
	free(resolver->current->value);
	resolver->current->value = ft_itoa(*resolver->ex_status);
}
