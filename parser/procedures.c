/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:55:46 by helarras          #+#    #+#             */
/*   Updated: 2024/10/15 13:18:44 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_ast   *prsr_parse_cmd(t_parser *parser)
{
    t_ast   *node;
    
    node = ast_create_node(NULL, AST_COMMAND);
    node->args = uprsr_build_cmd(parser);
    if (!node->args)
    {
        free(node);
        return (NULL);
    }
    return (node);
}

t_ast   *prsr_parse_pipe(t_parser *parser)
{
    t_ast *left;
    t_ast *pipe;

    left = prsr_parse_redirect(parser);
    if (parser->current && parser->current->type == PIPE)
    {
        pipe = ast_create_node(NULL, AST_PIPE);
        pipe->left = left;
        prsr_advance(parser);
        pipe->right = prsr_parse_pipe(parser);
        return (pipe);  
    }
    return (left);
}
