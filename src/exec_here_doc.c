#include "../header/minishell.h"

// '<<'
//3.6.6 Here Documents
// This type of redirection instructs the shell to read input from the current source until a line containing only word (with no trailing blanks) i
// s seen. All of the lines read up to that point are then used as the standard input (or file descriptor n if n is specified) for a command.
// The format of here-documents is:
// [n]<<[-]word
//         here-document
// delimiter
// No parameter and variable expansion, command substitution, arithmetic expansion, or filename expansion is performed on word. If any part of word is
// quoted, the delimiter is the result of quote removal on word, and the lines in the here-document are not expanded. If word is unquoted, all lines
// of the here-document are subjected to parameter expansion, command substitution, and arithmetic expansion, the character sequence \newline is ignored,
// and ‘\’ must be used to quote the characters ‘\’, ‘$’, and ‘`’.
// If the redirection operator is ‘<<-’, then all leading tab characters are stripped from input lines and the line containing delimiter. This allows
// here-documents within shell scripts to be indented in a natural fashion.

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

int	ft_here_doc(t_vars *ms, int *i, char *limiter)
{
	// char	*limiter;
	char	*line;

	line = NULL;
	printf("HERE\n");
	// limiter = ms->info->here_doc[*i]->limiter;
	ms->info.here_doc[*i]->text = ft_strdup("");
	while (1)
	{
		line = get_next_line_pipex(0);
		if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter)) == 0)
		{
			printf("LIMITER FOUND\n");
			// close(ms->pipe_fd[1]);
			break ;
		}
		ms->info.here_doc[*i]->text = ft_strjoin(ms->info.here_doc[*i]->text, line);
		// write(ms->pipe_fd[1], line, ft_strlen(line));
	}
	// ms->info->here_doc->text = line;
	(*i)++;
	printf("%s \n", ms->info.here_doc[*i]->text);
	return (0);
}

//  OLD
// int	here_doc(t_cmd *temp, t_vars *ms)
// {
// 	char	*line;

// 	line = NULL;
// 	// close(ms->pipe_fd[0]);
// 	// if (dup2(ms->pipe_fd[1], STDOUT_FILENO) < 0)
// 	// 	perror("dup2 here_doc STDOUT:");
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
