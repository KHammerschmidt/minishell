#include "../header/minishell.h"

//OPEN POINTS
//multiple redirections (finding the last and dominant one)
//how to handle here_doc (open and where to dup it into)
//exceptions for the last command necessary?

/* Rewritten gnl for pipex. The read() function reads respectively from fd = 0
one character at a time until a '\n' or '\0' is read. Each read character is
saved in buffer[i] which is then appended by a newline and a null-termiantor.
The buffer is freed and the line returned. */
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

/* The function ft_strncmp() compares lexicographically the null-terminated
strings s1 and s2 but not more than n characters. Characters that appear
after null-terminator are not compared. The function returns an integer
greater than, equal to or less than 0, according as s1 is greater than,
equal to or less than string 2. Comparison is done using unsigned
characters. */
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

/* Checks if there is a pipe in the previous command.
Afterwards searches for a prioritised redirection in input_op. */
// int	input_redirection(t_cmd *temp, t_vars *ms)
// {
	// close(ms->pipe_fd[0]);
	//second and following commands / maybe extra part for the last command
	// if(temp->previous != NULL)
	// {
	// 	//input comes from a previous pipe, no other input redirections		//tmp_fd?
	// 	if (temp->input_op == 0 && temp->previous->pipe == 1)
	// 	{
	// 		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
	// 			perror("dup2 infile: ");
	// 		return (0);
	// 	}
	// 	//input is not taken from previous pipe but from the overwriting input redirection
	// 	else if (temp->input_op == -1)
	// 	{
	// 		if (access(temp->infile, F_OK) != 0)
	// 		{
	// 			ft_putstr_fd("zsh: No such file or directory: ", 2);
	// 			ft_putendl_fd(temp->infile, 2);
	// 			ft_free_string(temp->execpath);
	// 			exit(1);//exit?
	// 		}
	// 		if (access(temp->infile, R_OK) != 0)
	// 		{
	// 			perror("Error");
	// 			ft_free_string(temp->execpath);
	// 			exit(1);//exit?
	// 		}
	// 		temp->fd_in = open(temp->infile, O_RDONLY);
	// 		if (dup2(temp->fd_in, STDIN_FILENO) < 0)
	// 			perror("dup2 infile: ");
	// 		close(temp->fd_in);
	// 		return (0);
	// 	}
	// 	//input comes from here_doc (read into char *line and written to pipe_fd[1])
	// 	else if (temp->input_op == -2)
	// 	{
	// 		char	*line;
	// 		char	*limiter;

	// 		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
	// 			perror("dup2 here_doc STDOUT: ");
	// 		while (1)
	// 		{
	// 			line = get_next_line_pipex(0);
	// 			if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
	// 			{
	// 				close(ms->pipe_fd[1]);
	// 				exit(EXIT_SUCCESS);
	// 			}
	// 		}
	// 		write(ms->pipe_fd[1], line, ft_strlen(line));
	// 		return (0);
	// 	}
	// }
	//first command
	// if (temp->previous == NULL)
	// {
	// 	//kein input
	// 	if (temp->input_op == 0)			// keine redirection
	// 	{
	// 		if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
	// 			perror("dup2: infile: ");
	// 		return (0);
	// 	}
		//infile redirection
		// else if (temp->input_op == -1)
		// {
		// 	if (access(temp->infile, F_OK) != 0)
		// 	{
		// 		ft_putstr_fd("zsh: No such file or directory: ", 2);
		// 		ft_putendl_fd(temp->infile, 2);
		// 		ft_free_string(temp->execpath);
		// 		exit(1);//exit?
		// 	}
		// 	if (access(temp->infile, R_OK) != 0)
		// 	{
		// 		perror("Error");
		// 		ft_free_string(temp->execpath);
		// 		exit(1);//exit?
		// 	}
		// 	temp->fd_in = open(temp->infile, O_RDONLY);
		// 	if (dup2(temp->fd_in, STDIN_FILENO) < 0)
		// 		perror("dup2 infile: ");
		// 	close(temp->fd_in);
		// 	return (0);
		// }
		// //here_doc
		// else if (temp->input_op == -2)
		// {
		// 	char	*line;
		// 	char	*limiter;

		// 	if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
		// 		perror("dup2 here_doc STDOUT: ");
		// 	while (1)
		// 	{
		// 		line = get_next_line_pipex(0);
		// 		if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
		// 		{
		// 			close(ms->pipe_fd[1]);
		// 			exit(EXIT_SUCCESS);
		// 		}
		// 	}
		// 	write(ms->pipe_fd[1], line, ft_strlen(line));
		// 	return (0);
		// }
