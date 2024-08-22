/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:50:41 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 19:41:36 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "token.h"

typedef struct s_lexer {
    char            *content;
    unsigned int    size;
    unsigned int    i;
    char            c;
    t_token         *tokens;
} t_lexer;

// initializing the lexer.
t_lexer *init_lexer(char *content);

// advance to the next char in sequence.
void    lexer_advance(t_lexer *lexer);

t_token *lexer_tokenize(t_lexer *lexer);

// utils
bool    ulex_extract_command(t_lexer *lexer, t_token **token);




#endif