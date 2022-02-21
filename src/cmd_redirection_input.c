#include "../header/minishell.h"

/* In case of infile redirection, the access rights to the
files are checked before it is opend and the fd is saved. */
static void	infile_fd(t_vars *ms)
{
	if (ms->info->fd_in != STDIN_FILENO)
		close(ms->info->fd_in);
	if (access(ms->info->infile, F_OK) != 0)
	{
		if (access((ms->info->infile), R_OK) != 0)
			perror("Error");
		else
		{
			ft_putstr_fd("zsh: No such file or directory: ", 2);
			ft_putendl_fd((ms->info->infile), 2);
		}
	}
	else
	{
		ms->info->fd_in = open((ms->info->infile), O_RDONLY);
		if (ms->info->fd_in == -1)
			perror("Error: ");
	}
}

/* Cuts out the redirections associated with the infile from the cmd_line. */
static void	cut_infile_red(char **string)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while ((*string)[i] != '<')
	{
		tmp = ft_strnjoin(tmp, (*string)[i], 1);
		i++;
	}
	while ((*string)[i] == '<')
		i++;
	while ((*string)[i] == ' ' && (*string)[i] != '\0')
		i++;
	i++;
	while ((*string)[i] != ' ' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] == ' ' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] != '\0')
		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
	ft_free_string(*string);
	*string = tmp;
}

/* Saves the infile in the t_info struct or the respective
limiter for a here_doc. */
static void	expansion_infile_red(char **string, t_vars *ms)
{
	int		k;
	int		j;

	k = 0;
	j = ft_strchr_pos(*string, '<');
	while (((*string)[j] == '<' || (*string)[j] == ' ') && (*string)[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '\0')
		k++;
	ms->info->infile = ft_substr(*string, j, k - j);
}

/* Allocates memory for the info struct and extracts the redirections and
associated files or limiters in a loop. */
void	input_redirection(t_vars *ms, char **string, int red_in)
{
	while (red_in != -1)
	{
		if ((*string)[red_in] == '<')
		{
			if ((*string)[red_in + 1] == '<')
				ms->info->input_op = -2;
			else
				ms->info->input_op = -1;
		}
		expansion_infile_red(string, ms);
		cut_infile_red(string);
		if (ms->info->input_op == -2)
			ft_here_doc(ms, ms->info->infile);
		else if (ms->info->input_op == -1)
			infile_fd(ms);
		red_in = ft_strchr_pos(*string, '<');
	}
}
