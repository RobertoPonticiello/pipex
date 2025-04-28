/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimateutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:20:54 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/28 19:22:28 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_command_not_found(t_pipex *pipex, char **cmd_args)
{
	char	*error_message;

	error_message = malloc(ft_strlen(cmd_args[0]) + 20);
	if (!error_message)
		cclean_exit(pipex, cmd_args, NULL, 127);
	ft_strcpy(error_message, "Command not found: ");
	ft_strcat(error_message, cmd_args[0]);
	write(2, error_message, ft_strlen(error_message));
	write(2, "$\n", 2);
	free(error_message);
	cclean_exit(pipex, cmd_args, NULL, 127);
}
