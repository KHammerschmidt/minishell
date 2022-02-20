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
void	ft_cut_infile_redirections(char **string)
{
	char	*tmp;
	int		i;
	// int		p;

	i = 0;
	// p = 0;
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
	ft_cut_infile_redirections(string);
}

/* Cuts out the redirections associated with the outfile from the cmd_line. */
void	ft_cut_outfile_redirections(char **string)
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
	free(*string);
	*string = NULL;
	*string = tmp;
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
	ft_cut_outfile_redirections(string);
}

static void	redirection_expansion_output(t_vars *ms, int redirection_out, char **string)
{
	if (redirection_out == 0)
		ms->info->output_op = 0;
	if (redirection_out != -1)
	{
		if ((*string)[redirection_out] == '>' && (*string)[redirection_out + 1] == '>')
		{
			ms->info->output_op = -2;
			outfile_redirection(string, ms);
		}
		else
		{
			ms->info->output_op = -1;
			outfile_redirection(string, ms);
		}
	}
}

static void	redirection_expansion_input(t_vars *ms, int redirection_in, char **string)
{
	if (redirection_in == -1)
			ms->info->input_op = 0;
		if (redirection_in != -1)
		{
			if ((*string)[redirection_in] == '<' && (*string)[redirection_in + 1] == '<')
			{
				ms->info->input_op = -2;
				infile_redirection(string, ms);
			}
			else
			{
				ms->info->input_op = -1;
				infile_redirection(string, ms);
			}
		}
}

/* Funktion compares the position of a redirection, first '<' then '>' and tests
if '<<' or '>>' are called. It then tests further if the pipe comes before
the redirection. */
void	check_redirections(char **string, int pipe_marker, t_vars *ms)
{
	int		redirection_in;
	int		redirection_out;

	redirection_in = ft_strchr_pos((*string), '<');
	redirection_expansion_input(ms, redirection_in, string);
	redirection_out = ft_strchr_pos(*string, '>');
	redirection_expansion_output(ms, redirection_out, string);
	if (ft_strchr_pos(*string, '<') != -1 && ft_strchr_pos(*string, '>') != -1)
	check_redirections((&*string), pipe_marker, ms);

	//add here info struct to open files!!!! and save here_doc and file descriptors in info struct
}

// //heredocs werden vor allem anderen ausgeführt, nicht nur pro command sondern in der ganzen input zeile
// //redirections for pipes
// //die letzte redirection zählt

// // '<<'
// //3.6.6 Here Documents
// // This type of redirection instructs the shell to read input from the current source until a line containing only word (with no trailing blanks) i
// // s seen. All of the lines read up to that point are then used as the standard input (or file descriptor n if n is specified) for a command.
// // The format of here-documents is:
// // [n]<<[-]word
// //         here-document
// // delimiter
// // No parameter and variable expansion, command substitution, arithmetic expansion, or filename expansion is performed on word. If any part of word is
// // quoted, the delimiter is the result of quote removal on word, and the lines in the here-document are not expanded. If word is unquoted, all lines
// // of the here-document are subjected to parameter expansion, command substitution, and arithmetic expansion, the character sequence \newline is ignored,
// // and ‘\’ must be used to quote the characters ‘\’, ‘$’, and ‘`’.
// // If the redirection operator is ‘<<-’, then all leading tab characters are stripped from input lines and the line containing delimiter. This allows
// // here-documents within shell scripts to be indented in a natural fashion.




// /* Cuts out the redirections associated with the outfile from the cmd_line. */
// void	cut_outfile_red(char **string)
// {
// 	char	*tmp;
// 	int		i;
// 	int		p;

// 	i = 0;
// 	p = 0;
// 	tmp = NULL;
// 	while ((*string)[i] != '>')
// 	{
// 		tmp = ft_strnjoin(tmp, (*string)[i], 1);
// 		i++;
// 	}
// 	while ((*string)[i] == '>')
// 		i++;
// 	while ((*string)[i] == ' ' && (*string)[i] != '\0')
// 		i++;
// 	i++;
// 	while ((*string)[i] != ' ' && (*string)[i] != '\0')
// 		i++;
// 	while ((*string)[i] == ' ' && (*string)[i] != '\0')
// 		i++;
// 	while ((*string)[i] != '\0')
// 		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
// 	free(*string);
// 	*string = NULL;
// 	*string = tmp;
// }

// /* Saves the outfile in the t_info struct. */
// void expansion_outfile_red(char **string, t_vars *ms)
// {
// 	int		k;
// 	int		j;
// 	char	*tmp;

// 	k = 0;
// 	j = ft_strchr_pos((*string), '>');
// 	while (((*string)[j] == '>' || (*string)[j] == ' ') && (*string)[j] != '\0')
// 		j++;
// 	k = j;
// 	while ((*string)[k] != ' ' && (*string)[k] != '\0')
// 		k++;
// 	tmp = ft_substr((*string), j, k - j);
// 	ms->info->outfile = tmp;
// }

// void	outfile_fd(t_vars *ms)
// {
// 	if (ms->info->output_op == -1)
// 	{
// 		if (ms->info->fd_out != STDOUT_FILENO)
// 			close(ms->info->fd_out);
// 		ms->info->fd_out = open(ms->info->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	}
// 	if (ms->info->output_op == -2)
// 	{
// 		if (ms->info->fd_out != STDOUT_FILENO)
// 			close(ms->info->fd_out);
// 		ms->info->fd_out = open(ms->info->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
// 	}
// 	if (ms->info->fd_out == -1 || access(ms->info->outfile, W_OK) != 0)
// 		perror("Error");
// }

