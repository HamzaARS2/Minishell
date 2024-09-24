/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:37:15 by helarras          #+#    #+#             */
/*   Updated: 2024/09/24 11:56:59 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_envlst *get_last_envlst(t_envlst *envlst_list)
{
    while (envlst_list && envlst_list->next)
        envlst_list = envlst_list->next;
    return (envlst_list);
}

void    add_last_envlst(t_envlst *envlst, t_envlst *envlst_node)
{
    t_envlst *current_last;

    current_last = get_last_envlst(envlst);
    if (!current_last)
        return ;
    current_last->next = envlst_node;
}

t_envlst *create_envlst(char *content)
{
    t_envlst *envlst;

    envlst = malloc(sizeof(t_envlst));
    if (!envlst)
        return (NULL);
    envlst->variable = content;
    envlst->next = NULL;
    return (envlst);
}

void    add_envlst(t_envlst **envlst_list, t_envlst *envlst)
{
    if (!(*envlst_list))
        *envlst_list = envlst;
    else
        add_last_envlst(*envlst_list, envlst);
}

t_envlst    *shell_init_envlst(char **env)
{
    t_envlst *head;

    if (!env || !*env)
        return (NULL);
    head = create_envlst(ft_strdup((*env)));
    env++;
    while (*env)
    {
        add_envlst(&head, create_envlst(ft_strdup(*env)));
        env++;
    }
    return (head);
}