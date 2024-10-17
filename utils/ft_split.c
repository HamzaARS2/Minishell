/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:00:26 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 07:55:01 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

static int	count_words(char *str, char delimeter)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == delimeter)
			i++;
		while (str[i] && str[i] != delimeter)
			i++;
		if (i > 0 && str[i - 1] != delimeter)
			count++;
	}
	return (count);
}

static void	freewords(char **words, int i)
{
	while (i >= 0 && words[i])
		free(words[i--]);
	free(words);
}

static char	**strcut(char **words, char *str, char delimeter, int wcount)
{
	int	i;
	int	ccount;
	int	windex;

	i = 0;
	ccount = 0;
	windex = 0;
	while (str[i] && windex < wcount)
	{
		while (str[i] == delimeter)
			i++;
		while (str[i + ccount] && str[i + ccount] != delimeter)
			ccount++;
		words[windex] = substr(str, i, i + ccount);
		if (!words[windex])
		{
			freewords(words, windex - 1);
			return (0);
		}
		i += ccount;
		ccount = 0;
		windex++;
	}
	words[windex] = NULL;
	return (words);
}

char	**ft_split(char *str, char c)
{
	int		wcount;
	char	**words;

	if (!str)
		return (0);
	wcount = count_words(str, c);
	words = malloc((wcount + 1) * sizeof(char *));
	if (!words || !strcut(words, str, c, wcount))
		return (0);
	return (words);
}
