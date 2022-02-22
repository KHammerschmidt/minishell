/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:27:33 by khammers          #+#    #+#             */
/*   Updated: 2021/11/18 16:30:26 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Rewritten gnl for pipex. The read() function reads respectively from fd = 0
one character at a time until a '\n' or '\0' is read. Each read character is
saved in buffer[i] which is then appended by a newline and a null-termiantor.
The buffer is freed and the line returned. */
static char	*get_next_line_pipex(int fd)
{
	char		*buffer;
	char		*line;
	char		c;
	int			i;
	ssize_t		reading;

	c = 0;
	i = 0;
	reading = 0;
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
		return (NULL);
	reading = read(fd, &c, 1);
	while (reading && c != '\0' && c != '\n')
	{
		buffer[i] = c;
		i++;
		reading = read(fd, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	line = buffer;
	free(buffer);
	buffer = NULL;
	return (line);
}

/* This function duplicates the writing part of the pipe as STDOUT and writes
the returned line from gnl into pipe_fd[1] until the returned line resembles the
limiter. If so, the writing part of the pipe is closed and the child process
exited.  */
static int	ft_heredoc_pipe(t_struct *data)
{
	char	*limiter;
	char	*line;
	int		k;

	k = 0;
	limiter = data->argv[2];
	close(data->pipe_fd[0]);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		perror("dup2 here_doc STDOUT:");
	while (1)
	{
		line = get_next_line_pipex(0);
		if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(data->pipe_fd[1]);
			exit(EXIT_SUCCESS);
		}
		write(data->pipe_fd[1], line, ft_strlen(line));
	}
	return (0);
}

/* A pipe (pipe_fd) is opened and a new process forked. The child is
handled in the ft_heredoc_pipe() while the parent process duplicates
the reading part of the pipe (pipe_fd[0]) into the temporary fd
(tmp_fd). All ends of the pipes are closed and the parent waits for
the child process before returning the exit_status of the last process
of the pipex_function. */
int	ft_here_doc(t_struct *data)
{
	if (pipe(data->pipe_fd) == -1)
		ft_error(data, 1);
	data->pid2 = fork();
	if (data->pid2 < 0)
		ft_error(data, 3);
	if (data->pid2 == 0)
		ft_heredoc_pipe(data);
	if (dup2(data->pipe_fd[0], data->tmp_fd) < 0)
		perror("dup2 heredoc: ");
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	waitpid(data->pid2, &data->exit_status, 0);
	return (ft_pipex(data));
}
