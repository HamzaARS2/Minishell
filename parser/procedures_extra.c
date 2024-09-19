/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:33:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/17 15:46:57 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_ast   *prsr_parse_redirect(t_parser *parser)
{
    t_ast *left;
    
    left = prsr_parse_cmd(parser);
    if (parser->current && parser->current->type == OUT_RED)
        return (prsr_redirect_subtree(parser, AST_OUT_RED, left));
    if (parser->current && parser->current->type == IN_RED)
        return (prsr_redirect_subtree(parser, AST_IN_RED, left));
    if (parser->current && parser->current->type == APPEND)
        return (prsr_redirect_subtree(parser, AST_APPEND, left));
    if (parser->current && parser->current->type == HERE_DOC)
        return (prsr_redirect_subtree(parser, AST_HEREDOC, left));
    return (left);
}
