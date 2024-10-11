/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:32:45 by helarras          #+#    #+#             */
/*   Updated: 2024/10/11 10:48:59 by helarras         ###   ########.fr       */
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

char    **get_env(t_envlst *envlst)
{
    t_envlst    *current;
    int         size;
    char        **env;
    int         i;

    i = 0;
    size = 0;
    current = envlst;
    while (current)
    {
        size++;
        current = current->next;
    }
    env = malloc((size + 1) * sizeof(char *));
    if (!env)
        return (NULL);
    current = envlst;
    while (current)
    {
        env[i++] = current->content;
        current = current->next;
    }
    env[i] = NULL;
    return (env);
}
