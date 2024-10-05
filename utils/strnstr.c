#include "../include/utils.h"


static int	isn(const char *s1, const char *s2, size_t j, size_t n)
{
	size_t	i;

	i = 0;
	while (i + j < n && s2[i] && s1[i] == s2[i])
		i++;
	return (i);
}

char	*ft_strnstr( char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ln;
	size_t	y;

	i = 0;
	j = 0;
	ln = ft_strlen(needle);
	if (needle[i] == '\0')
		return ((void *)haystack);
	while (i < len && haystack[i])
	{
		y = isn(&haystack[i], needle, i, len);
		if (y == ln)
			return ((void *)&haystack[i]);
		i++;
	}
	return (0);
}
