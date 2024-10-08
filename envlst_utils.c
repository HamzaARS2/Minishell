/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:32:45 by helarras          #+#    #+#             */
/*   Updated: 2024/10/10 10:28:31 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char    *get_env_value(t_envlst *envlst, char *key)
{
    t_envlst *current;

    current = envlst;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
            return (current->value + 1);
        current = current->next;
    }
    return (NULL);
}
