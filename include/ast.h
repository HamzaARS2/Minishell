/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:23:50 by helarras          #+#    #+#             */
/*   Updated: 2024/09/17 13:11:03 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_ast_type {
    AST_COMMAND = 1000,
    AST_PIPE,
    AST_OR,
    AST_AND,
    AST_IN_RED,
    AST_OUT_RED,
    AST_HEREDOC,
    AST_APPEND
} t_ast_type;

typedef struct s_ast {
    char    **args;
    t_ast_type type;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

t_ast   *ast_create_node(char **args, t_ast_type type);

#endif