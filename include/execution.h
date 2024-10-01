/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:03:53 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/01 16:18:44 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include <readline/readline.h>
#include <readline/history.h>
#include "../include/ast.h"
#include "../include/resolver.h"
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_vinfo {
    char *variable;
    char *value;
    uint32_t varsize;
    uint32_t valsize;
    uint32_t i;
} t_vinfo;

typedef struct s_context {
    int fd[2];
    int close_fd;

} t_context;

typedef struct s_pids{
    pid_t           pid;
    struct s_pids   *next;
}t_pids;

typedef struct s_executor {
    t_context   ctx;
    int         status;
    t_pids      *pids;

} t_executor;

void    exec(t_ast *ast);

void    exec_tree(t_ast *ast, t_executor *executor);

void    exec_cmd(t_ast *node, t_executor *executor);


void    hrdoc_collect(t_ast *node, t_envlst *envlst);

void    hrdoc_search(t_redirect *redirect, t_envlst *envlst);

void    hrdoc_run(t_redirect *heredoc, t_envlst *envlst);

char    *hrdoc_replace_env(t_vinfo vinfo, char *line);

void    uhrdoc_envval_cpy(t_vinfo vinfo, char *line, char *newline);

void    uhrdoc_expand_env(t_vinfo *vinfo, t_envlst *envlst);

char    *uhrdoc_envname(char *str);

void    uhrdoc_next_env(t_vinfo *vinfo, char *line);

void    uhrdoc_clear(t_vinfo vinfo);
#endif