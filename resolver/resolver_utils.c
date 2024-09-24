/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:34:55 by helarras          #+#    #+#             */
/*   Updated: 2024/09/24 16:23:53 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/resolver.h"

bool    urslv_should_merge(t_resolver *resolver)
{
    if (!resolver->current || !resolver->next)
        return (false);
    if ((resolver->current->state == IN_DQUOTES || resolver->current->state == IN_SQUOTES 
        || resolver->current->type == WORD || resolver->current->type == S_AND
        || resolver->current->type == VARIABLE)
        && (resolver->next->state == IN_DQUOTES || resolver->next->state == IN_SQUOTES
        || resolver->next->type == WORD || resolver->next->type == VARIABLE
        || resolver->next->type == S_AND))
            return (true);
    return (false);
}

bool    urslv_should_expand(t_resolver *resolver)
{
    t_token *current;

    current = resolver->current;
    if (!current)
        return (false);
    if (current->type == HERE_DOC)
        urslv_skip_heredoc_limiter(resolver);
    return (current->type == VARIABLE && current->state != IN_SQUOTES);
}

void    urslv_expand_variable(t_resolver *resolver)
{
    uint32_t    varsize;
    char        *variable;
    t_envlst    *current;
    
    current = resolver->envlst;
    variable = resolver->current->value + 1;
    varsize = ft_strlen(variable);
    while (current)
    {
        if (!ft_strncmp(current->variable, variable, varsize))
        {
            free(resolver->current->value);
            resolver->current->value = ft_strdup(current->variable + varsize + 1);
            return ;
        }
        current = current->next;
    }
    free(resolver->current->value);
    resolver->current->value = NULL;
}

void    urslv_skip_heredoc_limiter(t_resolver *resolver)
{
    rslv_advance(resolver);
    rslv_advance(resolver);
    while (resolver->current &&!is_special_token(resolver->current))
        rslv_advance(resolver);
}

void    urslv_reset(t_resolver *resolver)
{
    resolver->current = *(resolver->tokens);
    if (resolver->current)
        resolver->next = resolver->current->next;
}
