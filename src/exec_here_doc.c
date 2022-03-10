#include "../header/minishell.h"

/* Checks whether delimiter has open (-1), double (0) or single quotes (1)
which would influence the dollar expansion of the read line. */
static int	hdoc_dollar_sign(char *limiter)
{
	int		i;
	int		quote_on;
	int		quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	while (limiter[i] != '\0')
	{
		if ((limiter[i] == 34 || limiter[i] == 39) && quote_on == 0)
			quote_type = limiter[i];
		if (limiter[i] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
		}
		i++;
	}
	if (quote_on != 0)
		return (-1);
	if (quote_on == 0 && quote_type == 39)
		return (1);
	return (0);
}

/* Checks if content of here_doc is subject to dollar sign expansion
with dollar_flag. Cuts quotes from the delimiter. */
int	prepare_hdoc_expansion(t_vars *ms, int *dollar_flag, char **limiter)
{
	char	*temp;

	temp = NULL;
	*dollar_flag = hdoc_dollar_sign(*limiter);
	if (*dollar_flag == -1)
	{
		ms->info.flag = 1;
		printf("Error: open quote in limiter\n");
		return (-1);
	}
	temp = cut_quotes(*limiter);
	ft_free_string(limiter);
	*limiter = ft_strdup(temp);
	ft_free_string(&temp);
	return (0);
}

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

/* Reads with readline() into a pipe until delimiter, which becomes STDIN. */
int	ft_here_doc(t_vars *ms, char *limiter)
{
	int		dollar_flag;
	int		hdoc_pipe_fd[2];
	int		fd;
	char	*line;

	line = NULL;
	dollar_flag = 0;
	fd = dup(STDIN_FILENO);
	if (prepare_hdoc_expansion(ms, &dollar_flag, &limiter) == -1
		|| hdoc_hdle_pipe_fds_init(ms, hdoc_pipe_fd) == -1)
		return (-1);
	rl_init(1);
	while (1)
	{
		line = readline("heredoc> ");
		line = hdoc_dollar_expansion(ms, line, dollar_flag);
		if (line == NULL || \
			ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		sending_input_and_reset(&line, hdoc_pipe_fd);
	}
	rl_reset();
	hdoc_hdle_pipe_fds_end(hdoc_pipe_fd, fd, &line);
	return (0);
}
