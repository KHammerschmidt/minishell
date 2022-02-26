#include "../header/minishell.h"

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
// int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (1);
// 	while (s1[i] == s2[i])
// 	{
// 		if (s1[i + 1] == '\0' && s2[i + 1] == '\0')
// 			return ((unsigned char)s1[i + 1] - (unsigned char)s2[i + 1]);
// 		if ((i + 1) == n)
// 			break ;
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

// int	ft_strncmp_pipex(char *s1, char *s2, size_t n)
// {
// 	size_t i;

// 	i = 0;
// 	if (n == 0)
// 		return (1);
// 	s2 = ft_strjoin_2(s2, "\n", 1);
// 	printf(" line: %s limiter: %s\n", s1, s2);
// 	while (s1[i] == s2[i])
// 	{
// 		if (s1[i] == '\0' || s2[i] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	if (s1[i + 1] == '\n')
// 		return (0);
// 	if (s1[i + 1] != '\0')
// 		return (1);
// 	return (0);
// }

/* Creates a new pipe, reading part of the part is connected to pipe
in struct. GNL writes into fd[1] and breaks when the delimiter is found. */
// int	ft_here_doc(t_vars *ms, char *limiter)
// {
// 	int		hdoc_pipe_fd[2];
// 	char	*line;

// 	line = NULL;
// 	if (ms->tmp_fd != STDIN_FILENO)
// 	{
// 		close(ms->tmp_fd);
// 		ms->tmp_fd = dup(STDIN_FILENO);
// 	}
// 	if (pipe(hdoc_pipe_fd) == -1)
// 		printf("PIPE ERROR\n");
// 	if (dup2(hdoc_pipe_fd[0], ms->tmp_fd) < 0)
// 		perror("dup2 hdoc_fd into tmp_fd: ");
// 	close(hdoc_pipe_fd[0]);
// 	while (1)
// 	{
// 		line = get_next_line_pipex(0);
// 		if (ft_strncmp_pipex(line, limiter, ft_strlen(limiter + 1)) == 0)
// 			break ;
// 		write(hdoc_pipe_fd[1], line, ft_strlen(line));
// 	}
// 	close(hdoc_pipe_fd[1]);
// 	return (0);
// }

		// if (compare_str(line, limiter) == 0)
		// 	break ;
			// && ft_strlen(line) == ft_strlen(limiter))



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
	while (1)
	{
		line = readline("heredoc> ");	// line = dollar_expansion();	//für string umschreiben
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		write(hdoc_pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(hdoc_pipe_fd[1]);
	free(line);
	return (0);
}