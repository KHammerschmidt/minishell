#include "../header/minishell.h"

/* In case of infile redirection, the access rights to the
files are checked before it is opend and the fd is saved. */
static int	infile_fd(t_vars *ms)
{
	if (ms->info.fd_in != STDIN_FILENO)
		close(ms->info.fd_in);
	if (access(ms->info.infile, F_OK) != 0)
	{
		if (access((ms->info.infile), R_OK) != 0)
			perror("Error");
		else
		{
			ft_putstr_fd("zsh: No such file or directory: ", 2);
			ft_putendl_fd((ms->info.infile), 2);
		}
		ms->exit_status = 1;
		return (1);
	}
	else
	{
		ms->info.fd_in = open((ms->info.infile), O_RDONLY);
		if (ms->info.fd_in == -1)
		{
			ft_putstr_fd("Error: permission denied: ", 2);
			ft_putendl_fd((ms->info.infile), 2);
			ms->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

/* Cuts out the redirections associated with the infile from the cmd_line. */
static void	cut_infile_red(char **string, int fd_in)		//spaces!!!!
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < fd_in)
	{
		tmp = ft_strnjoin(tmp, (*string)[i], 1);
		i++;
	}
	while ((*string)[i] == '<')
		i++;
	while ((*string)[i] == ' ')
		i++;
	while ((*string)[i] != ' ' && (*string)[i] != '<' && (*string)[i] != '\0')
		i++;

	// while ((*string)[i] == ' ' && (*string)[i] != '<' && (*string)[i] != '\0')
	// 	i++;
	// i++;
	// while ((*string)[i] != ' ' && (*string)[i] != '<' && (*string)[i] != '\0')
	// 	i++;
	while ((*string)[i] == ' ' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] != '\0')
		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
	ft_free_string(string);
	*string = ft_strdup(tmp);
	ft_free_string(&tmp);
}

/* Saves the infile in the t_info struct. */
static void	expansion_infile_red(char **string, t_vars *ms, int j)
{
	int	k;

	k = 0;
	while (((*string)[j] == '<' || (*string)[j] == ' ') && (*string)[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '<' && (*string)[k] != '\0')
		k++;
	ft_free_string(&ms->info.infile);
	ms->info.infile = ft_substr(*string, j, k - j);
}

/* Rxtracts the redirections and associated files or limiters in a loop. */
int	input_redirection(t_vars *ms, char **string, int red_in)
{
	while (red_in != -1)
	{
		if ((*string)[red_in] == '<' && valid_red(*string, red_in) == 0)
		{
			if ((*string)[red_in + 1] == '<')
				ms->info.input_op = -2;
			else
				ms->info.input_op = -1;
		}
		else
		{
			red_in = ft_strchr_pos_red(*string, '<', red_in + 2);
			continue ;
		}
		expansion_infile_red(string, ms, red_in);
		cut_infile_red(string, red_in);
		if (ms->info.input_op == -2)
			ft_here_doc(ms, ms->info.infile);
		else if (ms->info.input_op == -1)
		{
			if (infile_fd(ms) == 1)
				return (1);
		}
		red_in = ft_strchr_pos(&(*string)[red_in], '<');
	}
	return (0);
}
