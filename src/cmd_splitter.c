#include "../header/minishell.h"

char	*copy_str_without_quotes(char *str)				//INFO: $sign has to work
{
	char	*tmp;
	char	*argument;

	tmp = "\"\\";
	argument = ft_strtrim(str, tmp);					//if no command -> access wirft command not found aus!
	return (argument);
}

void	ft_free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != '\0' && arr)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

int	check_pipe_validity(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[i] != '|')
	{
		if (str[i] == 34)			//double quote
			double_quote++;
		if (str[i] == 39)			//single quote
			single_quote++;
		i++;
	}
	if ((double_quote % 2) != 0 || (single_quote % 2) != 0)
		return (1);					//pipe is no valid pipe, it is in between quotes
	return (0);						//valid pipe
}

int	quote_infos(t_vars *ms, char *str)
{
	if (ms->info->single_quote_counter == 0 && ms->info->double_quote_counter != 0)			//only double quotes in string
	{
		ms->info->double_quote_counter = 1;
		printf("ONLY DOUBLE QUOTES\n");
		return (1);
	}
	else if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter != 0)	//only single quotes in string
	{
		ms->info->single_quote_counter = 1;
		printf("ONLY SINGLE QUOTES\n");
		return (1);
	}
	if (ft_strchr_pos(str, 34) < ft_strchr_pos(str, 39))	//pos double quotes < pos single quotes, double quotes are surrounding
	{
		ms->info->double_quote_counter = 1;					// double quotes are activated (can be trimmed afterwards)
		ms->info->single_quote_counter = 0;					//single quotes are deactivated
		printf("double quotes are outer quotes!\n");
	}
	else if (ft_strchr_pos(str, 34) > ft_strchr_pos(str, 39))	//pos single quotes < pos double quotes, single quotes are surrounding
	{
		ms->info->single_quote_counter = 1;					//single quotes activated (can be trimmed afterwards)
		ms->info->double_quote_counter = 0;					//double quotes deactivated
		printf("single quotes are outer quotes!\n");
	}
	printf("HERE 2\n");
	return (1);
}

int	check_quote_validity(char *str, t_vars *ms)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)						//double_quotes
			ms->info->double_quote_counter++;
		if (str[i] == 39)						//single quotes
			ms->info->single_quote_counter++;
		if (ms->info->double_quote_counter != 0 && str[i] == '$')			//valid quotes and $ sign in there
			ms->info->dollar++;
		i++;
	}
	printf("double:[%d]   single[%d]\n", ms->info->double_quote_counter, ms->info->single_quote_counter);
	if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter == 0)						//no quotes
	{
		printf("no quotes!\n");
		return (0);
	}
	if ((ms->info->double_quote_counter % 2) != 0 || (ms->info->single_quote_counter % 2) != 0)			//open quotes
	{
		printf("open quotes!\n");
		return (-1);
	}
	return (quote_infos(ms, str));
}

void	reset_info_struct(t_info *info)
{
	info->command = NULL;
	info->outfile = NULL;
	info->infile = NULL;
	info->errfile = NULL;
	info->op = 0;
	info->pipe = 0;
	info->single_quote_counter = 0;
	info->double_quote_counter = 0;
	info->open_quotes = 0;
	info->dollar = 0;
}

// void	pass_on_infos(t_vars *ms)
// {
// 	// ms->cmd->command = ms->info->command;
// 	printf("%d \n", ms->info->pipe);
// 	printf("%d \n", ms->cmd->pipe);
// 	ms->cmd->pipe = ms->info->pipe;
// 	// ms->cmd->op = ms->info->op;
// 	// ms->cmd->infile = ms->info->infile;
// 	// ms->cmd->outfile = ms->info->outfile;
// 	// ms->cmd->errfile = ms->info->errfile;
// 	printf("HERE\n");
// 	reset_info_struct(ms->info);
// }

