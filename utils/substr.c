/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:15:50 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 07:50:54 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*substr(char *str, int start, int end)
{
	char	*newstr;
	int		strsize;
	int		i;

	i = 0;
	strsize = end - start;
	if (strsize <= 0)
		return (NULL);
	newstr = malloc((strsize + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[start] && strsize > i)
		newstr[i++] = str[start++];
	newstr[i] = 0;
	return (newstr);
}
