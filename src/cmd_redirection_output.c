#include "../header/minishell.h"

/* Cuts out the redirections associated with the outfile from the cmd_line. */
void	cut_outfile_red(char **string)
{
	char	*tmp;
	int		i;
	// int		p;

	i = 0;
	// p = 0;
	tmp = NULL;
	while ((*string)[i] != '>')
	{
		tmp = ft_strnjoin(tmp, (*string)[i], 1);
		i++;
	}
	while ((*string)[i] == '>')
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

/* Saves the outfile in the t_info struct. */
void expansion_outfile_red(char **string, t_vars *ms)
{
	int		k;
	int		j;
	char	*tmp;

	k = 0;
	j = ft_strchr_pos((*string), '>');
	while (((*string)[j] == '>' || (*string)[j] == ' ') && (*string)[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '\0')
		k++;
	tmp = ft_substr((*string), j, k - j);
	ms->info.outfile = tmp;
}

void	outfile_fd(t_vars *ms)
{
	if (ms->info.output_op == -1)
	{
		if (ms->info->fd_out != STDOUT_FILENO)
			close(ms->info->fd_out);
		ms->info->fd_out = open(ms->info->outfile,
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	if (ms->info.output_op == -2)
	{
		if (ms->info->fd_out != STDOUT_FILENO)
			close(ms->info->fd_out);
		ms->info->fd_out = open(ms->info->outfile,
			O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	if (ms->info.fd_out == -1 || access(ms->info.outfile, W_OK) != 0)
		perror("Error");
}

void	output_redirection(t_vars *ms, char **string, int red_out)
{
	while (red_out != -1)
	{
		if ((*string)[red_out] == '>')
		{
			if ((*string)[red_out + 1] == '>')
				ms->info.output_op = -2;
			else
				ms->info.output_op = -1;
		}
		expansion_outfile_red(string, ms);
		cut_outfile_red(string);
		outfile_fd(ms);
		red_out = ft_strchr_pos(*string, '>');
	}
}
