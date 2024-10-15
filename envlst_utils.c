/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:32:45 by helarras          #+#    #+#             */
/*   Updated: 2024/10/15 10:30:35 by helarras         ###   ########.fr       */
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
        env[i++] = strcombine(current->key, current->value, false);
        current = current->next;
    }
    env[i] = NULL;
    return (env);
}

void    display_env_line(t_envlst *env, int fd, bool flag)
{
    if (flag)
    {
        if (!env->value)
            return ;
        ft_putstr_fd(env->key, fd);    
        ft_putstr_fd(env->value, fd);
        ft_putstr_fd("\n", fd);
    }
    else
    {
        if (env->value)
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(env->key, fd);
            ft_putstr_fd("=\"", fd);
            ft_putstr_fd(env->value + 1, fd);
            ft_putstr_fd("\"\n", fd);
        }
        else
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(env->key, fd);
            ft_putstr_fd("\n", fd);
        }
    }
}

void    print_env(t_envlst *envlst, int outfd, bool flag)
{
    t_envlst *current;

    current = envlst;
    while (current)
    {
        display_env_line(current, outfd, flag);
        current = current->next;
    }
}
