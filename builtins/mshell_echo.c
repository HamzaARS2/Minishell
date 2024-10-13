/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:27:39 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/13 14:33:21 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

bool	is_flag(char *s, int *flag)
{
	int	i;

	i = 0;
	if (s[i++] == '-')
	{
		while (s[i] && s[i] == 'n')
			i++;
		if (s[i] == '\0' && i > 1)
			return (true);
		else
        {
            if (*flag == -1)
                *flag = 0;
			return (false);
        }
	}
	else
    {
        if (*flag == -1)
            *flag = 0;
		return (false);
    }
}

int	dp_size(char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	return (len);
}
void    put_str(char *arg, int *space)
{
    if (*space != -1)
        ft_putstr_fd(" ", 1);
    ft_putstr_fd(arg, 1);
    *space = 1;
    
}
bool	mshell_echo(char **args)
{
	int	i;
	int	flag;
	int	args_end;
    int space;

	args_end = dp_size(args);
	flag = -1;
	i = 1;
    space = -1;
	while (args[i])
	{
		if (flag != 0 && is_flag(args[i], &flag))
		{
			flag = is_flag(args[i], &flag);
			i++;
			continue ;
		}
		else
		{
            put_str(args[i], &space);
			i++;
			if ((!flag || flag == -1) && i == args_end)
				ft_putstr_fd("\n", 1);
			continue ;
		}
	}
	return (true);
}
