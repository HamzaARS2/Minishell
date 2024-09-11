/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:33:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/10 13:42:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_ast   *prsr_create(t_parser *parser, t_ast_type type, t_ast *left)
{
    t_ast *ast;

    ast = ast_create_node(NULL, type);
    ast->left = left;
    prsr_advance(parser);
    ast->right = prsr_parse_outred(parser);
    return (ast);
}

t_ast   *prsr_parse_outred(t_parser *parser)
{
    t_ast *left;
    t_ast *redirect;
    
    left = prsr_parse_pipe(parser);
    if (parser->current && parser->current->type == OUT_RED)
        return (prsr_create(parser, AST_OUT_RED, left));
    if (parser->current && parser->current->type == IN_RED)
        return (prsr_create(parser, AST_IN_RED, left));
    return (left);
}