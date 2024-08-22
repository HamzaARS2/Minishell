/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:08:05 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 16:23:48 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int    ft_strlen(char *str)
{
    unsigned int i;
    
    i = 0;
    while (str && str[i])
        i++;
    return (i);
}