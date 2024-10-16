#include "../include/execution.h"
#include "../include/builtins.h"

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
}


void    run_command(t_ast *node, t_executor *executor)
{
    char *path;
    t_builtins_type type;

    type = builtin_check(node->args[0]);
    if (type == NONE)
    {
        dup_fds(executor->ctx);
        path = cmd_expand(node->args[0], executor->paths);
        execve(path, node->args, get_env(*executor->envlst));
        exit(EXIT_FAILURE);
    }
    else
    {
        if (exec_builtin(executor, node, type))
            exit(EXIT_SUCCESS);
        add_pid(&executor->pids, -1);
        exit(EXIT_FAILURE);
    }
}
