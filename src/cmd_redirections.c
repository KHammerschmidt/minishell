#include "../header/minishell.h"

/* Cuts out the redirections associated with the infile from the cmd_line. */
void	ft_cut_infile_redirections(char **string, t_vars *ms)
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
	if ((*string)[i] == '<')
		i++;
	while ((*string)[i] == ' ' && (*string)[i] != '\0')
		i++;
	i++;
	while ((*string)[i] != ' ' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] == ' ' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] != '\0')
		tmp = ft_strnjoin(tmp, *string[i++], 1);
	free(*string);
	*string = NULL;
	*string = tmp;
	ms->cmd_line = tmp;
}

/* Saves the infile in the t_info struct. */
void	infile_redirection(char **string, t_vars *ms)
{
	int		k;
	int		j;
	char	*tmp;

	k = 0;
	j = ft_strchr_pos(*string, '<');
	while ((*string[j] == '<' || *string[j] == ' ') && *string[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '\0')
		k++;
	tmp = ft_substr(*string, j, k - j);
	ms->info->infile = tmp;
	printf("infile: ..%s..\n", ms->info->infile);
	free(tmp);
	ft_cut_infile_redirections(string, ms);
}

/* Cuts out the redirections associated with the outfile from the cmd_line. */
void	ft_cut_outfile_redirections(char **string, t_vars *ms)
{
	char	*tmp;
	int		i;
	int		p;

	i = 0;
	p = 0;
	tmp = NULL;
	while (*string[i] != '>')
		tmp = ft_strnjoin(tmp, *string[i++], 1);
	if (*string[i] == '>')
		i++;
	while (*string[i] == ' ' && *string[i] != '\0')
		i++;
	i++;
	while (*string[i] != ' ' && *string[i] != '\0')
		i++;
	while (*string[i] == ' ' && *string[i] != '\0')
		i++;
	while (*string[i] != '\0')
		tmp = ft_strnjoin(tmp, *string[i++], 1);
	free(*string);
	*string = NULL;
	*string = tmp;
	ms->cmd_line = tmp;
}

/* Saves the outfile in the t_info struct. */
void outfile_redirection(char **string, t_vars *ms)
{
	int		k;
	int		j;
	char	*tmp;

	k = 0;
	j = ft_strchr_pos(*string, '>');
	while ((*string[j] == '>' || *string[j] == ' ') && *string[j] != '\0')
		j++;
	k = j;
	while (*string[k] != ' ' && *string[k] != '\0')
		k++;
	tmp = ft_substr(*string, j, k - j);
	ms->info->outfile = tmp;
	free(tmp);
	printf("outfile: ..%s..\n", ms->info->outfile);
	ft_cut_outfile_redirections(string, ms);
}



void	check_redirections(char **string, int pipe_marker, t_vars *ms)		//*string = ms->cmd_line;
{
	int		pos;

	printf("*string: %s\n", *string);
	pos = ft_strchr_pos(*string, '<');													//returns -1 if no redirection has been found or the position of the redirection
	while (pos != -1 && (pos <= ft_strchr_pos(*string, '|') || pipe_marker == -1))		// check if redirection is before the next pipe
	{
		if (*string[pos] == '<' && *string[pos + 1] == '<')						//check for '<<'
			printf("READ INPUT FROM THE CURRENT SOURCE\n");
		else																				//single '<'
			infile_redirection(string, ms);
		pos = ft_strchr_pos(*string, '<');												//check for multiple redirections
	}
	pos = ft_strchr_pos(*string, '>');
	while (pos != -1 && (pos <= ft_strchr_pos(*string, '|') || pipe_marker == -1))		// check if redirection is before the next pipe
	{
		if (*string[pos] == '>' && *string[pos + 1] == '>')
			printf("REDIRECTS OUTPUT WITH APPEND MODE\n");
		else
			outfile_redirection(string, ms);
		pos = ft_strchr_pos(*string, '>');
	}
}


//---------------------------------------------------------------------------------------------------------------------------------------

// /* Cuts out the redirections associated with the infile from the cmd_line. */
// void	ft_cut_infile_redirections(t_vars *ms)
// {
// 	char	*tmp;
// 	int		i;
// 	int		p;

// 	i = 0;
// 	p = 0;
// 	tmp = NULL;
// 	while (ms->cmd_line[i] != '<')
// 		tmp = ft_strnjoin(tmp, ms->cmd_line[i++], 1);
// 	if (ms->cmd_line[i] == '<')
// 		i++;
// 	while (ms->cmd_line[i] == ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	i++;
// 	while (ms->cmd_line[i] != ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	while (ms->cmd_line[i] == ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	while (ms->cmd_line[i] != '\0')
// 		tmp = ft_strnjoin(tmp, ms->cmd_line[i++], 1);
// 	free(ms->cmd_line);
// 	ms->cmd_line = NULL;
// 	ms->cmd_line = tmp;
// }

// /* Saves the infile in the t_info struct. */
// void	infile_redirection(t_vars *ms)
// {
// 	int		k;
// 	int		j;
// 	char	*tmp;

// 	k = 0;
// 	j = ft_strchr_pos(ms->cmd_line, '<');
// 	while ((ms->cmd_line[j] == '<' || ms->cmd_line[j] == ' ')
// 		&& ms->cmd_line[j] != '\0')
// 		j++;
// 	k = j;
// 	while (ms->cmd_line[k] != ' ' && ms->cmd_line[k] != '\0')
// 		k++;
// 	tmp = ft_substr(ms->cmd_line, j, k - j);
// 	ms->info->infile = tmp;
// 	// printf("infile: ..%s..\n", ms->info->infile);
// 	free(tmp);
// 	ft_cut_infile_redirections(ms);
// }

// /* Cuts out the redirections associated with the outfile from the cmd_line. */
// void	ft_cut_outfile_redirections(t_vars *ms)
// {
// 	char	*tmp;
// 	int		i;
// 	int		p;

// 	i = 0;
// 	p = 0;
// 	tmp = NULL;
// 	while (ms->cmd_line[i] != '>')
// 		tmp = ft_strnjoin(tmp, ms->cmd_line[i++], 1);
// 	if (ms->cmd_line[i] == '>')
// 		i++;
// 	while (ms->cmd_line[i] == ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	i++;
// 	while (ms->cmd_line[i] != ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	while (ms->cmd_line[i] == ' ' && ms->cmd_line[i] != '\0')
// 		i++;
// 	while (ms->cmd_line[i] != '\0')
// 		tmp = ft_strnjoin(tmp, ms->cmd_line[i++], 1);
// 	free(ms->cmd_line);
// 	ms->cmd_line = NULL;
// 	ms->cmd_line = tmp;
// }

// /* Saves the outfile in the t_info struct. */
// void outfile_redirection(t_vars *ms)
// {
// 	int	k;
// 	int	j;
// 	char *tmp;

// 	k = 0;
// 	j = ft_strchr_pos(ms->cmd_line, '>');
// 	while ((ms->cmd_line[j] == '>' || ms->cmd_line[j] == ' ') && ms->cmd_line[j] != '\0')
// 		j++;
// 	k = j;
// 	while (ms->cmd_line[k] != ' ' && ms->cmd_line[k] != '\0')
// 		k++;
// 	tmp = ft_substr(ms->cmd_line, j, k - j);
// 	ms->info->outfile = tmp;
// 	free(tmp);
// 	// printf("outfile: ..%s..\n", ms->info->outfile);
// 	ft_cut_outfile_redirections(ms);
// }

/* Searches for redirection symbols in the part of the *string and fills the relevant
content into the info struct. If there are multiple redirections in the part of the
input, they are being overwritten and only the last one is saved in the struct.*/
// void	check_redirections(t_vars *ms, int pipe_marker)
// {
// 	int		pos;

// 	pos = ft_strchr_pos(ms->cmd_line, '<');													//returns -1 if no redirection has been found or the position of the redirection
// 	while (pos != -1 && (pos <= ft_strchr_pos(ms->cmd_line, '|') || pipe_marker == -1))		// check if redirection is before the next pipe
// 	{
// 		if (ms->cmd_line[pos] == '<' && ms->cmd_line[pos + 1] == '<')						//check for '<<'
// 			printf("READ INPUT FROM THE CURRENT SOURCE\n");
// 		else																				//single '<'
// 			infile_redirection(ms);
// 		pos = ft_strchr_pos(ms->cmd_line, '<');												//check for multiple redirections
// 	}
// 	pos = ft_strchr_pos(ms->cmd_line, '>');
// 	while (pos != -1 && (pos <= ft_strchr_pos(ms->cmd_line, '|') || pipe_marker == -1))		// check if redirection is before the next pipe
// 	{
// 		if (ms->cmd_line[pos] == '>' && ms->cmd_line[pos + 1] == '>')
// 			printf("REDIRECTS OUTPUT WITH APPEND MODE\n");
// 		else
// 			outfile_redirection(ms);
// 		pos = ft_strchr_pos(ms->cmd_line, '>');
// 	}
// }