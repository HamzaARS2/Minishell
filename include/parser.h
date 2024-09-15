/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:45:18 by helarras          #+#    #+#             */
/*   Updated: 2024/09/15 14:24:09 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"


typedef struct s_parser
{
    t_token *tokens;
    t_token *current;
    t_ast   *ast;
} t_parser;

// initializing the parser.
t_parser    *init_parser(t_token *tokens);

// advances to the next token.
void    prsr_advance(t_parser *parser);

// build the abstract syntax tree.
t_ast   *prsr_parse(t_parser *parser);

// build the subtree of redirects.
t_ast   *prsr_redirect_subtree(t_parser *parser, t_ast_type type, t_ast *left);

// procedures.
t_ast   *prsr_parse_pipe(t_parser *parser);
t_ast   *prsr_parse_cmd(t_parser *parser);
t_ast   *prsr_parse_logical_and(t_parser *parser);
t_ast   *prsr_parse_logical_or(t_parser *parser);
t_ast   *prsr_parse_redirect(t_parser *parser);

// utils
uint32_t    uprsr_count_cmd(t_token *token);

#endif