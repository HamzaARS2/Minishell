/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:54:55 by helarras          #+#    #+#             */
/*   Updated: 2024/08/25 15:11:53 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast   *ast_create_node(t_token *token, t_ast_type type)
{
    t_ast   *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->token = token;
    node->type = type;
    return (node);
}