char	**ft_split_quotes(char *str, t_vars *ms)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**split;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	// if (ms->info->dollar != 0)
	// 		check_dollar_sign(str, ms);					//is there a dollar sign outside the quotes
	split = ft_calloc(1, sizeof(*(split)));
	if (!split)
		printf("MEM ALLOC ERROR\n");
	temp = NULL;
	if (ms->info->double_quote_counter == 1)
		quote = 34;									//double quotes are the outer quotes or are the only quotes
	else if (ms->info->single_quote_counter == 1)
		quote = 39;									//single quotes are the dominant one

	while (str[i] != '\0')
	{
		while (str[i] != quote)						//while no quote has been found we split by spaces
		{
			if (str[i] == ' ')						//iterate until space is found (create substring & save in char **)
			{
				temp = ft_substr(str, j, i);
				split[k] = temp;
				printf("split[%d]: ..%s..\n", k, split[k]);
				free(temp);
				j = j + i + 1;
				i--;
			}
			i++;
		}
		if (str[i] == quote)					//quote has been found, we leave the quotes part in one string
		{
			temp = ft_substr(str, j, i);
			split[k] = temp;
			printf("split[%d]: ..%s..\n", k, split[k]);
			k++;
			free(temp);
			j = j + i + 1;
		}
	i++;
	}
	return (split);
}

int	check_pipes_in_quote(t_vars *ms)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ms->cmd_line[i] != '|')
	{
		if (ms->cmd_line[i] == 34 || ms->cmd_line[i] == 39)
			flag++;
		i++;
	}
	return (i);
}


void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != '\0')
	{
		printf("||||||..%s\n", arr[i]);
		i++;
	}
}

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

	// }
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

	// if (i == -1)										//no pipes
	// {
	// 	handle_input(ms, ms->cmd_line, i);
	// 	new = ft_lstnew_cmd(ft_split(ms->cmd_line, ' '));
	// 	ft_lstadd_back_cmd(&ms->cmd, new);
	// }
	// else
	// {
	// 	while (i != -1)									//pipes
	// 	{
	// 		handle_input(ms, tmp, i);
	// 		// i = ft_strchr_pos(&ms->cmd_line[j], '|');
	// 		// tmp = ft_substr(ms->cmd_line, j, i);
	// 		// split = ft_split(tmp, ' ');
	// 		new = ft_lstnew_cmd(split);
	// 		ft_lstadd_back_cmd(&ms->cmd, new);
	// 		free(tmp);
	// 		j = (j + i + 1);
	// 	}
	// }






// char	**split_string(char *str, t_vars *ms, int pipe_marker)
// {
// 	char		*split;
// 	char		*tmp;
// 	int			i;
// 	int			j;
// 	char		**command;

// 	i = 0;
// 	j = 0;
// 	if (ms->info->pipe == 0)															//keine pipe
// 	{
// 		if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter == 0)	//keine quotes
// 			command = ft_split(str, ' ');												//split by spaces (check $ sign)
// 		else
// 			command = ft_split_quotes(str, ms);
// 	}
// 	// else
// 	// {

// 	// }


// 	// i = ft_strchr_pos(&ms->cmd_line[j], '|');
// 	// tmp = ft_substr(ms->cmd_line, j, i);
// 	// split = ft_split(tmp, ' ');
// 	// j = (j + i + 1);

// 	return (command);
// }

	// if (pipe_marker != -1 && check_pipe_validity(str) == 0)		//there is a pipe and it is valid
	// 	ms->info->pipe = 1;

// ______________________________________________________________________________________________________________________________________________________



// /* Splits the input line by it's pipes and fills the simple command table command by command. */
// void	handle_input(t_vars *ms, int pipe_marker)
// {
// 	t_info		*info;
// 	char		*split;
// 	char		*tmp;
// 	int			i = 0;
// 	int			j = 0;

// 	init_init(&info);
// 	split = ft_split(ms->cmd_line, ' ');
// 	tmp = ft_substr(ms->cmd_line, j, i);
// 	if (pipe_marker == -1)
// 	{
// 		info->pipe = 0;			//no pipe

// 	}
// 	else
// 	{
// 		if (check_pipe_quotes() != 0)
// 			info->pipe = 0;					//no pipe as pipe is within quotes
// 		else
// 			info->pipe = 1;					//valid pipe
// 	}

// 																	//check for quotes
// 								//split by spaces ( cut out pipes)
// 																	//check for redirections
// 																	//pipe_marker

// }


// void	fill_operators(char *str, t_cmd *element)
// {
// 	int	op;
// 	int	i;

