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
char	*hdoc_dollar_expansion(t_vars *ms, char *line)
{
	int		i;
	char	*cpy;

	i = 0;
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

// OLD
// char	*hdoc_dollar_expansion(t_vars *ms, char *line)
// {
// 	int		i;
// 	int		j;
// 	char	*cpy;
// 	char	*envar;
// 	char	*expansion;

// 	i = 0;
// 	j = 0;
// 	cpy = NULL;
// 	envar = NULL;
// 	expansion = NULL;
// 	while (line[i] != '\0')
// 	{		
// 		j = i;
// 		while (line[i] != '$' && line[i] != '\0')
// 			i++;
// 		if (cpy == NULL)
// 			cpy = ft_substr(line, j, i);					//copy for the first time part of string that is before $ sign
// 		else if (line[i] != '$' || (j + 1)< i)
// 			cpy = ft_strjoin(cpy, ft_substr(line, j, i));	//when there is no dollar sign append the rest of the string
// 		else if (line[i] == '$')							//when there is a dollar sign!
// 		{
// 			i++;
// 			j = i;
// 			while (line[i] != '\0' && line[i] != ' ' && line[i] != '$')
// 				i++;
// 			expansion = ft_substr(line, j, i - j);
// 			envar = search_for_var(ms, expansion);
// 			if (envar != NULL)
// 			{
// 				cpy = ft_strjoin(cpy, envar);
// 				ft_free_string(&envar);
// 			}
// 		}
// 	}
// 	return (cpy);
// }
