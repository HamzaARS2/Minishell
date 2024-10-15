/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:03:53 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/15 10:37:56 by helarras         ###   ########.fr       */
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
    int         *ex_status;
    t_pids      *pids;
    char        **paths;
    t_envlst    **envlst;
} t_executor;

void    exec(t_ast *ast, t_executor *executor);

void    exec_tree(t_ast *ast, t_executor *executor);

void    exec_cmd(t_ast *node, t_executor *executor);

void    add_pid(t_pids **pids, pid_t pid);

void    ft_wait(t_executor *executor);

void    init_executor(t_executor *executor, t_envlst **envlst, int *ex_status);

void    print_pids(t_pids *pids, int  flag);//delete

int     hndl_redirect(t_ast *ast, t_context *ctx);



void    hrdoc_collect(t_ast *node, t_envlst *envlst, int *ex_status);

void    hrdoc_search(t_redirect *redirect, t_envlst *envlst, int *ex_status);

void    hrdoc_run(t_redirect *heredoc, t_envlst *envlst, int *ex_status);

bool    uhrdoc_env_exist(char *line);

uint32_t    uhrdoc_get_size(t_token *tokens);

char    *uhrdoc_join_tokens(t_token *tokens, uint32_t size);

void    uhrdoc_clear(t_lexer *lexer, t_resolver *resolver, char *line);


char    **get_paths(t_envlst *envlst);

void print_dpointer(char **dirs);  //TMP TEST

char    *cmd_expand(char *cmd, char **paths);

void    run_command(t_ast *node, t_executor *executor);

// utils
void    dup_fds(t_context ctx);

#endif