// 	i =0 ;
// 	op = 0;
// 	while (str[i] != '\0')					//what happens when there are more redirections?
// 	{
// 		if (ft_strnstr(str, "<", ft_strlen(str)) != 0)
// 			element->op = LESS;
// 		if (ft_strnstr(str, "<<", ft_strlen(str)) != 0)
// 			element->op = LESSLESS;
// 		if (ft_strnstr(str, ">", ft_strlen(str)) != 0)
// 			element->op = GREATER;
// 		if (ft_strnstr(str, ">>", ft_strlen(str)) != 0)
// 			element->op = GREATERGREATER;
// 		i++;
// 	}
// }

// void	fill_table_2(t_cmd *element, int pipe_marker)
// {
// 	if (pipe_marker == -1)
// 		element->pipe = 0;
// 	else
// 		element->pipe = 1;
// 	// fill_operators(str, element);
// 	// free(command);
// 	// free(args);
// 	// free(str);
// }



	// tmp = ft_substr(ms->cmd_line, 0, i);
	// // fill_table(ms, tmp, i);
	// // ft_free_string(tmp);
	// while (ms->cmd_line[i] == ' ' || ms->cmd_line[i] == '|')
	// 	i++;
	// tmp = ft_strdup(&ms->cmd_line[i]);
	// ft_free_string(ms->cmd_line);
	// ms->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
	// ft_free_string(tmp);
	// i = 0;
	// print_lst(ms);




// int	count_pipes(char *line)
// {
// 	int	i;
// 	int	counter;

// 	i = 0;
// 	counter = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == 124)
// 			counter++;
// 		i++;
// 	}
// 	// if (counter != 0)
// 	// 	counter++;
// 	return (counter);
// }


// int	create_cmd_table(t_cmd *cmd, char *line)
// {
// 	int		i;
// 	char	*tmp;
// 	int		pipe_marker;

// 	i = 0;
// 	pipe_marker = 0;
// 	while (1)
// 	{
// 		pipe_marker = ft_strchr_pos(line, '|');				//find position of pipe
// 		if (pipe_marker == -1)								// no pipe was found
// 		{
// 			if (line != NULL)
// 				fill_table(cmd, line, pipe_marker);
// 			ft_free_string(line);
// 			break ;
// 		}

// 		tmp = ft_substr(line, 0, pipe_marker);				//create substring from start of line until pipe
// 		fill_table(cmd, tmp, pipe_marker);					//put content in list
// 		ft_free_string(tmp);
// 		i = pipe_marker;
// 		while (line[pipe_marker] == ' ' || line[i] == '|')
// 			i++;
// 		tmp = ft_strdup(&line[i]);
// 		ft_free_string(line);
// 		line = ft_substr(tmp, 0, ft_strlen(tmp));
// 		ft_free_string(tmp);
// 		pipe_marker = 0;
// 	}
// 	return (0);
// }





// void	fill_table(t_vars *ms, char *str, int pipe_marker)
// {
// 	t_cmd	*element;
// 	t_cmd	*temp;
// 	char **arr;
// 	int	i;

// 	i = 0;
// 	element = NULL;
// 	temp = NULL;
// 	arr = ft_split(str, ' ');
// 	if (!arr)
// 		return ;						//FEHLER MSG EINBAUEN
// 	while (arr[i] != NULL)
// 		i++;
// 	element = ft_lstnew_cmd(i, arr);
// 	ft_lstft_lstadd_back_cmd_cmd(&(ms->cmd), element);


// 	element = init_cmd_lst(ms, i);									// 3) allocate memory for struct arr
// 	temp = ms->cmd;
// 	while (temp)
// 	{
// 		printf("%s   \n", temp->command[0]);
// 		temp = temp->next;
// 	}
// 		last = lst;
// 	if (last == NULL)
// 		return (NULL);
// 	while (last->next != NULL)
// 		last = last->next;
// 	return (last);

// 	ft_lstft_lstadd_back_cmd_cmd(&ms->cmd, element);
// 	free(arr);
// 	printf("dfhjkdfhk\n");
// 	while (arr[i])														// 4) copy splitted string into struct
// 	{
// 		printf("HJAAJ\n");
// 		element->command = arr;
// 		// element->command[i] = arr[i];
// 		printf("HIHIHI\n");
// 		i++;
// 	}
// 	element->command[i] = NULL;
// 	element =

// 	ms->cmd = element;
// 	i = 0;
// 	while (element->command[i])
// 	{
// 		printf("%s 		", element->command[i]);
// 		i++;
// 	}
// 	printf("\n");

