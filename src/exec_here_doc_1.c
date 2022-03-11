#include "../header/minishell.h"

/* Sets the right fds for redirection and opens the pipe. */
static int	hdoc_hdle_pipe_fds_init(t_vars *ms, int *hdoc_pipe_fd)
{
	ms->tmp_fd = dup(STDIN_FILENO);
	if (pipe(hdoc_pipe_fd) == -1)
	{
		printf("PIPE ERROR\n");
		return (-1);
	}
	if (dup2(hdoc_pipe_fd[0], ms->tmp_fd) < 0)
	{
		perror("dup2 hdoc_fd into tmp_fd: ");
		return (-1);
	}
	close(hdoc_pipe_fd[0]);
	return (0);
}

static void	hdoc_hdle_pipe_fds_end(int *hdoc_pipe_fd, int fd, char **line)
{
	close(hdoc_pipe_fd[1]);
	dup2(fd, STDIN_FILENO);
	ft_free_string(line);
}

static void	sending_input_and_reset(char **line, int *hdoc_pipe_fd)
{
	write(hdoc_pipe_fd[1], *line, ft_strlen(*line));
	write(hdoc_pipe_fd[1], "\n", 1);
	ft_free_string(line);
}

/* Reads the here_doc input line calling readling(), expands $-signs when
appropriate and checks whether the limiter has been found. If not, input to
written to the pipe, if limiter has been found, 1 is returned. */
static int	hdoc_input(t_vars *ms, int d_flag, char *limiter, int *hdoc_pipe_fd)
{
	char	*line;

	line = NULL;
	line = readline("heredoc> ");
	line = hdoc_dollar_expansion(ms, line, d_flag);
	if (line == NULL || ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		return (1);
	sending_input_and_reset(&line, hdoc_pipe_fd);
	return (0);
}

/* Reads with readline() into a pipe until delimiter, which becomes STDIN. */
int	ft_here_doc(t_vars *ms)
{
	int		d_flag;
	int		hdoc_pipe_fd[2];
	int		fd;
	char	*line;
	char	*limiter;

	line = NULL;
	d_flag = 0;
	fd = dup(STDIN_FILENO);
	limiter = ft_strdup(ms->info.infile);
	if (prepare_hdoc_expansion(ms, &d_flag, &limiter) == -1
		|| hdoc_hdle_pipe_fds_init(ms, hdoc_pipe_fd) == -1)
		return (-1);
	rl_init(1);
	while (1)
	{
		if (hdoc_input(ms, d_flag, limiter, hdoc_pipe_fd) != 0)
			break ;
	}
	rl_reset();
	hdoc_hdle_pipe_fds_end(hdoc_pipe_fd, fd, &line);
	ft_free_string(&(ms->info.infile));
	return (0);
}
