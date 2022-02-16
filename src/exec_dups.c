#include "../header/minishell.h"

//OPEN POINTS
//multiple redirections (finding the last and dominant one)
//how to handle here_doc (open and where to dup it into)
//exceptions for the last command necessary?

/* Gnl for pipex. read() reads from fd 0. */
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

/* Compares lexicographically the null-terminated strings, not more than
n characters. Returns an integer greater than, equal to or less than 0
if s1 is greater than, equal to or less than s2.  */
int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (s1[i] == s2[i])
	{
		if (s1[i + 1] == '\0' && s2[i + 1] == '\0')
			return ((unsigned char)s1[i + 1] - (unsigned char)s2[i + 1]);
		if ((i + 1) == n)
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	input_redirection(t_cmd *temp, t_vars *ms)
{
	if (temp->previous == NULL && temp->input_op == 0 && ft_lstsize_cmd(ms->cmd) == 1)
	{
		//erster command, keine input redirection und nur ein command
		close(ms->pipe_fd[1]);
		close(ms->pipe_fd[0]);
	}
	else if (temp->input_op == 0)
	{
		//keine input redirection
		close(ms->pipe_fd[1]);
		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			perror("dup2: infile: ");
		close(ms->pipe_fd[0]);
	}
	else if (temp->input_op == -1)
	{
		//infile redirection
		close(ms->pipe_fd[0]);
		if (access(temp->infile, F_OK) != 0)
		{
			ft_putstr_fd("zsh: No such file or directory: ", 2);
			ft_putendl_fd(temp->infile, 2);
		}
		if (access(temp->infile, F_OK) == 0 && access(temp->infile, R_OK) != 0)
			perror("Error");
		else
		{
			temp->fd_in = open(temp->infile, O_RDONLY);
			if (dup2(temp->fd_in, STDIN_FILENO) < 0)
				perror("dup2 infile: ");
			close(temp->fd_in);
		}
	}
	else if (temp->input_op == -2)
	{
		// here_doc
		char	*line;
		char	*limiter;

		line = NULL;
		limiter = NULL;
		while (1)
		{
			line = get_next_line_pipex(0);
			if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
			{
				close(ms->pipe_fd[1]);
				break ;
			}
		}
		write(ms->pipe_fd[1], line, ft_strlen(line));
	}
	else if (temp->previous->pipe == 1)
	{
		//previous cmd comes from a pipe
		close(ms->pipe_fd[1]);
		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			perror("dup2: infile: ");
		close(ms->pipe_fd[0]);

	}
	return (0);
}

int	output_redirection(t_cmd *temp, t_vars *ms)
{
	if (ft_lstsize_cmd(ms->cmd) == 1 && temp->output_op == 0)
	{
		//nur ein cmd (kein duplicaten notwendig)
		close(ms->pipe_fd[0]);
		close(ms->pipe_fd[1]);
	}
	else if (temp->output_op == 0 && temp->pipe == 0)
	{
		// kein output file und keine redirection oder pipe
		close(ms->pipe_fd[0]);
		close(ms->pipe_fd[1]);
	}
	else if (temp->output_op == -1)
	{
		//output redirection
		close(ms->pipe_fd[0]);
		close(ms->pipe_fd[1]);
		temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
			perror("Error");
		else
		{
			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
			perror("dup2 outfile1: ");
		}
	}
	else if (temp->output_op == -2)
	{
		// outfile redirection im truncate mode
		close(ms->pipe_fd[1]);
		temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
			perror("Error");
		else
		{
			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
				perror("dup2 outfile1: ");
		}
		close(ms->pipe_fd[0]);
	}
	else if (temp->pipe == 1)	//&& temp->output_op == 0?
	{
		close(ms->pipe_fd[0]);
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
				perror("dup2 outfile: ");
		close(ms->pipe_fd[1]);
	}
	return (0);
}


// ------------------------------------------------------------------------------------------------
// BACKUP

// int	input_redirection(t_cmd *temp, t_vars *ms)
// {
// 	if (temp->previous == NULL && temp->input_op == 0 && ft_lstsize(ms->cmd) == 1)
// 	{
// 		//erster command, keine input redirection und nur ein command
// 		close(ms->pipe_fd[1]);
// 		close(ms->pipe_fd[0]);
// 	}
// 	else if (temp-input_op == 0)
// 	{
// 		//keine input redirection
// 		close(ms->pipe_fd[1]);
// 		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
// 			perror("dup2: infile: ");
// 		close(ms->pipe_fd[0]);
// 	}
// 	else if (temp->input_op == -1)
// 	{
// 		//infile redirection
// 		close(ms->pipe_fd[0]);
// 		if (access(temp->infile, F_OK) != 0)
// 		{
// 			ft_putstr_fd("zsh: No such file or directory: ", 2);
// 			ft_putendl_fd(temp->infile, 2);
// 			// ft_free_string(temp->execpath);
// 			// exit(1);//exit?
// 		}
// 		if (access(temp->infile, R_OK) != 0)
// 		{
// 			perror("Error");
// 			// ft_free_string(temp->execpath);
// 			// exit(1);//exit?
// 		}
// 		else
// 		{
// 			temp->fd_in = open(temp->infile, O_RDONLY);
// 			if (dup2(temp->fd_in, STDIN_FILENO) < 0)
// 				perror("dup2 infile: ");
// 			close(temp->fd_in);
// 		}
// 	}
// 	else if (temp->input_op == -2)
// 	{
// 		// here_doc
// 		printf("HEREDOC\n");
// 		char	*line;
// 		char	*limiter;

// 		// if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
// 		// 	perror("dup2 here_doc STDOUT: ");
// 		while (1)
// 		{
// 			line = get_next_line_pipex(0);
// 			if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
// 			{
// 				close(ms->pipe_fd[1]);
// 				break ;
// 				// exit(EXIT_SUCCESS);
// 			}
// 		}
// 		write(ms->pipe_fd[1], line, ft_strlen(line));
// 	}
// 	else if (temp->previous->pipe == 1)
// 	{
// 		//previous cmd comes from a pipe
// 		close(ms->pipe_fd[1]);
// 		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
// 			perror("dup2: infile: ");
// 		close(ms->pipe_fd[0]);

// 	}
// 	return (0);
// }

// int	output_redirection(t_cmd *temp, t_vars *ms)
// {
// 	if (ft_lstsize_cmd(ms->cmd) == 1 && temp->output_op == 0)
// 	{
// 		//nur ein cmd (kein duplicaten notwendig)
// 		close(ms->pipe_fd[0]);
// 		close(ms->pipe_fd[1]);
// 	}
// 	else if (temp->output_op == 0 && temp->pipe == 0)
// 	{
// 		// kein output file und keine redirection oder pipe
// 		close(ms->pipe_fd[0]);
// 		close(ms->pipe_fd[1]);
// 	}
// 	else if (temp->output_op == -1)
// 	{
// 		//output redirection
// 		close(ms->pipe_fd[0]);
// 		close(ms->pipe_fd[1]);
// 		temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
// 		{
// 			perror("Error");
// 			// ft_free_string(temp->execpath);
// 			// exit(1);//exit?
// 		}
// 		else
// 		{
// 			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
// 			perror("dup2 outfile1: ");
// 		}
// 	}
// 	else if (temp->output_op == -2)
// 	{
// 		// outfile redirection im truncate mode
// 		close(ms->pipe_fd[1]);
// 		temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
// 		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
// 		{
// 			perror("Error");
// 			// ft_free_string(temp->execpath);
// 			// exit(1);//exit?
// 		}
// 		else
// 		{
// 			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
// 				perror("dup2 outfile1: ");
// 		}
// 		close(ms->pipe_fd[0]);
// 	}
// 	else if (temp->pipe == 1)	//&& temp->output_op == 0?
// 	{
// 		close(ms->pipe_fd[0]);
// 		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
// 				perror("dup2 outfile: ");
// 		close(ms->pipe_fd[1]);
// 	}
// 	return (0);
// }

