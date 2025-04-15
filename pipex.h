/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025/04/13 12:00:00 by student          ###   ########.fr       */
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

/* Prototipi per gestione errori e risorse */
void	error_exit(void);
void	error_msg(const char *msg);
void	close_pipes(int **pipes, int count);
void	free_pipes(int **pipes, int count);
void	clean_exit(int **pipes, int pipe_count, int infile, int outfile);
void	display_usage(char *program_name);
void	setup_normal_mode(char **argv, int *infile, int *outfile, int argc);

/* Prototipi per manipolazione stringa e parsing */
char	**parse_cmd(char *cmd);
char	*get_command_str(char **argv, int i, int here_doc_mode);
void	free_cmd_args(char **args);

/* Prototipi per here_doc */
void	here_doc_input(const char *limiter, int pipe_fd);
void	setup_heredoc(int *heredoc_pipe, char *limiter);
void	setup_here_doc_mode(char **argv, int *outfile, int argc, int *heredoc_pipe);

/* Prototipi per creazione pipe */
int		**create_pipes(int count);
void	close_all_fds(int **pipes, int pipe_count, int infile, 
					int outfile, int *heredoc_pipe, int here_doc_mode);

/* Prototipi per esecuzione comandi */
int		execute_command(char *cmd_str, char **envp, int **pipes, 
					int pipe_count, int infile, int outfile, 
					int *heredoc_pipe, int here_doc_mode);
void	child_process(int i, int cmd_count, int **pipes, int infile, 
					int outfile, int *heredoc_pipe, int here_doc_mode, 
					char **argv, char **envp);
int		process_commands(int here_doc_mode, char **argv, int cmd_count, 
					int **pipes, int infile, int outfile, 
					int *heredoc_pipe, char **envp);
void	set_up_io_first(int infile, int *heredoc_pipe, int **pipes, 
					int here_doc_mode, int cmd_count);
void	set_up_io_middle(int i, int **pipes);
void	set_up_io_last(int i, int **pipes, int outfile);

/* Prototipi per ricerca comando e path */
char	*find_command_path(char *cmd, char **envp);
char	**get_paths(char **envp);
void	free_paths(char **paths);
char	*check_path_access(char *cmd, char **paths);

void populate_args(char **args, char *cmd_copy);
char **handle_empty_cmd(void);
int populate_paths(char **paths, char *path_line);
char *find_path_line(char **envp);
char **allocate_paths_array(void);
char *create_full_path(const char *base_path, const char *cmd);

#endif