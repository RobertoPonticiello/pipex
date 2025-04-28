/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpontici <rpontici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:39:50 by rpontici          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:50 by rpontici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		cmd_count;
	int		**pipes;
	int		here_doc_mode;
	int		heredoc_pipe[2];
	char	**argv;
	char	**envp;
}	t_pipex;

void	error_exit(void);
void	error_msg(const char *msg);
void	close_pipes(int **pipes, int count);
void	free_pipes(int **pipes, int count);
void	clean_exit(t_pipex *pipex);
void	display_usage(char *program_name);
void	setup_normal_mode(t_pipex *pipex, int argc);
char	**parse_cmd(char *cmd);
char	*get_command_str(t_pipex *pipex, int i);
void	free_cmd_args(char **args);
void	here_doc_input(const char *limiter, int pipe_fd);
void	setup_heredoc(int *heredoc_pipe, char *limiter);
void	setup_here_doc_mode(t_pipex *pipex, int argc);
int		**create_pipes(int count);
void	close_all_fds(t_pipex *pipex);
int		execute_command(char *cmd_str, t_pipex *pipex);
void	child_process(int i, t_pipex *pipex);
int		process_commands(t_pipex *pipex);
void	set_up_io_first(t_pipex *pipex);
void	set_up_io_middle(int i, t_pipex *pipex);
void	set_up_io_last(int i, t_pipex *pipex);
char	*find_command_path(char *cmd, char **envp);
char	**get_paths(char **envp);
void	free_paths(char **paths);
char	*check_path_access(char *cmd, char **paths);
void	populate_args(char **args, char *cmd_copy);
char	**handle_empty_cmd(void);
int		populate_paths(char **paths, char *path_line);
char	*find_path_line(char **envp);
char	**allocate_paths_array(void);
char	*create_full_path(const char *base_path, const char *cmd);
void	init_pipe(int **pipes, int i);
int		wait_for_processes(t_pipex *pipex);
void	initialize_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void	process_heredoc_line(char *line, const char *limiter,
			int pipe_fd, int *should_break);
char	*ft_strtok(char *str, const char *delim);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
char	*ft_strcpy(char *destination, const char *source);
char	*ft_strcat(char *dst, const char *src);
void	handle_io_error(t_pipex *pipex);
void	cclean_exit(t_pipex *pipex, char **cmd_args, char *path, int exit_code);

#endif