/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:28:46 by helarras          #+#    #+#             */
/*   Updated: 2024/09/11 18:17:57 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast   *ast_create_node(char **cmd, t_ast_type type)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->args = cmd;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return (node);
}
