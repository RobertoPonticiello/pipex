#include "pipex.h"

int execute_command(char *cmd_str, char **envp, int **pipes,
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
		close_all_fds(pipes, pipe_count, infile, outfile, heredoc_pipe, here_doc_mode);
		exit(0);
	}
	path = find_command_path(cmd_args[0], envp);
	if (!path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd_args[0]);
		free_cmd_args(cmd_args);
		close_all_fds(pipes, pipe_count, infile, outfile, heredoc_pipe, here_doc_mode);
		exit(127);
	}
	execve(path, cmd_args, envp);
	free(path);
	free_cmd_args(cmd_args);
	perror("execve");
	close_all_fds(pipes, pipe_count, infile, outfile, heredoc_pipe, here_doc_mode);
	exit(1);
}

void	here_doc_input(const char *limiter, int pipe_fd)
{
	size_t	len;
	char	*line;
	size_t	line_len;

	len = 0;
	line = NULL;
	if (!limiter || pipe_fd < 0)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (getline(&line, &len, stdin) == -1)
			break ;
		if (!line)
			break ;
		line_len = strlen(line);
		if (line_len > 0 && line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (strcmp(line, limiter) == 0)
			break ;
		write(pipe_fd, line, strlen(line));
		write(pipe_fd, "\n", 1);
	}
	if (line)
		free(line);
	close(pipe_fd);
}
// Trova la riga PATH nell'ambiente
char *find_path_line(char **envp)
{
    int i;

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

// Alloca la memoria per l'array di percorsi
char **allocate_paths_array(void)
{
    char **paths;
    
    paths = malloc(sizeof(char *) * 64);
    return (paths);
}

// Popola l'array dei percorsi
int populate_paths(char **paths, char *path_line)
{
    int i;
    char *path_var;
    
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