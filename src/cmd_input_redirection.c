#include "../header/minishell.h"

void	infile_fd(t_vars *ms, int i)
{
	if (ms->info->input_op == -1)
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
		if (ms->info->input_op == -2)
		{
			if (!i)
				printf("%d \n", i);
			if (ms->info->fd_in != STDIN_FILENO)
				close(ms->info->fd_in);
			ms->info->fd_in = 0;					// here_doc
		}
	}
}

/* Counts the number of simple infile redirections and here_doc. */
int	ft_count_hdoc(char **string)
{
	int	i;
	int	cnt_hdoc;

	i = 0;
	cnt_hdoc = 0;
	while ((*string)[i] != '\0')
	{
		if ((*string)[i] == '<')
		{
			if ((*string)[i + 1] == '<')
				cnt_hdoc++;
		}
		i++;
	}
	return (cnt_hdoc);
}

/* Allocates memory space for the struct t_here_doc and the int array input_op. */
int	mem_alloc_hdoc(t_vars *ms, char **string)
{
	int	cnt_hdoc;
	int	j;

	j = 0;
	cnt_hdoc = ft_count_hdoc(string);
	if (cnt_hdoc == 0)
		ms->info->here_doc = NULL;
	else
	{
		ms->info->here_doc = (t_here_doc **)ft_calloc(sizeof(t_here_doc *), cnt_hdoc);
		if (!(ms->info->here_doc))
		{
			printf("Mem allocation error here_doc\n");
			return (1);
		}
		while (j < cnt_hdoc)
		{
			ms->info->here_doc[j] = ft_calloc(1, sizeof(t_here_doc));
			if (!(ms->info->here_doc))
			{
				printf("Mem allocation error here_doc\n");
				return (1);
			}
			j++;
		}
	}
	return (0);
}

/* Cuts out the redirections associated with the infile from the cmd_line. */
void	cut_infile_red(char **string)
{
	char	*tmp;
	int		i;
	int		p;

	i = 0;
	p = 0;
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
	free(*string);
	*string = NULL;
	*string = tmp;
}

/* Saves the infile in the t_info struct or the respective
limiter for a here_doc. */
void	expansion_infile_red(char **string, t_vars *ms, int i, int flag)
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
	if (flag == -2)
		ms->info->here_doc[i]->limiter = ft_substr(*string, j, k - j);
	else
		ms->info->infile = ft_substr(*string, j, k - j);
}

/* Allocates memory for the info struct and extracts the redirections and
associated files or limiters in a loop. */
void	input_redirection(t_vars *ms, char **string, int red_in)
{
	int	i;

	i = 0;
	if (mem_alloc_hdoc(ms, string) != 0)
		return ;
	while (red_in != -1)
	{
		if ((*string)[red_in] == '<')
		{
			if ((*string)[red_in + 1] == '<')
				ms->info->input_op = -2;
			else
				ms->info->input_op = -1;
		}
		expansion_infile_red(string, ms, i, ms->info->input_op);
		cut_infile_red(string);
		if (ms->info->input_op == -2)
			ft_here_doc(ms, &i, ms->info->here_doc[i]->limiter);
		infile_fd(ms, i);
		red_in = ft_strchr_pos(*string, '<');
	}
}
