#include "../header/minishell.h"

/* Searches if the to be expanded var is found in env list.
Returns NULL if no otherwise the expanded variable. */
static char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;
	char	*tmp;

	tmp = NULL;
	current = ms->env;
	if (compare_str(var, "?") == 0)
	{
		tmp = ft_itoa(ms->exit_status);
		return (tmp);
	}
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (ft_strdup(current->content));
		current = current->next;
	}
	return (NULL);
}

/* Extracts the variable to be expanded (expansion), checks if it
can be expanded and appends it if so. */
void	check_and_append(t_vars *ms, char **cpy, char *line, int *i)
{
	int		j;
	char	*envar;
	char	*expansion;

	j = *i;
	envar = NULL;
	expansion = NULL;	
	while (line[*i] != ' ' && line[*i] != '$' && line[*i] != '\0')
		(*i)++;
	expansion = ft_substr(line, j, *i - j);
	envar = search_for_var(ms, expansion);
	if (envar != NULL)
	{
		*cpy = ft_strjoin(*cpy, envar);
		ft_free_string(&envar);
	}
	ft_free_string(&expansion);
}

/* Looks for $-signs and expands if variable is found in envar list. */
char	*hdoc_dollar_expansion(t_vars *ms, char *line, int dollar_flag)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	if (dollar_flag != 0 || ft_strchr_pos(line, '$') == -1)
		return (line);
	cpy = ft_strdup("");
	while (line[i] != '\0')
	{		
		while (line[i] != '$' && line[i] != '\0')
		{
			cpy = ft_strjoin_2(cpy, line, i);
			i++;
		}
		if (line[i] == '$')
		{
			i++;
			check_and_append(ms, &cpy, line, &i);
		}
	}
	ft_free_string(&line);
	return (cpy);
}
