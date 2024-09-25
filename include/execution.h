/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:11:16 by helarras          #+#    #+#             */
/*   Updated: 2024/09/25 16:19:33 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "ast.h"
#include "resolver.h"

typedef struct s_fds {
    int in_fd;
    int out_fd;
} t_fds;

typedef struct s_pids {
    pid_t pid;
    struct s_pids *next;
} t_pids;

typedef struct s_executor {
    t_ast           *ast;
    t_ast           *current;
    t_pids          *pids;
    char            **env;
    int    status;
} t_executor;

void    init_executor(t_executor *executor, t_ast *ast, char **env);
void    execute_ast(t_executor *executor);


t_pids *create_pid(pid_t content);
void    add_pid(t_pids **pids_list, t_pids *pids);
void    wait_all(t_executor *executor);
#endif