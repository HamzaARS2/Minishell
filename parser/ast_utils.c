/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:50:33 by helarras          #+#    #+#             */
/*   Updated: 2024/09/22 11:04:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"

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

t_ast_type  get_ast_type(t_token *token)
{
    if (token->type == HERE_DOC && token->next->state != DEFAULT)
        return (AST_INQ_HEREDOC);
    return (token->type - WORD);
}