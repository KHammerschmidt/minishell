#include "../header/minishell.h"

/* Reads with readline() into a pipe until delimiter, which becomes STDIN. */
int	ft_here_doc(t_vars *ms, char *limiter)
{
	int		hdoc_pipe_fd[2];
	char	*line;

	line = NULL;
	if (ms->tmp_fd != STDIN_FILENO)
	{
		close(ms->tmp_fd);
		ms->tmp_fd = dup(STDIN_FILENO);
	}
	if (pipe(hdoc_pipe_fd) == -1)
		printf("PIPE ERROR\n");
	if (dup2(hdoc_pipe_fd[0], ms->tmp_fd) < 0)
		perror("dup2 hdoc_fd into tmp_fd: ");
	close(hdoc_pipe_fd[0]);
	// signal(SIGINT, signal_handler3);
	// signal(SIGQUIT, signal_handler3);
	while (1)
	{
		line = readline("heredoc> ");	// line = dollar_expansion();	//für string umschreiben
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		write(hdoc_pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	close(hdoc_pipe_fd[1]);
	free(line);
	return (0);
}
