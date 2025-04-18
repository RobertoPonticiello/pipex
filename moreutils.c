#include "pipex.h"

void	setup_heredoc(int *heredoc_pipe, char *limiter)
{
	if (!heredoc_pipe || !limiter)
		return ;
	if (pipe(heredoc_pipe) == -1)
		error_exit();
	here_doc_input(limiter, heredoc_pipe[1]);
}

void	init_pipe(int **pipes, int i)
{
	pipes[i][0] = -1;
	pipes[i][1] = -1;
	if (pipe(pipes[i]) == -1)
	{
		while (i >= 0)
			free(pipes[i--]);
		free(pipes);
		error_exit();
	}
}

int	wait_for_processes(t_pipex *pipex)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	if (pipex->outfile < 0)
		return (1);
	return (last_status);
}

int	process_commands(t_pipex *pipex)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid == -1)
			error_exit();
		if (pid == 0)
			child_process(i, pipex);
		i++;
	}
	close_all_fds(pipex);
	return (wait_for_processes(pipex));
}

void	initialize_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->here_doc_mode = 0;
	pipex->heredoc_pipe[0] = -1;
	pipex->heredoc_pipe[1] = -1;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->argv = argv;
	pipex->envp = envp;
	if (argc < 5)
		display_usage(argv[0]);
	if (argc > 1 && strcmp(argv[1], "here_doc") == 0)
		pipex->here_doc_mode = 1;
	if (pipex->here_doc_mode)
	{
		pipex->cmd_count = argc - 4;
		setup_here_doc_mode(pipex, argc);
	}
	else
	{
		pipex->cmd_count = argc - 3;
		setup_normal_mode(pipex, argc);
	}
}
