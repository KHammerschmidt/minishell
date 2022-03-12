/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:10 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:11 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
