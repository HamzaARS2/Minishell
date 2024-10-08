#include "../include/builtins.h"

t_builtins_type    builtin_check(char *cmd)
{
    uint32_t length;

    length = ft_strlen(cmd);
    if (!ft_strncmp(cmd, "cd", length))
        return (CD);
    else if (!ft_strncmp(cmd, "export", length))
        return (EXPORT);
    return (NONE);
}