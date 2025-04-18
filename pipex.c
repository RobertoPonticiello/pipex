/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:47 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:47 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_up_io_first(t_pipex *pipex)
{
	if (pipex->here_doc_mode)
	{
		if (dup2(pipex->heredoc_pipe[0], STDIN_FILENO) == -1)
			error_exit();
	}
	else
	{
		if (pipex->infile < 0)
			exit(1);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			error_exit();
	}
	if (pipex->cmd_count > 1)
		if (dup2(pipex->pipes[0][1], STDOUT_FILENO) == -1)
			error_exit();
}

void	set_up_io_middle(int i, int **pipes)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		error_exit();
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		error_exit();
}

void	set_up_io_last(int i, int **pipes, int outfile)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		error_exit();
	if (outfile < 0)
		exit(1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit(1);
}

void	child_process(int i, t_pipex *pipex)
{
	char	*cmd_str;

	if (i == 0)
		set_up_io_first(pipex);
	else if (i == pipex->cmd_count - 1)
		set_up_io_last(i, pipex->pipes, pipex->outfile);
	else
		set_up_io_middle(i, pipex->pipes);
	close_all_fds(pipex);
	cmd_str = get_command_str(pipex, i);
	execute_command(cmd_str, pipex);
	free(cmd_str);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	initialize_pipex(&pipex, argc, argv, envp);
	if (pipex.cmd_count <= 0)
		return (1);
	pipex.pipes = create_pipes(pipex.cmd_count - 1);
	exit_status = process_commands(&pipex);
	if (pipex.pipes)
		free_pipes(pipex.pipes, pipex.cmd_count - 1);
	return (exit_status);
}
