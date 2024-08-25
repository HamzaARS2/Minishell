/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:31:11 by helarras          #+#    #+#             */
/*   Updated: 2024/08/25 15:14:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"


typedef struct s_parser {
    t_lexer     *lexer;
    t_token     *current_tkn;
    uint32_t    i;
} t_parser;

// initializing the parser.
t_parser    *init_parser(t_lexer *lexer);

// advance to the next token in the list.
void        psr_advance(t_parser *parser);

#endif
