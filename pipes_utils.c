#include "pipex.h"

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < count)
	{
		if (pipes[i])
		{
			if (pipes[i][0] >= 0)
				close(pipes[i][0]);
			if (pipes[i][1] >= 0)
				close(pipes[i][1]);
		}
		i++;
	}
}

void	free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (i < count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	if (count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * count);
	if (!pipes)
		error_exit();
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			error_exit();
		}
		init_pipe(pipes, i);
		i++;
	}
	return (pipes);
}

void	close_all_fds(t_pipex *pipex)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = pipex->cmd_count - 1;
	if (pipex->pipes)
	{
		while (i < pipe_count)
		{
			if (pipex->pipes[i])
			{
				if (pipex->pipes[i][0] >= 0)
					close(pipex->pipes[i][0]);
				if (pipex->pipes[i][1] >= 0)
					close(pipex->pipes[i][1]);
			}
			i++;
		}
	}
	if (!pipex->here_doc_mode && pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->here_doc_mode && pipex->heredoc_pipe[0] >= 0)
		close(pipex->heredoc_pipe[0]);
}

void	setup_here_doc_mode(t_pipex *pipex, int argc)
{
	if (!pipex->argv || argc < 4)
		return ;
	pipex->outfile = open(pipex->argv[argc - 1],
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (pipex->outfile < 0)
		perror(pipex->argv[argc - 1]);
	pipex->heredoc_pipe[0] = -1;
	pipex->heredoc_pipe[1] = -1;
	setup_heredoc(pipex->heredoc_pipe, pipex->argv[2]);
}
