/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:15:17 by helarras          #+#    #+#             */
/*   Updated: 2024/08/25 08:56:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool    ulxr_extract_inred(t_lexer *lexer, t_token **token)
{
    u_int32_t   start;

    start = lexer->i;
    if (lexer->c != '<')
        return (false);
    lxr_advance(lexer);
    while (lexer->c && lexer->c == '<')
        lxr_advance(lexer);
    *token = tkn_extract(IN_RED, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start > 1)
        (*token)->type = HERE_DOC;
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
        (*token)->type = APPENED;
    return (true);
}

bool    ulxr_extract_variable(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    start = lexer->i;
    if (lexer->c != '$')
        return (false);
    lxr_advance(lexer);
    while (lexer->c && ft_isalnum(lexer->c))
        lxr_advance(lexer);
    *token = tkn_extract(VARIABLE, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start == 1)
        (*token)->type = WORD;
    return (true);
}

bool    ulxr_extract_pipe(t_lexer *lexer,t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '|')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && lexer->c == '|')
        lxr_advance(lexer);
    *token = tkn_extract(PIPE, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start > 1)
        (*token)->type = OR;
    return (true);
}
