#include "../include/builtins.h"

t_builtins_type    builtin_check(char *cmd)
{
    if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
        return (CD);
    return (NONE);
}