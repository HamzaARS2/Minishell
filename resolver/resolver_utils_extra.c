/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:21:27 by helarras          #+#    #+#             */
/*   Updated: 2024/10/13 12:31:10 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/resolver.h"


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

void    urslv_insert_token(t_resolver *resolver, t_token *token)
{
    t_token *current;

    current = resolver->current;

    token->prev = current;
    token->next = current->next;

    if (current->next)
        current->next->prev = token;

    current->next = token;

    resolver->next = token;
}

void    urslv_handle_expanding(t_resolver *resolver, char *value)
{
    uint32_t    i;
    char        **env;

    i = 0;
    if (resolver->current->state == DEFAULT)
        env = ft_split(value, 32);
    else
        env = ft_split(value, 0);
    if (!env)
        return ;
    while (env[i])
    {
        if (i == 0)
        {
            free(resolver->current->value);
            resolver->current->value = env[i++];
            continue;    
        }
        urslv_insert_token(resolver, tkn_create_token(env[i], SPLIT_VAR));
        rslv_advance(resolver);
        i++;
    }
    free(env);
    env = 0;
}

void    urslv_expand_exstatus(t_resolver *resolver)
{
    free(resolver->current->value);
    resolver->current->value = ft_itoa(*resolver->ex_status);
}
