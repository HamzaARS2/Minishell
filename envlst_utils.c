/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:32:45 by helarras          #+#    #+#             */
/*   Updated: 2024/10/09 13:14:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char    *get_env_value(t_envlst *envlst, char *variable)
{
    t_envlst *current;
    uint32_t varsize;

    varsize = ft_strlen(variable);
    current = envlst;
    while (current)
    {
        if (!ft_strncmp(current->variable, variable, varsize))
            return (current->variable + varsize + 1);
        current = current->next;
    }
    return (NULL);
}
