/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:35:46 by helarras          #+#    #+#             */
/*   Updated: 2024/10/07 09:39:11 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/token.h"

t_token	*get_last_token(t_token *token_list)
{
	while (token_list && token_list->next)
		token_list = token_list->next;
	return (token_list);
}

void	add_last_token(t_token *token_list, t_token *token_node)
{
	t_token	*current_last;

	current_last = get_last_token(token_list);
	if (!current_last)
		return ;
	current_last->next = token_node;
	token_node->prev = current_last;
}

bool	is_special_token(t_token *token)
{
	if ((token->type == SSPACE || token->type == PIPE || token->type == OUT_RED
			|| token->type == IN_RED || token->type == HERE_DOC
			|| token->type == APPEND) && token->state == DEFAULT)
		return (true);
	return (false);
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}
