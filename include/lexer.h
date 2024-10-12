/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:50:41 by helarras          #+#    #+#             */
/*   Updated: 2024/10/12 11:29:41 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


#include "token.h"

typedef struct s_lexer {
    t_token         *tokens;
    char            *content;
    t_state         state;
    bool            dynamic_state;
    uint32_t        size;
    uint32_t        i;
    char            c;
} t_lexer;

// initializing the lexer.
t_lexer *init_lexer(char *content, bool dynamic_state);

// advance to the next char in sequence.
void    lxr_advance(t_lexer *lexer);

// recognize the current lexer's state and update it.
void    lxr_recognize_state(t_lexer *lexer);

// extract token from lexer content.
t_token *lxr_tokenize(t_lexer *lexer);

// generates list of tokens.
void    lxr_generate_tokens(t_lexer *lexer);

// extract specific token types.
bool    ulxr_extract_word(t_lexer *lexer, t_token **token);
bool    ulxr_extract_space(t_lexer *lexer, t_token **token);
bool    ulxr_extract_dquotes(t_lexer *lexer, t_token **token);
bool    ulxr_extract_squotes(t_lexer *lexer, t_token **token);
bool    ulxr_extract_variable(t_lexer *lexer, t_token **token);

bool    ulxr_extract_inred(t_lexer *lexer, t_token **token);
bool    ulxr_extract_outred(t_lexer *lexer, t_token **token);
bool    ulxr_extract_pipe(t_lexer *lexer,t_token **token);
bool    ulxr_extract_status(t_lexer *lexer, t_token **token);

#endif