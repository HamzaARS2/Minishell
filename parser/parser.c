/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:03:34 by helarras          #+#    #+#             */
/*   Updated: 2024/08/25 15:15:11 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parser    *init_parser(t_lexer *lexer)
{
    t_parser    *parser;

    parser = malloc(sizeof(t_parser));
    if (!parser)
        return (NULL);
    parser->lexer = lexer;
    parser->i = 0;
    parser->current_tkn = lexer->tokens;
    return (parser);
}

void    psr_advance(t_parser *parser)
{
    if (!parser->current_tkn || !parser->current_tkn->next)
        return ;
    parser->i++;
    parser->current_tkn = parser->current_tkn->next;
}