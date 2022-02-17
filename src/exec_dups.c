#include "../header/minishell.h"


void	input_redirection_2(t_cmd *temp, t_vars *ms)
{
	if (temp->input_op == 0)
	{
		if (temp->previous != NULL)
		{
			if (temp->previous->pipe == 1)
			{
				if (temp->previous->output_op == -1 || temp->previous->output_op == -2)
					close(ms->pipe_fd[0]);
				else if (temp->previous->output_op == 0)
				{
					if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
						perror("dup2 infile_2 1: ");
					close(ms->tmp_fd);
				}
			}
			else if (temp->previous->pipe == 0)
				close(ms->tmp_fd);
			// if (ms->pipe_fd[0] != STDIN_FILENO)
				// close(ms->pipe_fd[0]);
		}
		else if (temp->previous == NULL)
		{
			// if (ms->pipe_fd[0] != STDIN_FILENO)
			close(ms->pipe_fd[0]);
		}
	}
}

void	input_redirection_1(t_cmd *temp, t_vars *ms)
{
	if (temp->input_op == -1)			//infile redirection			//-2 fehlt
	{
		close(ms->pipe_fd[0]);
		if (access(temp->infile, F_OK) != 0)
		{
			if (access(temp->infile, R_OK) != 0)
				perror("Error");
			else
			{
				ft_putstr_fd("zsh: No such file or directory: ", 2);
				ft_putendl_fd(temp->infile, 2);
			}
		}
		else
		{
			temp->fd_in = open(temp->infile, O_RDONLY);
			if (dup2(temp->fd_in, STDIN_FILENO) < 0)
				perror("dup2 infile1: ");
			close(temp->fd_in);
			printf("HERE hihihi\n");
		}
	}
	else if (temp->input_op == -2)
		printf("HERE DOC/n");
	if (temp->input_op == 0)
	{
		if (temp->previous != NULL)
		{
			if (temp->previous->pipe == 1)
			{
				if (temp->previous->output_op == -1 || temp->previous->output_op == -2)
					close(ms->pipe_fd[0]);
				else if (temp->previous->output_op == 0)
				{
					if (dup2(ms->pipe_fd[0], STDIN_FILENO) < 0)
						perror("dup2 infile2: ");
					close(ms->pipe_fd[0]);
				}
			}
			else if (temp->previous->pipe == 0)
				close(ms->pipe_fd[0]);
			// if (ms->pipe_fd[0] != STDIN_FILENO)
				// close(ms->pipe_fd[0]);
		}
		else if (temp->previous == NULL)
		{
			// if (ms->pipe_fd[0] != STDIN_FILENO)
			close(ms->pipe_fd[0]);
		}
	}
}

void	output_redirection(t_cmd *temp, t_vars *ms)
{
	if (temp->output_op == -1 || temp->output_op == -2)
	{
		if (temp->output_op == -1)
			temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (temp->output_op == -2)
			temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
			perror("Error");
		else
		{
			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)		//hier die Version anders für builtins (kein dup notwendig)
				perror("dup2 outfile1: ");
			close(temp->fd_out);
			close(ms->pipe_fd[1]);
		}
	}
	if (temp->output_op == 0)
	{
		if (temp->pipe == 0)
		{
			// if (ms->pipe_fd[1] != 1)
			close(ms->pipe_fd[1]);
		}
		else if (temp->pipe == 1)
		{
			printf("HERE 1\n");
			if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
				perror("dup2 outfile2: ");
			write(1, "HALLO\n", 6);
			printf("HERE 2\n");
			close(ms->pipe_fd[1]);
		}
	}
}


// ---------__________--------------------__________--------------------__________--------------------__________--------------------__________-----------

//OPEN POINTS
//multiple redirections (finding the last and dominant one)
//how to handle here_doc (open and where to dup it into)
//exceptions for the last command necessary?

/* Gnl for pipex. read() reads from fd 0. */
// static char	*get_next_line_pipex(int fd)
// {
// 	char		*buffer;
// 	char		*line;
// 	char		c;
// 	int			i;
// 	ssize_t		reading;

