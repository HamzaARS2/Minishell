/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:27:02 by helarras          #+#    #+#             */
/*   Updated: 2024/08/26 10:37:58 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool    ulxr_extract_word(t_lexer *lexer, t_token **token)
{
    u_int32_t       start;

    start = lexer->i;
    while (lexer->c && !is_shell_special(lexer->c))
        lxr_advance(lexer);
    *token = tkn_extract(WORD, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    return (true);
}

bool    ulxr_extract_option(t_lexer *lexer, t_token **token)
{
    unsigned int    start;

    if (lexer->c != '-')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && !is_shell_special(lexer->c))
        lxr_advance(lexer);
    *token = tkn_extract(OPTION, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    return (true);
}

bool    ulxr_extract_space(t_lexer *lexer, t_token **token)
{
    unsigned int    start;

    if (lexer->c != 32)
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && lexer->c == 32)
        lxr_advance(lexer);
    *token = tkn_extract(SPACE, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    return (true);
}

bool    ulxr_extract_dquotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '"')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && lexer->c != '"')
        lxr_advance(lexer);
    if (lexer->c == '"')
    {
        lxr_advance(lexer);
        *token = tkn_extract(DQUOTES, lexer->content, start, lexer->i);
        if (!(*token))
            return (false);
    } else
        *token = tkn_create_token(NULL, ERROR);
    return (true);
}

bool    ulxr_extract_squotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '\'')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && lexer->c != '\'')
        lxr_advance(lexer);
    if (lexer->c == '\'')
    {
        lxr_advance(lexer);
        *token = tkn_extract(SQUOTES, lexer->content, start, lexer->i);
        if (!(*token))
            return (false);
    } else
        *token = tkn_create_token(NULL, ERROR);
    return (true);
}


