#include "../header/minishell.h"

/* Compares the position of the pipe to any redirections and indicates
what should be done next in the splitting process. */
int	pos_pipe_redirection(char **string, int pipe_marker)
{
	int	pos_infile;
	int	pos_outfile;

	pos_infile = ft_strchr_pos(*string, '<');
	pos_outfile = ft_strchr_pos(*string, '>');
	if (pos_infile == -1 && pos_outfile == -1)							//there is no redirection
		return (0);
	if ((pos_infile == -1 && pipe_marker < pos_outfile)
		|| (pos_outfile == -1 && pipe_marker < pos_infile))
		return (1);														//pipe comes before any redirection
	else if (pipe_marker < pos_infile && pipe_marker < pos_outfile)
		return (1);														//pipe comes before any redirection
	else if (pipe_marker < pos_infile)									//pipe comes before outfile redirection
		return (2);
	else if (pipe_marker < pos_outfile)									//pipe comes before infile redirection
		return (3);
	return (0);
}

/* Splits the input cmd_line in according to the quotes. */
char *handle_quotes_pipe(int quotes, t_vars *ms, char *command_line, char *new_cmd_line)				//quotes not working
{
	int	pipe_marker;

	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	check_redirections(&ms->cmd_line, pipe_marker, ms);
	if (quotes == 0)										//no quotes, split by '
		ms->info->command = ft_split(command_line, ' ');
	else if (quotes == -1)									//open quotes (ERROR)
	{
		ft_free_string(new_cmd_line);
		ft_free_string(command_line);						// free(new_cmd_line); 	// new_cmd_line = NULL; // free(command_line); // command_line = NULL;
		return (NULL);
	}
	else													//any types of quotes
		ms->info->command = ft_split_quotes(command_line);
	return (new_cmd_line);
}


/* Splits the input cmd_line in according to the quotes. */
char *handle_quotes(int quotes, t_vars *ms, char *command_line, char *new_cmd_line)				//quotes not working
{
	check_redirections(&ms->cmd_line, -1, ms);
	if (quotes == -1)										//open quotes (ERROR)
	{
		ft_free_string(new_cmd_line);
		ft_free_string(command_line);						// free(new_cmd_line); 	// new_cmd_line = NULL; // free(command_line); // command_line = NULL;
	}
	else													//any types of quotes
		ms->info->command = ft_split_quotes(ms->cmd_line);
	return (NULL);
}

char	*substring_pipe(t_vars *ms, char **command_line, int pipe_marker)
{
	char	*new_cmd_line;

	new_cmd_line = NULL;
	ms->info->pipe = 1;
	*command_line = ft_substr(ms->cmd_line, 0, pipe_marker);
	while (ms->cmd_line[pipe_marker] == ' ' || ms->cmd_line[pipe_marker] == '|')
		pipe_marker++;
	new_cmd_line = ft_substr(ms->cmd_line, pipe_marker, ft_strlen(ms->cmd_line) - pipe_marker);
	// new_cmd_line = ft_strdup(&ms->cmd_line[pipe_marker]);
	return (new_cmd_line);
}

/* Handles the input cmd_line which include a pipe and compares
in accordance to the priorities (redirection, pipes and quotes). */
char	*handle_pipe(t_vars *ms, int quotes, char *new_cmd_line, char *command_line)
{
	int	pipe_marker;
	int	pipe_redirections_index;

	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	pipe_redirections_index = pos_pipe_redirection(&ms->cmd_line, pipe_marker);			//tests if pipe comes before redirection
	if (pipe_redirections_index != 1)													//redirections comes before any redirection
	{
		check_redirections(&ms->cmd_line, pipe_marker, ms);
		new_cmd_line = substring_pipe(ms, &command_line, pipe_marker);
	}
	else																				//pipe come before pipes //ERROR!!!
	{
		new_cmd_line = substring_pipe(ms, &command_line, pipe_marker);
		check_redirections(&command_line, pipe_marker, ms);
	}
	ms->info->command = ft_split(command_line, ' ');
	if (ms->info->double_quote_counter != 0 || ms->info->single_quote_counter != 0)
		return (handle_quotes_pipe(quotes, ms, command_line, new_cmd_line));
	return (new_cmd_line);
}

/* Handles pipes, dollar signs, quotes and splits the string accordingly while
saving relevant variables in struct t_info of the first command. The function
returns any following commands of cmd_line or NULL if tehre was only one
command. */
char	*handle_input(t_vars *ms)
{
	int		pipe_marker;
	int		quotes;
	char	*command_line;
	char	*new_cmd_line;

	command_line = NULL;
	new_cmd_line = NULL;
	//expand dollar sign (here) when they are in double quotes or without quotes
	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');							//finds position of pipe, is -1 if no pipe exists
	quotes = check_quote_validity(ms->cmd_line, ms);						//checks for: no quotes (== 0), open quotes (== -1), active outside quotes and $ sign
	if (pipe_marker == -1 && quotes == 0)									//no pipe & no quotes
	{
		check_redirections(&ms->cmd_line, pipe_marker, ms);					//cuts out the redirections and saves them in t_info
		ms->info->command = ft_split(ms->cmd_line, ' ');
		return (NULL);
	}
	else if (pipe_marker != -1 && check_pipe_validity(ms->cmd_line) == 0)	//valid pipe (not within quotes) split by pipe first
		return (handle_pipe(ms, quotes, new_cmd_line, command_line));
	else
		return (handle_quotes(quotes, ms, command_line, new_cmd_line));		//only quotes, no pipes
}

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
int	create_cmd_table(t_vars *ms)
{
	int		i;
	char	*tmp;
	char	**split;
	t_cmd	*new;

	i = 0;
	split = NULL;
	tmp = (char *)malloc(sizeof(ms->cmd_line) + 1);
	if (!tmp)
		printf("MEM ALLOC ERROR!\n");//exit function einbauen
	while (ms->cmd_line != NULL)
	{
		tmp = handle_input(ms);									//returns new cmd_line, puts the current command in the struct t_info
		new = ft_lstnew_cmd(ms->info);							//creates a new element with all the content from struct t_info
		ft_lstadd_back_cmd(&ms->cmd, new);						//adds the new element to the end of the list
		if (tmp == NULL)
			break ;
		free(ms->cmd_line);
		ms->cmd_line = NULL;
		ms->cmd_line = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}
