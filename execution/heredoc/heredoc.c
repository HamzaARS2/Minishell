
#include "../../include/execution.h"

char    *hrdoc_replace_env(t_vinfo vinfo, char *line)
{
    uint32_t    linesize;
    char        *newline;
    uint32_t    newsize;

    linesize = ft_strlen(line);
    newsize = linesize - vinfo.varsize + vinfo.valsize;
    newline = malloc((newsize + 1) * sizeof(char));
    if (!newline)
        return (NULL);
    newline[newsize] = 0;
    uhrdoc_envval_cpy(vinfo, line, newline);
    return (newline);
}

char    *hrdoc_expand(t_envlst *envlst, char *line)
{
    int     i;
    t_vinfo vinfo;

    vinfo = (t_vinfo) {0};
    while (true)
    {
        uhrdoc_next_env(&vinfo, line);
        if (!vinfo.variable)
            break;
        uhrdoc_expand_env(&vinfo, envlst);
        line = hrdoc_replace_env(vinfo, line);
    }
    uhrdoc_clear(vinfo);
    return (line);
}

void    hrdoc_run(t_redirect *heredoc, t_envlst *envlst)
{
    int p[2];
    char *line;
    uint32_t linesize;

    pipe(p);
    while (true)
    {
        line = readline("heredoc > ");
        if (!line)
            break;
        linesize = ft_strlen(line);
        if (linesize > 0 && !ft_strncmp(line, heredoc->content, linesize))
           break;
        line = hrdoc_expand(envlst, line);
        write(p[1], line, linesize);
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
        if (current->type == AST_HEREDOC)
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