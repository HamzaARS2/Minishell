/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:25:23 by helarras          #+#    #+#             */
/*   Updated: 2024/10/12 16:10:47 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void    free_env_rm(t_envlst *env_rm)
{
    free(env_rm->key);
    free(env_rm->value);
    free(env_rm);
}

t_envlst *find_env(t_envlst **envlst, char *key)
{
    t_envlst *current;

    current = *envlst;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
            return (current);
        current = current->next;
    }
    return (NULL);
}

bool    remove_env(t_envlst **envlst, t_envlst *env_rm)
{
    if (*envlst == env_rm)
    {
        *envlst = env_rm->next;
        (*envlst)->prev = NULL;
        free_env_rm(env_rm);
        return (true);
    }
    env_rm->prev->next = env_rm->next;
    if (env_rm->next)
        env_rm->next->prev = env_rm->prev;
    free_env_rm(env_rm);
    return (true);
}

bool    mshell_unset(t_envlst **envlst, t_ast *node)
{
    t_envlst *env_rm;
    int i;

    i = 0;
    while (node->args[++i])
    {
        env_rm = find_env(envlst, node->args[i]);
        if (!env_rm)
            continue;
        remove_env(envlst, env_rm);
    }
    return (true);
}