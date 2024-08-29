/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:27:02 by helarras          #+#    #+#             */
/*   Updated: 2024/08/29 15:39:48 by helarras         ###   ########.fr       */
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
    (*token)->state = lexer->state;
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
    *token = tkn_extract(SSPACE, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    (*token)->state = lexer->state;
    return (true);
}

bool    ulxr_extract_dquotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '"')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    if (lexer->state == DEFAULT)
        lexer->state = IN_DQUOTES;
    else if (lexer->state == IN_SQUOTES)
        (*token)->state = IN_SQUOTES;
    else if (lexer->state == IN_DQUOTES)
        lexer->state = DEFAULT;
    return (false);
}

bool    ulxr_extract_squotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    char        *word;
    
    if (lexer->c != '\'')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    if (lexer->state == DEFAULT)
        lexer->state = IN_SQUOTES;
    else if (lexer->state == IN_DQUOTES)
        (*token)->state = IN_DQUOTES;
    else if (lexer->state == IN_SQUOTES)
        lexer->state = DEFAULT;
    return (false);
}


