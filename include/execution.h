/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:03:53 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/30 12:18:18 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../include/ast.h"

#include <unistd.h>
#include <sys/wait.h>

typedef struct s_context {
    int fd[2];
    int close_fd;

} t_context;

typedef struct s_pids{
    pid_t           pid;
    struct s_pids   *next;
}t_pids;

typedef struct s_executor {
    t_context   context;
    int         status;
    t_pids      *pids;

} t_executor;

void    exec(t_ast *ast);

void    exec_tree(t_ast *ast, t_executor *executor);

void    exec_cmd(t_ast *node, t_executor *executor);


#endif