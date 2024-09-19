/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:55:46 by helarras          #+#    #+#             */
/*   Updated: 2024/09/17 15:02:15 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_ast   *prsr_parse_cmd(t_parser *parser)
{
    t_ast   *node;
    uint32_t count;
    uint32_t i;
    
    i = 0;
    node = ast_create_node(NULL, AST_COMMAND);
    count = uprsr_count_cmd(parser->current);
    node->args = malloc((count + 1) * sizeof(char *));
    if (!node->args)
    {
        free(node);
        return (NULL);
    }
    while (i < count)
    {
        node->args[i] = parser->current->value;
        prsr_advance(parser);
        i++;
    }
    node->args[i] = NULL;
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

t_ast   *prsr_parse_logical_and(t_parser *parser)
{
    t_ast *left;
    t_ast *logical_and;
    
    left = prsr_parse_pipe(parser);
    if (parser->current && parser->current->type == D_AND)
    {
        logical_and = ast_create_node(NULL, AST_AND);
        logical_and->left = left;
        prsr_advance(parser);
        logical_and->right = prsr_parse_logical_and(parser);
        return (logical_and);
    }
    return (left);
}

t_ast   *prsr_parse_logical_or(t_parser *parser)
{
    t_ast *left;
    t_ast *logical_or;
    
    left = prsr_parse_logical_and(parser);
    if (parser->current && parser->current->type == OR)
    {
        logical_or = ast_create_node(NULL, AST_OR);
        logical_or->left = left;
        prsr_advance(parser);
        logical_or->right = prsr_parse_logical_or(parser);
        return (logical_or);
    }
    return (left);
}