#include "../include/execution.h"
size_t	ft_strlcpy(char *dst,  char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	lss;
	size_t	ls;

	lss = 0;
	if (!s)
		return (0);
	ls = ft_strlen(s);
	if (start > ls)
	{
		lss = 0;
		start = ls;
	}
	else if (ls - start < len)
		lss = ls - start;
	else if (ls - start >= len)
		lss = len;
	ss = malloc(lss * sizeof(char) + 1);
	if (ss == 0)
		return (0);
	ft_strlcpy(ss, &s[start], lss + 1);
	return (ss);
}
static size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	word;

	word = 1;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && word == 1)
		{
			count++;
			word = 0;
		}
		else if (s[i] == c)
			word = 1;
		i++;
	}
	return (count);
}

static size_t	sslen(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static void	ft_free(char **s, size_t j)
{
	while (j > 0)
	{
		free(s[--j]);
	}
	free(s);
}

static char	**split1(char *s, char c, char **r)
{
	size_t	i;
	size_t	j;
	size_t	ssl;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			ssl = sslen(&s[i], c);
			r[j] = ft_substr(&s[i], 0, ssl);
			if (!r[j])
			{
				ft_free(r, j);
				return (0);
			}
			j++;
			i = i + ssl;
		}
	}
	r[j] = 0;
	return (r);
}

char	**ft_split(char *s, char c)
{
	char	**r;

	if (s == 0)
		return (0);
	r = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (r == 0)
		return (0);
	return (split1(s, c, r));
}
