#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strcpy(char *destination, const char *source)
{
	size_t	i;

	if (!destination || !source)
		return (NULL);
	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

char	*ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	dlen;

	if (!dst || !src)
		return (NULL);
	dlen = 0;
	while (dst[dlen])
		dlen++;
	i = 0;
	while (src[i])
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dst);
}
