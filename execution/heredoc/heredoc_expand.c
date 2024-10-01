
#include "../../include/execution.h"

void    uhrdoc_clear(t_vinfo vinfo)
{
    free(vinfo.variable);
    free(vinfo.value);
    vinfo = (t_vinfo) {0};
}

void    uhrdoc_envval_cpy(t_vinfo vinfo, char *line, char *newline)
{
    uint32_t    i;
    uint32_t    val_i;
    uint32_t    new_i;

    i = 0;
    val_i = 0;
    new_i = 0;
    while (line[i] && i < vinfo.i)
        newline[new_i++] = line[i++];
    while (vinfo.value && vinfo.value[val_i])
    {
        newline[new_i + val_i] = vinfo.value[val_i];
        val_i++;
    }
    i += vinfo.varsize;
    new_i += vinfo.valsize;
    while (line[i])
        newline[new_i++] = line[i++];
    free(line);
    line = NULL;
    newline[new_i] = 0;
}


void    uhrdoc_expand_env(t_vinfo *vinfo, t_envlst *envlst)
{
    t_envlst *current;
    uint32_t varsize;
    char    *var;

    var = vinfo->variable + 1;
    varsize = vinfo->varsize - 1;
    current = envlst;
    while (current)
    {
        if (varsize > 0 && !ft_strncmp(current->variable, var, varsize))
        {
            vinfo->value = ft_strdup(current->variable + varsize + 1);
            vinfo->valsize = ft_strlen(vinfo->value);
            return ;
        }
        current = current->next;
    }
    return ;
}

char    *uhrdoc_envname(char *str)
{
    int i;

    i = 1;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    return (substr(str, 0, i));
}

void    uhrdoc_next_env(t_vinfo *vinfo, char *line)
{
    static int i;

    while (line[i])
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
        {
            vinfo->variable = uhrdoc_envname(line + i);
            vinfo->varsize = ft_strlen(vinfo->variable);
            vinfo->i = i;
            i += vinfo->varsize;
            return ;
        }
        i++;
    }
    i = 0;
    vinfo->variable = NULL;
    return ;
}