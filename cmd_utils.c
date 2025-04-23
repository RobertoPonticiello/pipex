/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:30 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:30 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**handle_empty_cmd(void)
{
	char	**args;

	args = malloc(sizeof(char *));
	if (!args)
		error_exit();
	args[0] = NULL;
	return (args);
}

char	**parse_cmd(char *cmd)
{
	char	**args;
	char	*cmd_copy;

	if (!cmd || cmd[0] == '\0')
		return (handle_empty_cmd());
	cmd_copy = ft_strdup(cmd);
	if (!cmd_copy)
		error_exit();
	args = malloc(sizeof(char *) * 64);
	if (!args)
	{
		free(cmd_copy);
		error_exit();
	}
	populate_args(args, cmd_copy);
	free(cmd_copy);
	return (args);
}

void	populate_args(char **args, char *cmd_copy)
{
	int		index;
	char	*token;

	index = 0;
	token = ft_strtok(cmd_copy, " ");
	while (token != NULL && index < 63)
	{
		args[index] = ft_strdup(token);
		if (!args[index])
		{
			while (index > 0)
				free(args[--index]);
			free(args);
			error_exit();
		}
		index++;
		token = ft_strtok(NULL, " ");
	}
	args[index] = NULL;
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

char	*get_command_str(t_pipex *pipex, int i)
{
	char	*cmd_str;

	if (pipex->here_doc_mode)
		cmd_str = ft_strdup(pipex->argv[i + 3]);
	else
		cmd_str = ft_strdup(pipex->argv[i + 2]);
	if (!cmd_str)
		error_exit();
	return (cmd_str);
}