// 	c = 0;
// 	i = 0;
// 	reading = 0;
// 	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
// 	if (buffer == NULL)
// 		return (NULL);
// 	reading = read(fd, &c, 1);
// 	while (reading && c != '\0' && c != '\n')
// 	{
// 		buffer[i] = c;
// 		i++;
// 		reading = read(fd, &c, 1);
// 	}
// 	buffer[i] = '\n';
// 	buffer[++i] = '\0';
// 	line = buffer;
// 	free(buffer);
// 	buffer = NULL;
// 	return (line);
// }

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

// int	here_doc(t_cmd *temp, t_vars *ms)
// {
// 	char	*line;

// 	line = NULL;
// 	close(ms->pipe_fd[0]);
// 	if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
// 		perror("dup2 here_doc STDOUT:");
// 	while (1)
// 	{
// 		line = get_next_line_pipex(0);
// 		if (ft_strncmp_pipex(line, temp->infile, ft_strlen(temp->infile)) == 0)
// 		{
// 			printf("LIMITER FOUND\n");
// 			close(ms->pipe_fd[1]);
// 			return (0);
// 		}
// 		write(ms->pipe_fd[1], line, ft_strlen(line));
// 	}
// }



// ____________________________________________________________________________________________________________________________________________
//BACKUP 2


int	input_redirection(t_cmd *temp, t_vars *ms)
{
	if (ft_lstsize_cmd(ms->cmd) == 1)
		return (0);
	else if (temp->previous == NULL && temp->input_op == 0)
	{
		//erster command, keine input redirection und nur ein command
		close(ms->pipe_fd[0]);
	}
	else if (temp->input_op == 0 && temp->previous != NULL)
	{
		//keine input redirection
		if (dup2(ms->pipe_fd[0], STDIN_FILENO) < 0)
			perror("dup2: infile1: ");
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
				perror("dup2 infile2: ");
			close(temp->fd_in);
		}
	}
	else if (temp->previous->pipe == 1)
	{
		// there is no previous input STDIN bleibt STDIN
		if (temp->previous->fd_out == -1 || temp->previous->fd_out == -2)
			return (0);
		//previous cmd comes from a pipe
		if (dup2(ms->pipe_fd[0], STDIN_FILENO) < 0)
			perror("dup2: infile3: ");
		// close(ms->pipe_fd[0]);
	}
	// else if (temp->input_op == -2)
	// {
	// 	// here_doc
	// 	close(ms->pipe_fd[0]);
	// 	char	*line;

	// 	line = NULL;
	// 	if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
	// 		perror("dup2 here_doc STDOUT:");
	// 	while (1)
	// 	{
	// 		line = get_next_line_pipex(0);
	// 		if (ft_strncmp_pipex(line, temp->infile, ft_strlen(temp->infile)) == 0)
	// 		{
	// 			printf("LIMITER FOUND\n");
	// 			close(ms->pipe_fd[1]);
	// 			return (0);
	// 			// break ;
	// 		}
	// 		write(ms->pipe_fd[1], line, ft_strlen(line));
	// 	}
	// }
	return (0);
}

int	output_redirection(t_cmd *temp, t_vars *ms)
{
	if (ft_lstsize_cmd(ms->cmd) == 1)
		return (0);
	else if (ft_lstsize_cmd(ms->cmd) == 1 && temp->output_op == 0)
	{
		//nur ein cmd (kein duplicaten notwendig)
		close(ms->pipe_fd[1]);
	}
	else if (temp->output_op == 0 && temp->pipe == 0)
	{
		// kein output file und keine redirection oder pipe
		close(ms->pipe_fd[1]);
	}
	else if (temp->output_op == -1)
	{
		//output redirection
		close(ms->pipe_fd[1]);
		temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
			perror("Error");
		else
		{
			if (dup2(temp->fd_out, STDOUT_FILENO) < 0)				//hier die Version anders für builtins (kein dup notwendig)
				perror("dup2 outfile1: ");
		}
		// close(temp->fd_out);
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
				perror("dup2 outfile2: ");
		}
	}
	else if (temp->pipe == 1)	//&& temp->output_op == 0?	//außer wenn here_doc
	{
		//builtings
		temp->fd_out = ms->pipe_fd[1];

		// cmd:
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
				perror("dup2 outfile3: ");
		close(ms->pipe_fd[1]);
	}
	else if (temp->next == NULL)
		close(ms->pipe_fd[1]);
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

