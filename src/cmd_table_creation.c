#include "../header/minishell.h"

char	*handle_input(t_vars *ms)
{
	int		pipe_marker;
	char	*new_cmd_line;
	char	*command_line;
	int		quotes;

	new_cmd_line = NULL;
	command_line = NULL;
	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');							//finds position of pipe, is -1 if no pipe exists
	quotes = check_quote_validity(ms->cmd_line, ms);						//checks for: open quotes, active outside quotes, double quotes and $ sign
	//expand dollar sign (here)
	if (pipe_marker == -1 && quotes == 0)									//no pipe & no quotes
	{
		// check_redirections(&ms->cmd_line, pipe_marker, ms);
		ms->info->command = ft_split(ms->cmd_line, ' ');
		return (NULL);
	}
	if (pipe_marker != -1 && check_pipe_validity(ms->cmd_line) == 0)		//valid pipe (not within quotes) split by pipe first
	{
		ms->info->pipe = 1;
		command_line = ft_substr(ms->cmd_line, 0, pipe_marker);
		while (ms->cmd_line[pipe_marker] == ' ' || ms->cmd_line[pipe_marker] == '|')
			pipe_marker++;
		new_cmd_line = ft_strdup(&ms->cmd_line[pipe_marker]);
		// check_redirections(&new_cmd_line, pipe_marker, ms);					// redirections
		if (quotes == 0)			//no quotes, split by '
			ms->info->command = ft_split(command_line, ' ');				// split by quotes () //ms->info->command = ft_split_pipe(command_line);
		else if (quotes == -1)		//open quotes (ERROR)
		{
			free(new_cmd_line);
			new_cmd_line = NULL;
			free(command_line);
			command_line = NULL;
		}
		else						// valid quotes (any kind saved in info)
 			ms->info->command = ft_split_quotes(command_line);				// ms->info->command = ft_split_quotes(command_line, ms);		//quotes
	}
	else
	{
		//dollar sign etc.
		// check_redirections(&ms->cmd_line, pipe_marker, ms);						//redirections
		if (quotes == 0)			//no quotes, split by '
			ms->info->command = ft_split(ms->cmd_line, ' ');				// split by quotes () //ms->info->command = ft_split_pipe(command_line);
		else if (quotes == -1)		//open quotes (ERROR)
		{
			free(new_cmd_line);
			new_cmd_line = NULL;
		}
		else						// valid quotes (any kind saved in info)
			ms->info->command = ft_split_quotes(ms->cmd_line);
	} 	// pass_on_infos(ms);
	return (new_cmd_line);
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
		printf("MEM ALLOC ERROR!\n");			//exit function einbauen
	while (ms->cmd_line != NULL)				// while (1) //as long as there is no command to handle anymore
	{
		tmp = handle_input(ms);					//handle pipes, quotes, dollar signs, split string and put info into struct
		new = ft_lstnew_cmd(ms->info);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (tmp == NULL)
			break ;
		free(ms->cmd_line);
		ms->cmd_line = NULL;
		ms->cmd_line = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}


