#include "../include/execution.h"

int    open_redirect(char *path, int flag)
{
    int fd;

    fd = open(path, flag, 0644);
    if (fd == -1)
        return (-1);
    return (fd);
}

int    update_ctx(int *ctx_fd, int fd)
{
    if (*ctx_fd != STDOUT_FILENO && *ctx_fd != STDIN_FILENO)
        close(*ctx_fd);

    *ctx_fd = fd;
    return (fd);
}

int check_redirect(t_context *ctx, t_redirect *redirect)
{
    int fd;
    int IN_RED;
    int OUT_RED;
    int APPEND;

    IN_RED = O_RDONLY;
    OUT_RED = O_CREAT | O_TRUNC | O_RDWR;
    APPEND = O_CREAT | O_APPEND | O_RDWR;

    if (redirect->type == AST_IN_RED)
        fd = update_ctx(&(ctx->fd[0]), open_redirect(redirect->content, IN_RED));
    else if (redirect->type == AST_OUT_RED)
        fd = update_ctx(&(ctx->fd[1]), open_redirect(redirect->content, OUT_RED));
    else if (redirect->type == AST_APPEND)
        fd = update_ctx(&(ctx->fd[1]), open_redirect(redirect->content, APPEND));
    else if (redirect->type == AST_HEREDOC || redirect->type == AST_INQ_HEREDOC)
        fd = update_ctx(&(ctx->fd[0]), redirect->heredoc_fd);
    return (fd);
}

int    hndl_redirect(t_ast *ast, t_context *ctx)
{
    t_redirect  *redirect;
    int         fd;

    redirect = ast->redirect;
    while (redirect)
    {
        fd = check_redirect(ctx, ast->redirect);
        redirect = redirect->next;
    }
    return (fd);
}