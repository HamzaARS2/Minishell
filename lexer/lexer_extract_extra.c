/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:15:17 by helarras          #+#    #+#             */
/*   Updated: 2024/10/07 09:54:40 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

bool    ulxr_extract_inred(t_lexer *lexer, t_token **token)
{
    u_int32_t   start;

    start = lexer->i;
    if (lexer->c != '<')
        return (false);
    lxr_advance(lexer);
    while (lexer->c && lexer->c == '<' && lexer->i - start < 2)
        lxr_advance(lexer);
    *token = tkn_extract(IN_RED, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start > 1)
        (*token)->type = HERE_DOC;
    (*token)->state = lexer->state;
    return (true);
}

bool    ulxr_extract_outred(t_lexer *lexer, t_token **token)
{
    u_int32_t   start;

    start = lexer->i;
    if (lexer->c != '>')
        return (false);
    lxr_advance(lexer);
    while (lexer->c && lexer->c == '>')
        lxr_advance(lexer);
    *token = tkn_extract(OUT_RED, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start > 1)
        (*token)->type = APPEND;
    (*token)->state = lexer->state;
    return (true);
}

bool    ulxr_extract_pipe(t_lexer *lexer,t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '|')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    *token = tkn_extract(PIPE, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    (*token)->state = lexer->state;
    return (true);
}

bool    ulxr_extract_status(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '$' || lexer->content[lexer->i + 1] != '?')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    lxr_advance(lexer);
    *token = tkn_extract(STATUS, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    (*token)->state = lexer->state;
    return (true);
}
