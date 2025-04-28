/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moremoreutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:34 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:34 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_heredoc_line(char *line, const char *limiter,
			int pipe_fd, int *should_break)
{
	size_t	line_len;

	if (!line)
	{
		*should_break = 1;
		return ;
	}
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	if (strcmp(line, limiter) == 0)
	{
		*should_break = 1;
		return ;
	}
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", 1);
}

static int	is_delim(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*start;

	if (str)
		save = str;
	if (!save)
		return (NULL);
	while (*save && is_delim(*save, delim))
		save++;
	if (!*save)
		return (NULL);
	start = save;
	while (*save && !is_delim(*save, delim))
		save++;
	if (*save)
		*save++ = '\0';
	return (start);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*r;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
