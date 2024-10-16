/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:28:46 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 22:46:09 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ast.h"

t_ast	*ast_create_node(char **cmd, t_ast_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->args = cmd;
	node->type = type;
	node->redirect = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_redirect	*ast_create_redirect(char *content, t_ast_type type)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->content = content;
	redirect->type = type;
	redirect->heredoc_fd = -1;
	redirect->next = NULL;
	return (redirect);
}

void	ast_add_redirect(t_redirect **redirect_list, t_redirect *redirect)
{
	if (!(*redirect_list))
		*redirect_list = redirect;
	else
		add_last_redirect(*redirect_list, redirect);
}
