/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:27:02 by helarras          #+#    #+#             */
/*   Updated: 2024/09/24 15:24:34 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/lexer.h"

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
    if (lexer->state == IN_SQUOTES)
    {
        *token = tkn_extract(DQUOTES, lexer->content, start, lexer->i);   
        (*token)->state = lexer->state;
        return (true);
    }
    else if (lexer->c == '"')
    {
        *token = tkn_create_token(ft_strdup(""), WORD);
        (*token)->state = lexer->state;
        return (true);
    }
    return (false);
}


bool    ulxr_extract_squotes(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    if (lexer->c != '\'')
        return (false);
    start = lexer->i;
    lxr_advance(lexer);
    if (lexer->state == IN_DQUOTES)
    {
        *token = tkn_extract(SQUOTES, lexer->content, start, lexer->i);   
        (*token)->state = lexer->state;
        return (true);
    }
    else if (lexer->c == '\'')
    {
        *token = tkn_create_token(ft_strdup(""), WORD);
        (*token)->state = lexer->state;
        return (true);
    }
    return (false);
}

bool    ulxr_extract_variable(t_lexer *lexer, t_token **token)
{
    uint32_t    start;
    
    start = lexer->i;
    if (lexer->c != '$')
        return (false);
    lxr_advance(lexer);
    while (lexer->c && (ft_isalnum(lexer->c)))
        lxr_advance(lexer);
    *token = tkn_extract(WORD, lexer->content, start, lexer->i);
    if (!(*token))
        return (false);
    if (lexer->i - start > 1 || ((lexer->i - start == 1 && lexer->state == DEFAULT)
        && (lexer->c == '"' || lexer->c == '\'')))
        (*token)->type = VARIABLE;
    (*token)->state = lexer->state;
    return (true);
}
