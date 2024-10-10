
#include "../include/builtins.h"

void    display_error(char *intro, char *body, char *conclusion)
{
    ft_putstr_fd(intro, 2);
    ft_putstr_fd(body, 2);
    ft_putstr_fd(conclusion, 2);
}