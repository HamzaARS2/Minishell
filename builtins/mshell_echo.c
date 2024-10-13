#include "../include/builtins.h"

bool    is_flag(char *s)
{
    int i;

    i = 0;
    if (s[i++] == '-')
    {
        while (s[i] == 'n')
            i++;
        if (s[i] == '\0')
            return (true);
        else 
            return (false);
    }
    else
        return (false);
}

int dp_size(char **args)
{
    int len;

    len = 0;
    while (args[len])
        len++;
    return (len);
}

bool    mshell_echo(char **args)
{
    int i;
    int flag;
    int args_end;

    args_end = dp_size(args);
    flag = 0;
    i = 1;
    while (args[i])
    {
        if (is_flag(args[i]))
        {
            flag = is_flag(args[i]);
            i++;
            continue ;
        }
        else
        {
            ft_putstr_fd(args[i], 1);
            i++;
            if (!flag && i == args_end)
                ft_putstr_fd("\n", 1);
            continue ;
        }
    }
    return (true);
}
