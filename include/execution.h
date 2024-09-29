/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:11:16 by helarras          #+#    #+#             */
/*   Updated: 2024/09/26 09:33:12 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "ast.h"
#include "resolver.h"

typedef struct s_context {
    int fd[2];
    int fd_close;
} t_context;

void    exec_ast(t_ast *ast);

void    exec_node(t_ast *node, t_context *ctx);

void    exec_pipe(t_ast *node, t_context *ctx);

void    exec_command(t_ast *node, t_context *ctx);

#endif