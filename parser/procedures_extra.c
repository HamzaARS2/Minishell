/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedures_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:33:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/22 11:39:41 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void    prsr_parse_file(t_parser *parser, t_ast *ast, t_ast_type type)
{
    t_redirect *redirect;

    prsr_advance(parser);
    redirect = ast_create_redirect(parser->current->value, type);
    if (!redirect)
        return ;
    ast_add_redirect(&ast->redirect, redirect);
}

t_ast   *prsr_parse_redirect(t_parser *parser)
{
    t_ast *left;
    
    left = prsr_parse_cmd(parser);
    while (parser->current)
    {
        if (parser->current->type == WORD || parser->current->type == VARIABLE || parser->current->state != DEFAULT)
            prsr_advance(parser);
        else if (parser->current->type >= 33 && parser->current->type <= 36)
        {
            prsr_parse_file(parser, left, get_ast_type(parser->current));
            prsr_advance(parser);
        }
        else
            break ;
    } 
    return (left);
}
