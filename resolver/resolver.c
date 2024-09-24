/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:51 by helarras          #+#    #+#             */
/*   Updated: 2024/09/24 15:22:23 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/resolver.h"

t_resolver  *init_resolver(t_lexer *lexer, t_envlst *envlst)
{
    t_resolver *resolver;

    resolver = malloc(sizeof(t_resolver));
    if (!resolver)
        return (NULL);
    resolver->tokens = &(lexer->tokens);
    resolver->size = lexer->size;
    resolver->envlst = envlst;
    resolver->current = *(resolver->tokens);
    if (resolver->current)
        resolver->next = resolver->current->next;
    else
        resolver->next = NULL;
    return (resolver);
}

void    rslv_advance(t_resolver *resolver)
{
    if (!resolver->current)
        return ;
    resolver->current = resolver->next;
    if (resolver->current)
        resolver->next = resolver->current->next;
    else
        resolver->next = NULL;
}

void rslv_merge(t_resolver *resolver)
{
    char *merged_value;

    merged_value = strcombine(resolver->current->value, resolver->next->value);
    resolver->current->value = merged_value;
    if (resolver->next->next)
    {
        resolver->current->next = resolver->next->next;
        resolver->next->next->prev = resolver->current;
    }
    else
        resolver->current->next = NULL;
    free(resolver->next);
    resolver->next = resolver->current->next;
}


void    rslv_expand(t_resolver *resolver)
{    
    if (!resolver->current)
        return ;
    while (resolver->current)
    {
        if (urslv_should_expand(resolver))
            urslv_expand_variable(resolver);
        rslv_advance(resolver);
    }
    urslv_reset(resolver);
}


void    rslv_optimize(t_resolver *resolver)
{
    while (resolver->current && resolver->next)
    {
        while (urslv_should_merge(resolver))
            rslv_merge(resolver);
        rslv_advance(resolver);
    }
    urslv_remove_spaces(resolver);
}
