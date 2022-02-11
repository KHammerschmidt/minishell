#include "../header/minishell.h"

//heredocs werden vor allem anderen ausgeführt, nicht nur pro command sondern in der ganzen input zeile
//redirections for pipes
//die letzte redirection zählt

// '>>'
// Appending Redirected Output
// Redirection of output in this fashion causes the file whose name results from the expansion of word to be opened for appending on file descriptor n,
// or the standard output (file descriptor 1) if n is not specified. If the file does not exist it is created.
// The general format for appending output is:
// [n]>>word


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
		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
	free(*string);
	*string = NULL;
	*string = tmp;
	if (!ms)
		printf("\n");
}

/* Saves the infile in the t_info struct. */
void	infile_redirection(char **string, t_vars *ms)
{
	int		k;
	int		j;
	char	*tmp;

	k = 0;
	j = ft_strchr_pos(*string, '<');
	while (((*string)[j] == '<' || (*string)[j] == ' ') && (*string)[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '\0')
		k++;
	tmp = ft_substr(*string, j, k - j);
	ms->info->infile = tmp;
	ft_cut_infile_redirections(string, ms);
}

/* Cuts out the redirections associated with the outfile from the cmd_line. */
void	ft_cut_outfile_redirections(char **string, t_vars *ms)				//he isn't allowed to jump in here!
{
	char	*tmp;
	int		i;
	int		p;

	i = 0;
	p = 0;
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
	free(*string);
	*string = NULL;
	*string = tmp;
	if (!ms)
		printf("\n");
}

/* Saves the outfile in the t_info struct. */
void outfile_redirection(char **string, t_vars *ms)
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
	ms->info->outfile = tmp;
	ft_cut_outfile_redirections(string, ms);
}

/* Funktion compares the position of a redirection, first '<' then '>' and tests
if '<<' or '>>' are called. It then tests further if the pipe comes before				//necessary?
the redirection. */
void	check_redirections(char **string, int pipe_marker, t_vars *ms)
{
	int		redirection_in;
	int		redirection_out;

	redirection_in = ft_strchr_pos((*string), '<');
	if (redirection_in != -1)
	{
		if ((*string)[redirection_in] == '<' && (*string)[redirection_in + 1] == '<')		//check for '<<'
			printf("READ INPUT FROM THE CURRENT SOURCE\n");
		else																			//single '<'
			infile_redirection(string, ms);
	}
	redirection_out = ft_strchr_pos(*string, '>');
	if (redirection_out != -1)
	{
		if ((*string)[redirection_out] == '>' && (*string)[redirection_out + 1] == '>')
			printf("REDIRECTS OUTPUT WITH APPEND MODE\n");
		else
			outfile_redirection(string, ms);
	}
	if (ft_strchr_pos(*string, '<') != -1 && ft_strchr_pos(*string, '>') != -1)			// in case there are multiple redirections in there (how are they overwriting each other, but calling the here_doc for example?)
		check_redirections((&*string), pipe_marker, ms);
}