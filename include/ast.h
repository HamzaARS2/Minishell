/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:48:22 by helarras          #+#    #+#             */
/*   Updated: 2024/08/25 15:40:57 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "lexer.h"

typedef enum e_ast_type {
    COMMAND,
    OPTIONN,
    ARGUMENT
} t_ast_type;

typedef struct s_ast { 
    t_token *token;
    t_ast_type type;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

// create ast node.
t_ast   *ast_create_node(t_token *token, t_ast_type type);



#endif