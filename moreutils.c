#include "pipex.h"

void	setup_heredoc(int *heredoc_pipe, char *limiter)
{
	if (!heredoc_pipe || !limiter)
		return ;
	if (pipe(heredoc_pipe) == -1)
		error_exit();
	here_doc_input(limiter, heredoc_pipe[1]);
}
