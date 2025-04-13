/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/13 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_cmd(char *cmd)
{
	char	**args;
	int		index;
	char	*cmd_copy;
	char	*token;

	if (!cmd || cmd[0] == '\0')
	{
		args = malloc(sizeof(char *));
		if (!args)
			error_exit();
		args[0] = NULL;
		return (args);
	}
	cmd_copy = strdup(cmd);
	if (!cmd_copy)
		error_exit();
	args = malloc(sizeof(char *) * 64);
	if (!args)
	{
		free(cmd_copy);
		error_exit();
	}
	index = 0;
	token = strtok(cmd_copy, " ");
	while (token != NULL)
	{
		args[index] = strdup(token);
		if (!args[index])
		{
			while (index > 0)
				free(args[--index]);
			free(args);
			free(cmd_copy);
			error_exit();
		}
		index++;
		token = strtok(NULL, " ");
	}
	args[index] = NULL;
	free(cmd_copy);
	return (args);
}

void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*get_command_str(char **argv, int i, int here_doc_mode)
{
	char	*cmd_str;
	
	if (here_doc_mode)
		cmd_str = strdup(argv[i + 3]);
	else
		cmd_str = strdup(argv[i + 2]);
	if (!cmd_str)
		error_exit();
	return (cmd_str);
}

int	execute_command(char *cmd_str, char **envp, int **pipes, 
					int pipe_count, int infile, int outfile, 
					int *heredoc_pipe, int here_doc_mode)
{
	char	**cmd_args;
	char	*path;

	cmd_args = parse_cmd(cmd_str);
	free(cmd_str);
	if (!cmd_args[0])
	{
		free_cmd_args(cmd_args);
		return (0);
	}
	path = find_command_path(cmd_args[0], envp);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_args[0]);
		free_cmd_args(cmd_args);
		close_all_fds(pipes, pipe_count, infile, outfile, heredoc_pipe, here_doc_mode);
		exit(127);
	}
	if (execve(path, cmd_args, envp) == -1)
	{
		free(path);
		free_cmd_args(cmd_args);
		error_msg("execve");
		close_all_fds(pipes, pipe_count, infile, outfile, heredoc_pipe, here_doc_mode);
		exit(1);
	}
	return (0);
}

void	here_doc_input(const char *limiter, int pipe_fd)
{
	size_t	len;
	char	*line;
	size_t	line_len;

	len = 0;
	line = NULL;
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (getline(&line, &len, stdin) == -1)
			break ;
		line_len = strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (strcmp(line, limiter) == 0)
			break ;
		write(pipe_fd, line, strlen(line));
		write(pipe_fd, "\n", 1);
	}
	free(line);
	close(pipe_fd);
}