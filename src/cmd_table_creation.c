#include "../header/minishell.h"

/* Splits the input cmd_line in according to the quotes. */
static char *handle_quotes_pipe(int quotes, t_vars *ms, char *curr_cmd_line, char *new_cmd_line)
{
	handle_redirections(&ms->cmd_line, ms);
	if (quotes == -1)
	{
		ft_free_string(&new_cmd_line);
		ft_free_string(&curr_cmd_line);
		ms->info.command = NULL;
		return (NULL);
	}
	ms->info.command = ft_split_quotes(curr_cmd_line);
	ft_free_string(&curr_cmd_line);
	return (new_cmd_line);
}

/* Splits the input cmd_line in according to the quotes. */
static char *handle_quotes(int quotes, t_vars *ms, char *curr_cmd_line, char *new_cmd_line)
{
	handle_redirections(&ms->cmd_line, ms);
	if (quotes == -1)
	{
		ft_free_string(&new_cmd_line);
		ms->info.command = NULL;
	}
	else
		ms->info.command = ft_split_quotes(ms->cmd_line);
	ft_free_string(&curr_cmd_line);
	return (NULL);
}

/* Handles the input cmd_line which include a pipe and compares in accordance to the
priorities (redirection, pipes and quotes). */
char	*handle_pipe(t_vars *ms, int quotes, char *new_cmd_line, char *curr_cmd_line)
{
	int	p_marker;
	char	**array;

	array = NULL;
	p_marker = ft_strchr_pos(ms->cmd_line, '|');
	ms->info.pipe = 1;
	curr_cmd_line = ft_substr(ms->cmd_line, 0, p_marker);
	while (ms->cmd_line[p_marker] == ' ' || ms->cmd_line[p_marker] == '|')
		p_marker++;
	new_cmd_line = ft_substr(ms->cmd_line, p_marker, ft_strlen(ms->cmd_line) - p_marker);
	handle_redirections(&curr_cmd_line, ms);
	if (ft_strchr_pos(curr_cmd_line, 34) != -1 || ft_strchr_pos(curr_cmd_line, 39) != -1)
		return (handle_quotes_pipe(quotes, ms, curr_cmd_line, new_cmd_line));
	else
	{
		ms->info.command = ft_split(curr_cmd_line, ' ');
		ft_free_strarray(&array);
		ft_free_string(&curr_cmd_line);
		return (new_cmd_line);
	}
	// array = ft_split(curr_cmd_line, ' ');
	// ms->info.command = copy_strarray(array);		// ms->info.command = ft_split(curr_cmd_line, ' ');
	// ft_free_strarray(&array);
	// ft_free_string(&curr_cmd_line);
	// return (new_cmd_line);
}

/* Handles pipes, dollar signs, quotes and splits the string accordingly while
saving relevant variables in struct t_info of the first command. The function
returns any following commands of cmd_line or NULL if tehre was only one
command. */
static char	*handle_input(t_vars *ms)
{
	int		quotes;
	int		pipe_marker;
	char	*curr_cmd_line;
	char	*new_cmd_line;

	curr_cmd_line = NULL;
	new_cmd_line = NULL;
	pipe_marker = ft_strchr_pos(ms->cmd_line, '|');
	quotes = check_quote_status(ms->cmd_line);
	if (pipe_marker == -1 && quotes == 0)
	{
		handle_redirections(&ms->cmd_line, ms);
		ms->info.command = ft_split(ms->cmd_line, ' ');
		return (NULL);
	}
	else if (pipe_marker != -1 && pipe_validity(ms->cmd_line) == 0)
		return (handle_pipe(ms, quotes, new_cmd_line, curr_cmd_line));
	else
		return (handle_quotes(quotes, ms, curr_cmd_line, new_cmd_line));
}

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
void	create_cmd_table(t_vars *ms)
{
	char	*tmp;
	t_cmd	*new;

	tmp = NULL;
	new = NULL;
	dollar_expansion(ms);
	while (ms->cmd_line != NULL)
	{
		tmp = handle_input(ms);
		new = ft_lstnew_cmd(&ms->info);
		ft_lstadd_back_cmd(&ms->cmd, new);
		ft_free_string(&ms->cmd_line);
		if (tmp == NULL)
		{
			ft_free_string(&tmp);
			break ;
		}
		ms->cmd_line = ft_strdup(tmp);
		ft_free_string(&tmp);
	}

}
