/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:50:33 by helarras          #+#    #+#             */
/*   Updated: 2024/09/19 10:55:42 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_redirect *get_last_redirect(t_redirect *redirect_list)
{
    while (redirect_list && redirect_list->next)
        redirect_list = redirect_list->next;
    return (redirect_list);
}

void    add_last_redirect(t_redirect *redirect_list, t_redirect *redirect_node)
{
    t_redirect *current_last;

    current_last = get_last_redirect(redirect_list);
    if (!current_last)
        return ;
    current_last->next = redirect_node;
}
