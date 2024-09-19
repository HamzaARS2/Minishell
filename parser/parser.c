/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:46:03 by helarras          #+#    #+#             */
/*   Updated: 2024/09/17 15:47:06 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_parser    *init_parser(t_token *tokens)
{
    t_parser *parser;

    parser = malloc(sizeof(t_parser));
    if (!parser)
        return (NULL);
    parser->tokens = tokens;
    parser->current = tokens;
    parser->ast = NULL;
    return (parser);
}

void    prsr_advance(t_parser *parser)
{
    if (!parser->current)
        return ;
    parser->current = parser->current->next;
}

t_ast   *prsr_redirect_subtree(t_parser *parser, t_ast_type type, t_ast *left)
{
    t_ast *ast;

    ast = ast_create_node(NULL, type);
    ast->left = left;
    prsr_advance(parser);
    ast->right = prsr_parse_redirect(parser);
    return (ast);
}

t_ast   *prsr_parse(t_parser *parser)
{
    return (prsr_parse_logical_or(parser));
}