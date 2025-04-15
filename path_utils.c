#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**get_paths(char **envp)
{
	char		**paths;
	char		*path_line;
	int			success;

	path_line = find_path_line(envp);
	if (!path_line)
		return (NULL);
	paths = allocate_paths_array();
	if (!paths)
	{
		free(path_line);
		return (NULL);
	}
	success = populate_paths(paths, path_line);
	free(path_line);
	if (!success)
	{
		free_paths(paths);
		return (NULL);
	}
	return (paths);
}

char	*create_full_path(const char *base_path, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = strdup(base_path);
	if (!tmp)
		return (NULL);
	full_path = malloc(strlen(tmp) + strlen(cmd) + 2);
	if (!full_path)
	{
		free(tmp);
		return (NULL);
	}
	strcpy(full_path, tmp);
	strcat(full_path, "/");
	strcat(full_path, cmd);
	free(tmp);
	return (full_path);
}

char	*check_path_access(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	if (!cmd || !paths)
		return (NULL);
	while (paths[i])
	{
		full_path = create_full_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (!cmd || !cmd[0] || !envp)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (strdup(cmd));
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	path = check_path_access(cmd, paths);
	free_paths(paths);
	return (path);
}