// 	if (!pipe_marker)
// 		printf("\n");
// }


// void	print_lst(t_vars *ms)
// {
// 	t_cmd *tmp;
// 	int		i;

// 	i = 0;
// 	tmp = ms->cmd;
// 	printf("\nSimple Command Table\n");
// 	if (tmp == NULL)
// 		printf("tmp is empty!!!!\n");
// 	while (tmp != NULL)
// 	{
// 		printf("command: %s		", tmp->command[i]);
// 		while (tmp->command[i] != NULL && tmp != NULL)
// 		{
// 			i++;
// 			if (tmp->command[i])
// 				printf("args: %s		", tmp->command[i++]);
// 		}
// 		printf("\n");
// 		tmp = tmp->next;
// 		i = 0;
// 	}
// }





// t_cmd	*init_cmd_element(t_cmd *cmd)
// {
// 	t_cmd	*element;

// 	element = ft_lstnew_cmd();
// 	ft_lstft_lstadd_back_cmd_cmd(&cmd, element);

// 	return (element);
// }

// void	print_list_1(t_cmd *head)
// {
// 	t_cmd	*current;

// 	current = head;
// 	printf("HERE 6\n");
// 	while (current != NULL)
// 	{
// 		printf("HUHUHHU: %s\n", current->command);
// 		current = current->next;
// 	}
// 	// printf("HUHUHHU: %p, ", current->command);
// }



// void	fill_table(t_vars *ms, char *str, int pipe_marker)
// {
// 	t_cmd	*element;
// 	int		pos;
// 	char	**command;
// 	char	**args;
// 	int		quotes;

// 	args = NULL;
// 	command = NULL;
// 	element = NULL;
// 	pos = ft_strchr_pos(str, ' ');
// 	quotes = cmd_validity(str);
// 	element = init_cmd_lst(ms);
// 	if (quotes == 0)								// no quotes
// 	{
// 		if (pos != -1)								//pos != -1 --> spaces have been found, e.g. comamnd consists of cmd & args
// 		{
// 			command = ft_substr(str, 0, pos);
// 			args = ft_substr(str, pos, ft_strlen(str) - pos);
// 			element->args = ft_strdup(args);
// 		}
// 		else										//pos == -1 ---> no space has been found, e.g. command only consists of one word
// 			command = ft_substr(str, 0, ft_strlen(str));
// 		element->command = ft_strdup(command);
// 	}
// 	else if (quotes == 1)							//quotes and other text, split cmd und args
// 	{
// 		command = ft_substr(str, 0, pos);
// 		element->command = ft_strdup(command);
// 		args = ft_substr(str, pos, ft_strlen(str) - pos);
// 		element->args = copy_str_without_quotes(args);
// 	}
// 	else if (quotes == 2)							// only quotes (one long string, e.g. no command()
// 		element->command = copy_str_without_quotes(str);
// 	// else if	(quotes == 3)							//open quotes: es gibt normale Fehlermeldungen die dann aufkommen (erstmal auslassen)
// 	fill_table_2(element, pipe_marker);
// }






// void	fill_table(t_vars *ms, char *str, int pipe_marker)				//ursprüngliche Version
// {
// 	t_cmd	*element;
// 	char	**args;
// 	char	*command;
// 	int		pos;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	args = NULL;
// 	command = NULL;
// 	element = NULL;
// 	pos = ft_strchr_pos(str, 32);
// 	element = init_cmd_lst(ms);
// 	// element->command = ft_calloc(sizeof(char **), 1);
// 	if (pos == -1)
// 		element->command[i] = ft_strdup(str);
// 	else
// 	{
// 		command = ft_substr(str, 0, pos);
// 		element->command[i] = ft_strdup(command);
// 		args = ft_split(&str[pos], 32);
// 		while (args[i] != NULL)
// 		{
// 			element->command[i + 1] = ft_strdup(args[j]);
// 			i++;
// 			j++;
// 		}
// 		ft_free_arr(args);
// 	}
// 	element->command[i + 1] = NULL;
// 	if (!pipe_marker)
// 		printf("\n");
// 	i = 0;
// 	while (element->command[i] != NULL)
// 	{
// 		printf("%s	\n", element->command[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	// fill_table_2(element, pipe_marker);
// }