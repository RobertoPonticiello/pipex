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

void	handle_io_error(t_pipex *pipex)
{
	close_all_fds(pipex);
	free_pipes(pipex->pipes, pipex->cmd_count - 1);
	error_exit();
}

void	cclean_exit(t_pipex *pipex, char **cmd_args, char *path, int exit_code)
{
	if (path)
		free(path);
	if (cmd_args)
		free_cmd_args(cmd_args);
	close_all_fds(pipex);
	if (pipex->pipes)
		free_pipes(pipex->pipes, pipex->cmd_count - 1);
	exit(exit_code);
}
