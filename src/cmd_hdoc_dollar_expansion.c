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
		ft_free_string(&var);
		return (tmp);
	}
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (ft_strdup(current->content));
		current = current->next;
	}
	ft_free_string(&var);
	return (NULL);
}

/* Looks for $-signs and expands if variable is found in envar list. */
char	*hdoc_dollar_expansion(t_vars *ms, char *line)
{
	int		i;
	int		j;
	char	*cpy;
	char	*envar;
	char	*expansion;

	i = 0;
	j = 0;
	cpy = NULL;
	envar = NULL;
	expansion = NULL;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '$' && line[i] != '\0')
			i++;
		if (cpy == NULL)
			cpy = ft_substr(line, j, i);					//copy for the first time part of string that is before $ sign
		else if (line[i] != '$' || (j + 1)< i)
			cpy = ft_strjoin(cpy, ft_substr(line, j, i));	//when there is no dollar sign append the rest of the string
		else if (line[i] == '$')							//when there is a dollar sign!
		{
			i++;
			j = i;
			while (line[i] != '\0' && line[i] != ' ' && line[i] != '$')
				i++;
			expansion = ft_substr(line, j, i - j);
			envar = search_for_var(ms, expansion);
			if (envar != NULL)
			{
				cpy = ft_strjoin(cpy, envar);
				ft_free_string(&envar);
			}
		}
	}
	return (cpy);
}


