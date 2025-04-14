/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/13 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		if (pipe(pipes[i]) == -1)
		{
			while (i >= 0)
				free(pipes[i--]);
			free(pipes);
			error_exit();
		}
		i++;
	}
	return (pipes);
}

void	close_all_fds(int **pipes, int pipe_count, int infile,
					int outfile, int *heredoc_pipe, int here_doc_mode)
{
	int	i;

	i = 0;
	if (pipes)
	{
		while (i < pipe_count)
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
	if (!here_doc_mode && infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
	if (here_doc_mode && heredoc_pipe && heredoc_pipe[0] >= 0)
		close(heredoc_pipe[0]);
}

void	setup_here_doc_mode(char **argv, int *outfile, int argc, int *heredoc_pipe)
{
	if (!argv || !outfile || !heredoc_pipe || argc < 4)
		return ;
	*outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*outfile < 0)
		perror(argv[argc - 1]);
	heredoc_pipe[0] = -1;
	heredoc_pipe[1] = -1;
	setup_heredoc(heredoc_pipe, argv[2]);
}