/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:27:02 by helarras          #+#    #+#             */
/*   Updated: 2024/08/24 14:13:29 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

bool    ulxr_extract_quotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '"')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    while (lexer->c && lexer->c == '"')
        lxr_advance(lexer);
    *token = tkn_extract(DQUOTES, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    return (true);
}


