/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:12:35 by helarras          #+#    #+#             */
/*   Updated: 2024/09/25 12:46:28 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

t_pids *get_last_pid(t_pids *pids_list)
{
    while (pids_list && pids_list->next)
        pids_list = pids_list->next;
    return (pids_list);
}

void    add_last_pid(t_pids *pids, t_pids *pids_node)
{
    t_pids *current_last;

    current_last = get_last_pid(pids);
    if (!current_last)
        return ;
    current_last->next = pids_node;
}

t_pids *create_pid(pid_t content)
{
    t_pids *pids;

    pids = malloc(sizeof(t_pids));
    if (!pids)
        return (NULL);
    pids->pid = content;
    pids->next = NULL;
    return (pids);
}

void    add_pid(t_pids **pids_list, t_pids *pids)
{
    if (!(*pids_list))
        *pids_list = pids;
    else
        add_last_pid(*pids_list, pids);
}

void    wait_all(t_executor *executor)
{
    t_pids *current;

    current = executor->pids;
    while (current)
    {
        waitpid(current->pid, &executor->status, 0);
        printf("status: %i\n", executor->status);
        current = current->next;
    }
}