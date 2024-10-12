#include "../include/execution.h"

void    dup_fds(t_context ctx)
{
    if (ctx.fd[STDIN_FILENO] != STDIN_FILENO) {
        dup2(ctx.fd[STDIN_FILENO], STDIN_FILENO);
        close(ctx.fd[STDIN_FILENO]);
    }
    if (ctx.fd[STDOUT_FILENO] != STDOUT_FILENO) {
        dup2(ctx.fd[STDOUT_FILENO], STDOUT_FILENO);
        close(ctx.fd[STDOUT_FILENO]);
    }
    if (ctx.close_fd != -1)
        close(ctx.close_fd);
}

bool    exec_builtin(t_executor *executor, t_ast *node, t_builtins_type type)
{
    if (type == CD)
        return (cd(node->args, *executor->envlst));
    else if (type == EXPORT)
        return (mshell_export(executor->envlst, node));
    else if (type == ENV)
        return (mshell_env(*executor->envlst));
    else if (type == EXIT)
        return(mshell_exit(node->args));
    return (false);
}

void    run_command(t_ast *node, t_executor *executor)
{
    char *path;
    t_builtins_type type;

    type = builtin_check(node->args[0]);
    if (type == NONE)
    {
        path = cmd_expand(node->args[0], executor->paths);
        execve(path, node->args, get_env(*executor->envlst));
        exit(23);
    }
    else
    {
        if (!exec_builtin(executor, node, type))    
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    }
}