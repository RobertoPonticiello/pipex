#include "pipex.h"

void	error_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	error_msg(const char *msg)
{
	perror(msg);
}

void	clean_exit(t_pipex *pipex)
{
	if (pipex->pipes)
	{
		close_pipes(pipex->pipes, pipex->cmd_count - 1);
		free_pipes(pipex->pipes, pipex->cmd_count - 1);
	}
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	exit(EXIT_FAILURE);
}

void	display_usage(char *program_name)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr,
		"Normal: %s infile cmd1 cmd2 ... cmdN outfile\n",
		program_name);
	fprintf(stderr,
		"here_doc: %s here_doc LIMITER cmd1 cmd2 ... cmdN outfile\n",
		program_name);
	exit(EXIT_FAILURE);
}

void	setup_normal_mode(t_pipex *pipex, int argc)
{
	if (!pipex->argv || argc < 4)
		return ;
	pipex->infile = open(pipex->argv[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(pipex->argv[1]);
	pipex->outfile = open(pipex->argv[argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->outfile < 0)
		perror(pipex->argv[argc - 1]);
}
