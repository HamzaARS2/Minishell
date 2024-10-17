/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 11:54:55 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 07:55:38 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (dstsize <= 0)
		return (srclen);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (srclen);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	s1_bytes;
	char	*dest;

	i = 0;
	if (!s1)
		return (NULL);
	s1_bytes = ft_strlen(s1) + 1;
	dest = malloc(s1_bytes * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s1, s1_bytes);
	return (dest);
}
