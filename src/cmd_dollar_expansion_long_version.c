#include "../header/minishell.h"

char	*search_for_var(t_vars *ms, char *var)
{
	t_env	*current;

	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, var) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

char	*dollar_expansion(t_vars *ms, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*var;
	char	*ret;

	i = 0;
	j = 0;
	tmp = NULL;
	var = NULL;
	ret = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, j, i - j);
			if (ret == NULL)
				ret = ft_strdup(tmp);
			else
				ret = ft_strjoin(ret, tmp);
			free(tmp);
			i++;
			j = i;
			while (ft_isalpha(str[i]) == 1)
				i++;
			var = ft_substr(str, j, i - j);
			tmp = ft_strdup(search_for_var(ms, var));
			if (tmp == NULL)
			{
				ret = ft_strjoin(ret, "$");
				ret = ft_strjoin(ret, var);
			}
			else
				ret = ft_strjoin(ret, tmp);
			j = i;
			// printf("var: %s\n", var);
			free(var);
			free(tmp);
		}
		else
			i++;
	}
	tmp = ft_substr(str, j, i - j);
	if (ret == NULL)
		ret = ft_strdup(tmp);
	else
		ret = ft_strjoin(ret, tmp);
	free(tmp);
	return (ret);
}
