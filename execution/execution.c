/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:11:09 by helarras          #+#    #+#             */
/*   Updated: 2024/09/25 16:19:42 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void    init_executor(t_executor *executor, t_ast *ast, char **env)
{
    executor->ast = ast;
    executor->current = ast;
    executor->env = env;
    executor->pids = NULL;
    executor->status = EXIT_SUCCESS;
}

void    close_fds(t_fds fds)
{
    if (fds.in_fd != STDIN_FILENO)
        close(fds.in_fd);
    if (fds.out_fd != STDOUT_FILENO)
        close(fds.out_fd);
}
void    dup_fds(t_fds *fds)
{
    if (fds->in_fd != STDIN_FILENO)
        dup2(fds->in_fd, STDIN_FILENO);
    if (fds->out_fd != STDOUT_FILENO)
        dup2(fds->out_fd, STDOUT_FILENO);
    close_fds(*fds);
}


void    execute_command(t_executor *executor, t_fds fds, int p[2]) 
{
    pid_t pid;
    t_ast *command;

    command = executor->current;
    pid = fork();
    if (pid != 0)
    {
        add_pid(&executor->pids, create_pid(pid));
        return ;
    }
    dup_fds(&fds);
    if (p)
    {
        close(p[0]);
        close(p[1]);
    }
    // close_fds(executor->pipe);
    execve(command->args[0], command->args, executor->env);
    // TODO: need to be handled effectivly.
    exit(1);
}

void    execute_pipe(t_executor *executor, t_fds fds)
{
    int p[2];
    
    pipe(p);
    fds.out_fd = p[1];
    executor->current = executor->current->left;
    execute_command(executor, fds, p);
    if (executor->current->right)
        executor->current = executor->current->right;
    else 
        executor->current = executor->ast->right;
        
    if (executor->current->type == AST_COMMAND)
    {
        fds.in_fd = p[0];
        fds.out_fd = 1;
        execute_command(executor, fds, p);
    } else {
        
        // execute_pipe(executor, fds);
    }
    close(p[0]);
    close(p[1]);
    close_fds(fds);
}

void    execute_ast(t_executor *executor)
{
    t_ast *ast;

    ast = executor->ast;
    if (ast->type == AST_COMMAND)
    {
        execute_command(executor, (t_fds) {0, 1}, NULL);
    }
    else if (ast->type == AST_PIPE)
    {
        execute_pipe(executor, (t_fds) {0, 1});
    }
    wait_all(executor);
}