/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:03:53 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/05 08:36:45 by ajbari           ###   ########.fr       */
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
#include <fcntl.h>
#include "get_next_line.h"

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

void    exec(t_ast *ast, t_executor *executor);

void    exec_tree(t_ast *ast, t_executor *executor);

void    exec_cmd(t_ast *node, t_executor *executor);

void    add_pid(t_pids **pids, pid_t pid);

void    ft_wait(t_executor *executor);

void    init_executor(t_executor *executor);

void    print_pids(t_pids *pids, int  flag);//delete

int     hndl_redirect(t_ast *ast, t_context *ctx);



void    hrdoc_collect(t_ast *node, t_envlst *envlst);

void    hrdoc_search(t_redirect *redirect, t_envlst *envlst);

void    hrdoc_run(t_redirect *heredoc, t_envlst *envlst);

bool    uhrdoc_env_exist(char *line);

uint32_t    uhrdoc_get_size(t_token *tokens);

char    *uhrdoc_join_tokens(t_token *tokens, uint32_t size);

void    uhrdoc_clear(t_lexer *lexer, t_resolver *resolver, char *line);

void    expand_cmd(t_ast **ast, t_envlst *envlst);



#endif