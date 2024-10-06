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