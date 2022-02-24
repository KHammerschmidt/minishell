#include "../header/minishell.h"

/* Splits the input cmd_line in according to the quotes. */
static char *lexer_parser_quotes(int quotes, t_vars *ms, char *crr, char *nxt)
{
	if ((ft_strchr_pos(ms->cmd_line, '<') != -1)
		|| ft_strchr_pos(ms->cmd_line, '>') != -1)
		lexer_parser_redirections(&ms->cmd_line, ms);
	else
	{
		ms->info.fd_in = STDIN_FILENO;
		ms->info.fd_out = STDOUT_FILENO;
	}
	if (quotes == -1)
	{
		ft_free_string(&nxt);
		ft_free_string(&crr);
		ms->info.command = NULL;
		return (NULL);
	}
	else
		ms->info.command = ft_split_quotes(ms->cmd_line);
	ft_free_string(&ms->cmd_line);
	if (crr == NULL)
	{
		// ft_free_string(&ms->cmd_line);
		ft_free_string(&crr);
		return (NULL);
	}
	return (crr);
}

/* Splits the input cmd_line in according to the quotes. */
static char *lexer_parser_quotes_pipe(t_vars *ms, int quotes, char *crr, char *nxt)
{
	if ((ft_strchr_pos(crr, '<') != -1)
		|| ft_strchr_pos(crr, '>') != -1)
		lexer_parser_redirections(&crr, ms);
	else
	{
		ms->info.fd_in = STDIN_FILENO;
		ms->info.fd_out = STDOUT_FILENO;
	}
	if (quotes == -1)
	{
		ft_free_string(&nxt);
		ft_free_string(&crr);
		ms->info.command = NULL;
		return (NULL);
	}
	ms->info.command = ft_split_quotes(crr);
	ft_free_string(&crr);
	return (nxt);
}

/* Handles the input cmd_line which include a pipe and compares in accordance to the
priorities (redirection, pipes and quotes). */
char	*lexer_parser_pipe(t_vars *ms, int quotes, char *nxt, char *crr)
{
	int		p_index;

	ms->info.pipe = 1;
	p_index = ft_strchr_pos(ms->cmd_line, '|');
	crr = ft_substr(ms->cmd_line, 0, p_index);
	while (ms->cmd_line[p_index] == ' ' || ms->cmd_line[p_index] == '|')
		p_index++;
	nxt = ft_substr(ms->cmd_line, p_index, ft_strlen(ms->cmd_line) - p_index);
	if ((ft_strchr_pos(crr, '<') != -1) || ft_strchr_pos(crr, '>') != -1)
		lexer_parser_redirections(&crr, ms);
	else
	{
		ms->info.fd_in = STDIN_FILENO;
		ms->info.fd_out = STDOUT_FILENO;
	}
	if (ft_strchr_pos(crr, 34) != -1 || ft_strchr_pos(crr, 39) != -1)
		return (lexer_parser_quotes_pipe(ms, quotes, crr, nxt));
	else
	{
		// if ((ft_strchr_pos(crr, '<') != -1) || ft_strchr_pos(crr, '>') != -1)
		// 	lexer_parser_redirections(&crr, ms);
		ms->info.command = ft_split(crr, ' ');
		ft_free_string(&crr);
		return (nxt);
	}
}

/* Checks for any redirections, splits the cmd_line by spaces and saves
it in t_info command. It returns NULL as there is no next command. */
static char	*lexer_parser_smple(t_vars *ms)
{
	if ((ft_strchr_pos(ms->cmd_line, '<') != -1)
		|| ft_strchr_pos(ms->cmd_line, '>') != -1)
		lexer_parser_redirections(&ms->cmd_line, ms);
	else
	{
		ms->info.fd_in = STDIN_FILENO;
		ms->info.fd_out = STDOUT_FILENO;
	}
	ms->info.command = ft_split(ms->cmd_line, ' ');
	return (NULL);
}

/* Handles pipes, dollar signs, quotes and splits the string accordingly while
saving relevant variables in struct t_info of the first command. The function
returns any following commands of cmd_line or NULL if tehre was only one
command. */
char	*lexer_parser(t_vars *ms)
{
	int		quotes;
	int		p_index;
	char	*crr;
	char	*nxt;

	crr = NULL;
	nxt = NULL;
	p_index = ft_strchr_pos(ms->cmd_line, '|');
	quotes = quote_status(ms->cmd_line);
	if (p_index == -1 && quotes == 0)
		return (lexer_parser_smple(ms));
	if (p_index != -1 && valid_pipe(ms->cmd_line) == 0)
		return (lexer_parser_pipe(ms, quotes, nxt, crr));
	else
		return (lexer_parser_quotes(quotes, ms, crr, nxt));
}