// 	}
// 	return (0);
// }

// int	output_redirection(t_cmd *temp, t_vars *ms)
// {
	// if ("here_doc found") // 	ft_here_doc_out(ms);
	// output goes into a pipe
	// kein output file und keine redirection
	// if (temp->output_op == 0 && temp->pipe == 0)
	// {
	// 	if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
	// 		perror("dup2 outfile: ");
	// 	return (0);
	// }
	// else if (temp->pipe == 1 && temp->output_op == 0)
	// {
	// 	if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
	// 		perror("dup2 outfile: ");
	// 	return (0);
	// }
	// outfile redirection im truncate mode
	// else if (temp->output_op == -1)
	// {
	// 	close(ms->pipe_fd[1]);
	// 	temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	// 	if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
	// 	{
	// 		perror("Error");
	// 		ft_free_string(temp->execpath);
	// 		exit(1);//exit?
	// 	}
	// 	if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
	// 		perror("dup2 outfile1: ");
	// 	return (0);
	// }
	// // outfile redirection im append mode
	// else if (temp->output_op == -2)
	// {
	// 	close(ms->pipe_fd[1]);
	// 	temp->fd_out = open(temp->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	// 	if (temp->fd_out == -1 || access(temp->outfile, W_OK) != 0)
	// 	{
	// 		perror("Error");
	// 		ft_free_string(temp->execpath);
	// 		exit(1);//exit?
	// 	}
	// 	if (dup2(temp->fd_out, STDOUT_FILENO) < 0)
	// 		perror("dup2 outfile1: ");
	// 	return (0);
	// }
// 	return (0);
// }


int	input_redirection(t_cmd *temp, t_vars *ms)
{
	//erster command
	if (temp->previous == NULL)
	{
		//kein input
		if (temp->input_op == 0)			// keine redirection
		{
			if (ft_lstsize_cmd(ms->cmd) == 1)
			{
				close(ms->pipe_fd[1]);
				close(ms->pipe_fd[0]);
				// if (dup2(ms->pipe_fd[0], STDIN_FILENO) < 0)
				// 	perror("dup2: infile: ");
			}
			// else
			// {
			// 	close(ms->pipe_fd[0]);
			// 	if (dup2(ms->tmp_fd, STDIN_FILENO) < 0)
			// 		perror("dup2: infile: ");
			// }
		}
		//infile redirection
		// if (temp->input_op == -1)
		// {
		// 	if (access(temp->infile, F_OK) != 0)
		// 	{
		// 		ft_putstr_fd("zsh: No such file or directory: ", 2);
		// 		ft_putendl_fd(temp->infile, 2);
		// 		ft_free_string(temp->execpath);
		// 		exit(1);//exit?
		// 	}
		// 	if (access(temp->infile, R_OK) != 0)
		// 	{
		// 		perror("Error");
		// 		ft_free_string(temp->execpath);
		// 		exit(1);//exit?
		// 	}
		// 	temp->fd_in = open(temp->infile, O_RDONLY);
		// 	if (dup2(temp->fd_in, STDIN_FILENO) < 0)
		// 		perror("dup2 infile: ");
		// 	close(temp->fd_in);
		// 	return (0);
		// }
	}
	return (0);
}

int	output_redirection(t_cmd *temp, t_vars *ms)
{
	//nur ein cmd (kein duplicaten notwendig)
	if (ft_lstsize_cmd(ms->cmd) == 1)
	{
		close(ms->pipe_fd[0]);
		close(ms->pipe_fd[1]);
		return (0);
	}
	// kein output file und keine redirection
	if (temp->output_op == 0 && temp->pipe == 0)
	{
		close(ms->pipe_fd[0]);
		// close(ms->pipe_fd[1]);
		if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2 outfile: ");
		return (0);
	}
	return (0);
}
