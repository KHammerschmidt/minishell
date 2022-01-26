#include "../header/minishell.h"

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

void	fill_table_2(t_cmd *element, int pipe_marker)
{
	if (pipe_marker == -1)
		element->pipe = 0;
	else
		element->pipe = 1;
	// fill_operators(str, element);
	// free(command);
	// free(args);
	// free(str);
}

void	fill_table(t_cmd *cmd, char *str, int pipe_marker)
{
	t_cmd	*element;
	int		pos;
	char	*command;
	char	*args;

	args = NULL;
	command = NULL;
	element = cmd;
	pos = ft_strchr_pos(str, ' ');
	element = ft_lstnew_cmd();
	ft_lstadd_back_cmd(&cmd, element);
	if (pos != -1)							//pos == -1 --> no space has been found, e.g. command only consists of one word
	{
		command = ft_substr(str, 0, pos);
		args = ft_substr(str, pos, ft_strlen(str) - pos);
		element->args = ft_strdup(args);
	}
	else
		command = ft_substr(str, 0, ft_strlen(str));
	element->command = ft_strdup(command);
	fill_table_2(element, pipe_marker);
}

void	print_lst(t_vars *ms)
{
	t_cmd *tmp;

	tmp = ms->cmd;
		printf("\nSimple Command Table\n");
		printf("COMMAND			ARGS	LESS=3, LESSLESS=4, GREAT=5, GREATGREAT=6	pipe		NULL\n");
	while (tmp->next != NULL)
	{
		printf("%s			%s		%d			  	 	 %d\n", tmp->next->command, tmp->next->args, tmp->next->op, tmp->next->pipe);
		tmp = tmp->next;
	}
}

/* Splits the input line by it's pipes and fills the simple command table command by command. */
int	create_cmd_table(t_vars *ms)
{
	int		i;
	char	*tmp;

	i = 0;
	while (1)
	{
		i = ft_strchr_pos(ms->cmd_line, '|');						//find position of pipe
		if (i == -1)												// no pipe was found
		{
			if (ms->cmd_line != NULL)
				fill_table(ms->cmd, ms->cmd_line, i);
			// ft_free_string(ms->cmd_line);						// Mio: error (free before allocated), why??
			break ;
		}
		tmp = ft_substr(ms->cmd_line, 0, i);						//create substring from start of line until pipe
		fill_table(ms->cmd, tmp, i);								//put content in list
		ft_free_string(tmp);
		while (ms->cmd_line[i] == ' ' || ms->cmd_line[i] == '|')
			i++;
		tmp = ft_strdup(&ms->cmd_line[i]);
		ft_free_string(ms->cmd_line);
		ms->cmd_line = ft_substr(tmp, 0, ft_strlen(tmp));
		ft_free_string(tmp);
		i = 0;
	}
	return (0);
	// print_lst(ms);
}

// ______________________________________________________________________________________________________________________________________________________

// int	chop_input_in_cmds(t_vars *ms)
// {
// 	// char	*line;
// 	// line = readline("");
// 	// if (line == NULL)
// 	// 	return (1);
// 	// create_cmd_table(ms->cmd, ms->cmd_line);
// 	// print_lst(ms->cmd);
// 	return (0);
// }

// char	*split_cmds(char *line, t_cmd *cmd)
// {
// 	char	*command;
// 	char	*args;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = ft_strchr_pos(line, " ");
// 	if (j != 0)
// 	{
// 		command = ft_substr(line, 0, j);
// 		args = ft_substr(line, j, ft_strlen(line) - j);
// 		printf("command: %s | args: \n", command, args);
// 	}

// }

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

// void	split_line(char *str, char *command, char *args)
// {
// 	int	pos;

// 	pos = ft_strchr_pos(str, ' ');
// 	command = ft_substr(str, 0, pos);
// 	args = ft_substr(str, pos, ft_strlen(str) - pos);
// }

// t_cmd	*init_cmd_element(t_cmd *cmd)
// {
// 	t_cmd	*element;

// 	element = ft_lstnew_cmd();
// 	ft_lstadd_back_cmd(&cmd, element);

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