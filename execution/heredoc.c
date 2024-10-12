
#include "../include/execution.h"

char    *hrdoc_expand(t_envlst *envlst, char *line)
{
    t_lexer     *lexer;
    t_resolver  *resolver;
    char        *newline;

    if (!uhrdoc_env_exist(line))
        return (line);
    lexer = init_lexer(line);
    lxr_generate_tokens(lexer);
    resolver = init_resolver(lexer, envlst);
    rslv_expand(resolver, false);
    newline = uhrdoc_join_tokens(lexer->tokens, uhrdoc_get_size(lexer->tokens));
    uhrdoc_clear(lexer, resolver, line);
    return (newline);
}

void    hrdoc_run(t_redirect *heredoc, t_envlst *envlst)
{
    int     p[2];
    char    *line;

    pipe(p);
    while (true)
    {
        line = readline("heredoc > ");
        if (!line)
            break;
        if (!ft_strcmp(line, heredoc->content))
           break;
        line = strcombine(line, ft_strdup("\n"), true);
        if (!line)
            break;
        if (heredoc->type == AST_HEREDOC)
            line = hrdoc_expand(envlst, line);
        write(p[1], line, ft_strlen(line));
        free(line);
    }
    close(p[1]);
    heredoc->heredoc_fd = p[0];
}

void    hrdoc_search(t_redirect *redirect, t_envlst *envlst)
{
    t_redirect *current;

    current = redirect;
    while (current)
    {
        if (current->type == AST_HEREDOC || current->type == AST_INQ_HEREDOC)
            hrdoc_run(current, envlst);
        current = current->next;
    }
}

void    hrdoc_collect(t_ast *node, t_envlst *envlst)
{
    if (node->type == AST_PIPE)
    {
        hrdoc_collect(node->left, envlst);
        hrdoc_collect(node->right, envlst);
    }
    else if (node->type == AST_COMMAND)
        hrdoc_search(node->redirect, envlst);
}