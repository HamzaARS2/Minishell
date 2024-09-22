/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:23:50 by helarras          #+#    #+#             */
/*   Updated: 2024/09/22 10:23:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "token.h"

typedef enum e_ast_type {
    AST_COMMAND,
    AST_PIPE,
    AST_OR,
    AST_IN_RED,
    AST_OUT_RED,
    AST_APPEND,
    AST_HEREDOC,
    AST_INQ_HEREDOC,
    AST_AND
} t_ast_type;

typedef struct s_redirect {
    char *content;
    t_ast_type type;
    struct s_redirect *next;
} t_redirect;

typedef struct s_ast {
    char    **args;
    t_ast_type type;
    t_redirect *redirect;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

// creates AST node.
t_ast   *ast_create_node(char **args, t_ast_type type);

// creates AST command redirection.
t_redirect *ast_create_redirect(char *content, t_ast_type type);

void    ast_add_redirect(t_redirect **redirect_list, t_redirect *redirect);

// utils.
t_redirect  *get_last_redirect(t_redirect *redirect_list);
void        add_last_redirect(t_redirect *redirect_list, t_redirect *redirect_node);
t_ast_type  get_ast_type(t_token *token);




#endif