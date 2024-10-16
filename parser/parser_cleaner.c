/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:07:29 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 22:46:15 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	prsr_clean_redirects(t_redirect *redirects)
{
	t_redirect	*current;
	t_redirect	*temp;

	current = redirects;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	prsr_clean_node(t_ast *node)
{
	free(node->args);
	prsr_clean_redirects(node->redirect);
	free(node);
}

void	prsr_ast_clean(t_ast *node)
{
	if (node->type == AST_PIPE)
	{
		prsr_ast_clean(node->left);
		prsr_ast_clean(node->right);
		free(node);
	}
	else if (node->type == AST_COMMAND)
		prsr_clean_node(node);
}

void	prsr_clean(t_parser *parser)
{
	prsr_ast_clean(parser->ast);
}
