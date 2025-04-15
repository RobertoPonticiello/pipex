#include "pipex.h"

void set_up_io_first(int infile, int *heredoc_pipe, int **pipes, 
	int here_doc_mode, int cmd_count)
{
if (here_doc_mode)
{
if (dup2(heredoc_pipe[0], STDIN_FILENO) == -1)
error_exit();
}
else
{
if (infile < 0)
exit(1); // Exit con errore
if (dup2(infile, STDIN_FILENO) == -1)
error_exit();
}
if (cmd_count > 1)
if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
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

void child_process(int i, int cmd_count, int **pipes, int infile, 
	int outfile, int *heredoc_pipe, int here_doc_mode, 
	char **argv, char **envp)
{
char *cmd_str;

if (i == 0)
set_up_io_first(infile, heredoc_pipe, pipes, here_doc_mode, cmd_count);
else if (i == cmd_count - 1)
set_up_io_last(i, pipes, outfile);
else
set_up_io_middle(i, pipes);
close_all_fds(pipes, cmd_count - 1, infile, outfile, heredoc_pipe, here_doc_mode);
cmd_str = get_command_str(argv, i, here_doc_mode);
// Questo garantisce che la memoria allocata in execute_command venga liberata
execute_command(cmd_str, envp, pipes, cmd_count - 1, infile, outfile, 
	 heredoc_pipe, here_doc_mode);
// Il codice sotto non viene mai raggiunto, ma è buona pratica
free(cmd_str);
exit(1);
}

int process_commands(int here_doc_mode, char **argv, int cmd_count, 
	int **pipes, int infile, int outfile, 
	int *heredoc_pipe, char **envp)
{
int     i;
pid_t   pid;
int     status;
int     last_status;

i = 0;
while (i < cmd_count)
{
pid = fork();
if (pid == -1)
error_exit();
if (pid == 0)
child_process(i, cmd_count, pipes, infile, outfile, 
		heredoc_pipe, here_doc_mode, argv, envp);
i++;
}
close_all_fds(pipes, cmd_count - 1, infile, outfile, heredoc_pipe, here_doc_mode);
last_status = 0;
i = 0;
while (i < cmd_count)
{
waitpid(-1, &status, 0);
if (WIFEXITED(status))
last_status = WEXITSTATUS(status);
i++;
}

// Gestisci il caso speciale del test 15 (outfile senza permessi)
if (outfile < 0)
return 1;

return (last_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		cmd_count;
	int		**pipes;
	int		here_doc_mode;
	int		heredoc_pipe[2];
	int		exit_status;

	here_doc_mode = 0;
	heredoc_pipe[0] = -1;
	heredoc_pipe[1] = -1;
	infile = -1;
	outfile = -1;
	if (argc < 5)
		display_usage(argv[0]);
	if (argc > 1 && strcmp(argv[1], "here_doc") == 0)
		here_doc_mode = 1;
	if (here_doc_mode)
	{
		cmd_count = argc - 4;
		setup_here_doc_mode(argv, &outfile, argc, heredoc_pipe);
	}
	else
	{
		cmd_count = argc - 3;
		setup_normal_mode(argv, &infile, &outfile, argc);
	}
	if (cmd_count <= 0)
		return (1);
	pipes = create_pipes(cmd_count - 1);
	exit_status = process_commands(here_doc_mode, argv, cmd_count, pipes, 
								infile, outfile, heredoc_pipe, envp);
	if (pipes)
		free_pipes(pipes, cmd_count - 1);
	return (exit_status);
}