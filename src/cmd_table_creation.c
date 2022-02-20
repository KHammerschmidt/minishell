#include "../header/minishell.h"

/* Splits the input cmd_line in according to the quotes. */
static char *handle_quotes_pipe(int quotes, t_vars *ms, char *command_line, char *new_cmd_line)
{
	int	pipe_marker;

	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	handle_redirections(&ms->cmd_line, ms);
	if (quotes == 0)
		ms->info->command = ft_split(command_line, ' ');
	else if (quotes == -1)
	{
		ft_free_string(new_cmd_line);
		ft_free_string(command_line);
		return (NULL);
	}
	else
		ms->info->command = ft_split_quotes(command_line);
	return (new_cmd_line);
}


/* Splits the input cmd_line in according to the quotes. */
static char *handle_quotes(int quotes, t_vars *ms, char *command_line, char *new_cmd_line)
{
	handle_redirections(&ms->cmd_line, ms);
	if (quotes == -1)
	{
		ft_free_string(new_cmd_line);
		ft_free_string(command_line);
	}
	else
		ms->info->command = ft_split_quotes(ms->cmd_line);
	return (NULL);
}

/* Handles the input cmd_line which include a pipe and compares in accordance to the
priorities (redirection, pipes and quotes). */
char	*handle_pipe(t_vars *ms, int quotes, char *new_cmd_line, char *command_line)
{
	int	pipe_marker;

	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	ms->info->pipe = 1;
	command_line = ft_substr(ms->cmd_line, 0, pipe_marker);
	while (ms->cmd_line[pipe_marker] == ' ' || ms->cmd_line[pipe_marker] == '|')
		pipe_marker++;
	new_cmd_line = ft_substr(ms->cmd_line, pipe_marker, ft_strlen(ms->cmd_line) - pipe_marker);
	handle_redirections(&command_line, ms);
	ms->info->command = ft_split(command_line, ' ');
	if (ft_strchr(command_line, 34) != NULL || ft_strchr(command_line, 39) != NULL)
		return (handle_quotes_pipe(quotes, ms, command_line, new_cmd_line));
	return (new_cmd_line);
}

/* Handles pipes, dollar signs, quotes and splits the string accordingly while
saving relevant variables in struct t_info of the first command. The function
returns any following commands of cmd_line or NULL if tehre was only one
command. */
static char	*handle_input(t_vars *ms)
{
	int		pipe_marker;
	int		quotes;
	char	*command_line;
	char	*new_cmd_line;

	command_line = NULL;
	new_cmd_line = NULL;
	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	quotes = check_quote_status(ms->cmd_line);
	if (pipe_marker == -1 && quotes == 0)
	{
		handle_redirections(&ms->cmd_line, ms);
		ms->info->command = ft_split(ms->cmd_line, ' ');
		return (NULL);
	}
	else if (pipe_marker != -1 && pipe_validity(ms->cmd_line) == 0)
		return (handle_pipe(ms, quotes, new_cmd_line, command_line));
	else
		return (handle_quotes(quotes, ms, command_line, new_cmd_line));
}

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
void	create_cmd_table(t_vars *ms)
{
	char	*tmp;
	t_cmd	*new;

	tmp = (char *)malloc(sizeof(ms->cmd_line) + 1);
	if (!tmp)
		printf("MEM ALLOC ERROR!\n");					//exit function einbauen
	dollar_expansion(ms);
	ft_free_string(ms->cmd_line);
	ms->cmd_line = ft_strdup(ms->line);
	while (ms->cmd_line != NULL)
	{
		tmp = handle_input(ms);
		new = ft_lstnew_cmd(ms->info);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (tmp == NULL)
			break ;
		free(ms->cmd_line);
		ms->cmd_line = NULL;
		ms->cmd_line = ft_strdup(tmp);
		free(tmp);
	}
}
