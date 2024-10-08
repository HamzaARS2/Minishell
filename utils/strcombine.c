/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcombine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:42 by helarras          #+#    #+#             */
/*   Updated: 2024/10/08 10:25:29 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	combine_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*strcombine(char *s1, char *s2, bool should_free)
{
	size_t	i;
	size_t	s1_len;
	size_t	newstrlen;
	char	*newstr;

	if (!s1 && !s2)
		return (0);
	i = 0;
	s1_len = ft_strlen(s1);
	newstrlen = s1_len + ft_strlen(s2);
	newstr = malloc(newstrlen + 1);
	if (newstr)
	{
		while (s1 && s1[i++])
			newstr[i - 1] = s1[i - 1];
		i = 0;
		while (s2 && s2[i++])
			newstr[s1_len + (i - 1)] = s2[i - 1];
		newstr[newstrlen] = 0;
	}
	if (should_free)
		combine_free(s1, s2);
	return (newstr);
}
