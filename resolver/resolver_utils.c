/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:34:55 by helarras          #+#    #+#             */
/*   Updated: 2024/08/31 12:06:24 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool    urslv_should_merge(t_resolver *resolver)
{
    if (!resolver->current || !resolver->next)
        return (false);
    if ((resolver->current->state == IN_DQUOTES || resolver->current->state == IN_SQUOTES 
        || resolver->current->type == WORD) && (resolver->next->state == IN_DQUOTES
        || resolver->next->state == IN_SQUOTES || resolver->next->type == WORD
        || resolver->next->type == VARIABLE))
            return (true);
    return (false);
}

bool    urslv_should_expand(t_resolver *resolver)
{
    t_token *current;

    current = resolver->current;
    if (!current)
        return (false);
    return (current->type == VARIABLE && current->state != IN_SQUOTES);
}

void    urslv_expand_variable(t_resolver *resolver)
{
    uint32_t    i;
    uint32_t    varsize;
    char        *variable;
    char        **env;
    
    i = 0;
    env = resolver->env;
    variable = resolver->current->value + 1;
    varsize = ft_strlen(variable);
    while (env[i])
    {
        if (!ft_strncmp(env[i], variable, varsize))
        {
            free(resolver->current->value);
            resolver->current->value = ft_strdup(env[i] + varsize + 1);
            return ;
        }
        i++;
    }
    free(resolver->current->value);
    resolver->current->value = NULL;
}

void    urslv_reset(t_resolver *resolver)
{
    resolver->current = resolver->tokens;
    if (resolver->current)
        resolver->next = resolver->current->next;
}