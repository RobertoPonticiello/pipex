/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/13 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	clean_exit(int **pipes, int pipe_count, int infile, int outfile)
{
	close_pipes(pipes, pipe_count);
	free_pipes(pipes, pipe_count);
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
	exit(EXIT_FAILURE);
}

void	display_usage(char *program_name)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  Normal: %s infile cmd1 cmd2 ... cmdN outfile\n", 
			program_name);
	fprintf(stderr, "  here_doc: %s here_doc LIMITER cmd1 cmd2 ... cmdN outfile\n", 
			program_name);
	exit(EXIT_FAILURE);
}

void	setup_normal_mode(char **argv, int *infile, int *outfile, int argc)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
		perror(argv[1]);
	*outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
		perror(argv[argc - 1]);
}