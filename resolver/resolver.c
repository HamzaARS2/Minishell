/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:51 by helarras          #+#    #+#             */
/*   Updated: 2024/08/29 15:39:14 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_resolver  *init_resolver(t_lexer *lexer)
{
    t_resolver *resolver;

    resolver = malloc(sizeof(t_resolver));
    if (!resolver)
        return (NULL);
    resolver->tokens = lexer->tokens;
    resolver->size = lexer->size;
    resolver->current = resolver->tokens;
    if (resolver->current)
        resolver->next = resolver->current->next;
    else
        resolver->next = NULL;
    return (resolver);
}

void    rslv_advance(t_resolver *resolver)
{
    if (!resolver->current || !resolver->next)
        return ;
    resolver->current = resolver->next;
    resolver->next = resolver->current->next;
}

void    rslv_merge(t_resolver *resolver)
{
    char *merged_value;

    merged_value = strcombine(resolver->current->value, resolver->next->value);
    resolver->current->value = merged_value;
    if (resolver->next->next)
        resolver->current->next = resolver->next->next;
    else
        resolver->current->next = NULL;
    free(resolver->next);
    resolver->next = resolver->current->next;
}


void    rslv_optimize(t_resolver *resolver)
{
    while (resolver->next)
    {
        while (urslv_should_merge(resolver))
            rslv_merge(resolver);
        rslv_advance(resolver);
    }
}
