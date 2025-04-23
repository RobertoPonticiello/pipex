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
	line_len = strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	if (strcmp(line, limiter) == 0)
	{
		*should_break = 1;
		return ;
	}
	write(pipe_fd, line, strlen(line));
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
