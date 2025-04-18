/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:44 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:44 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_command(char *cmd_str, t_pipex *pipex)
{
	char	**cmd_args;
	char	*path;

	cmd_args = parse_cmd(cmd_str);
	free(cmd_str);
	if (!cmd_args[0])
	{
		free_cmd_args(cmd_args);
		close_all_fds(pipex);
		exit(0);
	}
	path = find_command_path(cmd_args[0], pipex->envp);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_args[0]);
		free_cmd_args(cmd_args);
		close_all_fds(pipex);
		exit(127);
	}
	execve(path, cmd_args, pipex->envp);
	free(path);
	free_cmd_args(cmd_args);
	perror("execve");
	close_all_fds(pipex);
	exit(1);
}

void	here_doc_input(const char *limiter, int pipe_fd)
{
	size_t	len;
	char	*line;
	int		should_break;

	len = 0;
	line = NULL;
	should_break = 0;
	if (!limiter || pipe_fd < 0)
		return ;
	while (!should_break)
	{
		write(1, "heredoc> ", 9);
		if (getline(&line, &len, stdin) == -1)
			break ;
		process_heredoc_line(line, limiter, pipe_fd, &should_break);
	}
	if (line)
		free(line);
	close(pipe_fd);
}

char	*find_path_line(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	**allocate_paths_array(void)
{
	char	**paths;

	paths = malloc(sizeof(char *) * 64);
	return (paths);
}

int	populate_paths(char **paths, char *path_line)
{
	int		i;
	char	*path_var;

	i = 0;
	path_var = strtok(path_line, ":");
	while (path_var != NULL && i < 63)
	{
		paths[i] = strdup(path_var);
		if (!paths[i])
			return (0);
		i++;
		path_var = strtok(NULL, ":");
	}
	paths[i] = NULL;
	return (1);
}
