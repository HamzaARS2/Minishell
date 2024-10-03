#include "../include/execution.h"

void    print_redirect(t_ast *ast)
{
    t_redirect *redirect = ast->redirect;

    while (redirect)
    {
        printf("%d\n", redirect->type);
        redirect = redirect->next;

    }
}
int    open_redirect(char *path, int flag)
{
    int fd;

    fd = open(path, flag, 0644);
    if (fd == -1)
        return (-1);
    return (fd);
}

void    update_ctx(int *ctx_fd, int fd)
{
    if (*ctx_fd != STDOUT_FILENO && *ctx_fd != STDIN_FILENO)
        close(*ctx_fd);

    *ctx_fd = fd;
}

void check_redirect(t_context *ctx, int type, char *file)
{
    int IN_RED;
    int OUT_RED;
    int APPEND;

    IN_RED = O_RDONLY;
    OUT_RED = O_CREAT | O_TRUNC | O_RDWR;
    APPEND = O_CREAT | O_APPEND | O_RDWR;

    if (type == AST_IN_RED)
        update_ctx(&(ctx->fd[0]), open_redirect(file, IN_RED));
    else if (type == AST_OUT_RED)
        update_ctx(&(ctx->fd[1]), open_redirect(file, OUT_RED));
    else if (type == AST_APPEND)
        update_ctx(&(ctx->fd[1]), open_redirect(file, APPEND));
}

void    hndl_redirect(t_ast *ast, t_context *ctx)
{
    //CHECK REDIRECTION ; < AST ;
    t_redirect  *redirect;

    redirect = ast->redirect;
    while (redirect)
    {
        check_redirect(ctx, redirect->type, redirect->content);
        redirect = redirect->next;
    }

    //OPEN FILES        ;
    // SET CONTEXT      ;
    print_redirect(ast);


}