// static void	output_redirection(t_vars *ms, char **string, int red_out)
// {
// 	while (red_out != -1)
// 	{
// 		if ((*string)[red_out] == '>')
// 		{
// 			if ((*string)[red_out + 1] == '>')
// 				ms->info->output_op = -2;
// 			else
// 				ms->info->output_op = -1;
// 		}
// 		expansion_outfile_red(string, ms);
// 		cut_outfile_red(string);
// 		outfile_fd(ms);
// 		red_out = ft_strchr_pos(*string, '>');
// 	}
// }

// /* Funktion compares the position of a redirection, first '<' then '>' and tests
// if '<<' or '>>' are called. It then tests further if the pipe comes before
// the redirection. */
// void	check_redirections(char **string, t_vars *ms)
// {
// 	int		red_in;
// 	int		red_out;

// 	red_in = 0;
// 	red_out = 0;
// 	red_in = ft_strchr_pos(*string, '<');
// 	ms->info->fd_in = STDIN_FILENO;
// 	if (red_in != -1)
// 		input_redirection(ms, string, red_in);
// 	else
// 		ms->info->input_op = 0;
// 	red_out = ft_strchr_pos(*string, '>');
// 	ms->info->fd_out = STDOUT_FILENO;
// 	if (red_out != -1)
// 		output_redirection(ms, string, red_out);
// 	else
// 		ms->info->output_op = 0;

// }


/* Cuts out the redirections associated with the infile from the cmd_line. */
// void	ft_cut_infile_redirections(char **string)
// {
// 	char	*tmp;
// 	int		i;
// 	int		p;

// 	i = 0;
// 	p = 0;
// 	tmp = NULL;
// 	while ((*string)[i] != '<')
// 	{
// 		tmp = ft_strnjoin(tmp, (*string)[i], 1);
// 		i++;
// 	}
// 	while ((*string)[i] == '<')
// 		i++;
// 	while ((*string)[i] == ' ' && (*string)[i] != '\0')
// 		i++;
// 	i++;
// 	while ((*string)[i] != ' ' && (*string)[i] != '\0')
// 		i++;
// 	while ((*string)[i] == ' ' && (*string)[i] != '\0')
// 		i++;
// 	while ((*string)[i] != '\0')
// 		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
// 	free(*string);
// 	*string = NULL;
// 	*string = tmp;
// }

/* Saves the infile in the t_info struct or the respective
limiter for a here_doc. */
// void	infile_redirection(char **string, t_vars *ms, int i)
// {
// 	int		k;
// 	int		j;
// 	char	*tmp;

// 	k = 0;
// 	j = ft_strchr_pos(*string, '<');
// 	while (((*string)[j] == '<' || (*string)[j] == ' ') && (*string)[j] != '\0')
// 		j++;
// 	k = j;
// 	while ((*string)[k] != ' ' && (*string)[k] != '\0')
// 		k++;
// 	tmp = ft_substr(*string, j, k - j);
// 	if ((*string[j] == '<') && (*string[j + 1]) == '<')
// 		ms->info->here_doc[i]->limiter = tmp;
// 	else
// 		ms->info->infile[i] = tmp;
// 	ft_cut_infile_redirections(string);
// }


// static void	redirection_expansion_input(t_vars *ms, int redirection_in, char **string, int i)
// {
// 	if (redirection_in == -1)
// 			ms->info->input_op[i] = 0;
// 		if (redirection_in != -1)
// 		{
// 			if ((*string)[redirection_in] == '<' && (*string)[redirection_in + 1] == '<')
// 			{
// 				// HERE_DOC
// 				ms->info->input_op[i] = -2;

// 				infile_redirection(string, ms);
// 			}
// 			else
// 			{
// 				ms->info->input_op[i] = -1;
// 				infile_redirection(string, ms);
// 			}
// 		}
// }

/* int	ft_count_here_doc();
Counts the number of here_docs for allocation memory for the struct t_here_doc;
Writtin in branch at 42. */

// void	input_redirection(t_vars *ms, char **string, int red_in)
// {
// 	int			cntr_hdoc;
// 	int			cntr_smpl_red;
// 	t_here_doc	*here_doc;
// 	int			i;

// 	i = 0;
// 	cntr_smpl_red = 0;
// 	cntr_hdoc = 0;
// 	//ft_count_here_doc(cntr_smpl_red, cntr_smpl_red);
// 	cntr_hdoc = 1;
// 	if (cntr_hdoc != 0)
// 	{
// 		// mem allocation for the amount of here_docs we need
// 		here_doc = (t_here_doc *)ft_calloc(sizeof(t_here_doc), cntr_hdoc);
// 		if (!here_doc)
// 		{
// 			printf("Mem allocation error here_doc\n");
// 			return ;
// 		}
// 	}
// 	else
// 		here_doc = NULL;
// 	ms->info->input_op = (int **)ft_calloc(sizeof(int *), cntr_smpl_red + 1);
// 	if (!(ms->info->input_op))
// 		printf("Mem allocation error int **\n");
// 	// while there are still '<'found in the string
// 	while (ft_strchr_pos(*string, '>') != -1)
// 	{
// 		redirection_expansion_input(ms, red_in, string, i);
// 		i++;
// 	}
// }