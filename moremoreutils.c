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
