/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:34:55 by helarras          #+#    #+#             */
/*   Updated: 2024/08/29 15:35:32 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool    urslv_should_merge(t_resolver *resolver)
{
    if (!resolver->current || !resolver->next)
        return (false);
    if ((resolver->current->state == IN_DQUOTES || resolver->current->type == WORD)
            && (resolver->next->state == IN_DQUOTES || resolver->next->type == WORD))
            return (true);
    return (false);
}