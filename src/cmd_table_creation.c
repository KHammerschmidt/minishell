#include "../header/minishell.h"

char	*handle_input(t_vars *ms)
{
	int		pipe_marker;
	char	*new_cmd_line;
	char	*command_line;
	int		quotes;

	new_cmd_line = NULL;
	command_line = NULL;
	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');//finds position of pipe, is -1 if no pipe exists
	quotes = check_quote_validity(ms->cmd_line, ms);//checks for: open quotes, active outside quotes, double quotes and $ sign
	if (pipe_marker == -1 && quotes == 0)									//no pipe & no quotes
	{
		//redirections //dollar sign etc.
		ms->info->command = ft_split(ms->cmd_line, ' ');
		return (NULL);
	}
	if (pipe_marker != -1 && check_pipe_validity(ms->cmd_line) == 0)		//valid pipe (not within quotes) split by pipe first
	{
		//redirections //dollar sign etc.
		ms->info->pipe = 1;
		command_line = ft_substr(ms->cmd_line, 0, pipe_marker);
		while (ms->cmd_line[pipe_marker] == ' ' || ms->cmd_line[pipe_marker] == '|')
			pipe_marker++;
		new_cmd_line = ft_strdup(&ms->cmd_line[pipe_marker]);
		if (quotes == 0)					//no quotes, split by '
			ms->info->command = ft_split(command_line, ' ');					// split by quotes () //ms->info->command = ft_split_pipe(command_line);
		else if (quotes == -1)				//open quotes (ERROR)
		{
			printf("ERROR: Open quotes\n");
			free(new_cmd_line);
			new_cmd_line = NULL;
			free(command_line);// return (NULL);
		}
		else								// valid quotes (any kind saved in info)
			ms->info->command = ft_split_quotes(command_line, ms);		//quotes
	}
	else
	{
		if (quotes == 0)			//no quotes, split by '
			ms->info->command = ft_split(ms->cmd_line, ' ');					// split by quotes () //ms->info->command = ft_split_pipe(command_line);
		else if (quotes == -1)				//open quotes (ERROR)
		{
			printf("ERROR: Open quotes\n");
			free(new_cmd_line);
			new_cmd_line = NULL;
		}
		else								// valid quotes (any kind saved in info)
		{
			printf("%s\n", ms->cmd_line);
			ms->info->command = ft_split_quotes(ms->cmd_line, ms);		//quotes
			print_arr(ms->info->command);
		}
	}
	// pass_on_infos(ms);
	printf("new_cmd >>> %s\n", new_cmd_line);
	return (new_cmd_line);
}


/* Creates the simple command table for the execution part. */
int	create_cmd_table(t_vars *ms)
{
	int		i;
	// int		j;
	char	*tmp;
	char	**split;
	t_cmd	*new;

	i = 0;
	// j = 0;
	split = NULL;
	tmp = (char *)malloc(sizeof(ms->cmd_line) + 1);
	if (!tmp)
		printf("MEM ALLOC ERROR!\n");			//exit function einbauen
	while (1)									// as long as there is no command to handle anymore
	{
		tmp = handle_input(ms);					//handle pipes, quotes, dollar signs, split string and put info into struct
		new = ft_lstnew_cmd(ms->info);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (tmp == NULL)
			break ;
		free(ms->cmd_line);						//free here?
		ms->cmd_line = ft_strdup(tmp);
		printf("ms->cmd_line>> %s\n", ms->cmd_line);
		free(tmp);
	}
	return (0);
}


