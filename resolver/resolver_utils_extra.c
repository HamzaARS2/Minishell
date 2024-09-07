/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:21:27 by helarras          #+#    #+#             */
/*   Updated: 2024/09/07 16:21:47 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    urslv_remove_spaces(t_resolver *resolver)
{
    t_token **head;
    t_token *current;

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
            {  
                current->prev->next = current->next;
                if (current->next)
                    current->next->prev = current->prev;
            }
            free_token(current);
        }
        current = current->next;
    }
}
