#include "../include/builtins.h"

int i = 0;
void    atoi_perror(char *str)
{
    printf("exit\n");
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    exit (255); //bash exist with 255 in this arg's case
}

void    size_check(unsigned long number, int sign, char *str)
{
    if (number > 9223372036854775808ULL && sign == -1)
        atoi_perror(str);
    if (number > 9223372036854775807 && sign == 1)
        atoi_perror(str);
}

int	ft_atoi(char *str)
{
	int				i;
	int				sign;
	unsigned long	number;

	number = 0;
	sign = 1;
	i = 0;
	while (str && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str && (str[i] >= 32 && str[i] <= 126))
	{
        if ( str[i] >= '0' && str[i] <= '9')
		    number = number * 10 + str[i++] - '0';
        else
            atoi_perror(str);
        size_check(number, sign, str);
	}
	return (number *= sign);
}

bool    mshell_exit(char **arg)
{
    int     i;
    char    *trim_arg;
    int     E_status;

    i = 0;
    while (arg[i])
        i++;
    if (i == 1)
    {
        printf("exit\n");
        exit(24); //*EXIT WITH EXIT_STATUS
    }
    else if (i >= 2)
    {
        if (!arg[1][0])
            atoi_perror(arg[1]);
        else if (i == 2)
            E_status = ft_atoi(ft_strtrim(arg[1], " "));
        else if (i > 2)
        {
            ft_atoi(ft_strtrim(arg[1], " "));
            ft_putstr_fd("bash: exit: too many arguments\n", 2);
            //(*TODO) UPDATE THE EXIST_STATUS TO 1
            return (false);
        }
    }
    printf("exit\n");
    exit(E_status);
}
