#include "../header/minishell.h"

/* Looks for var_name in envar list. If found, changes var_value or, if not */
/* found, creates new node with respective name and content.                */
int	builtin_export(t_vars *ms, char *var_name, char *var_value)
{
	t_env	*current;
	t_env	*new;
	char	*join;

	current = ms->env;
	new = NULL;
	join = malloc(ft_strlen(var_name) + ft_strlen(var_value) + 2);
	if (current == NULL)
	{
		write(2, "Error. No environment variables found.\n", 39);
		return (1);
	}
	while (current != NULL)
	{
		if (compare_str(current->name, var_name) == 0)
		{
			free(current->content);
			current->content = ft_strdup(var_value);
			return (0);
		}
		current = current->next;
	}
	ft_strlcat(join, var_name, ft_strlen(var_name) + 1);
	ft_strlcat(join, "=", ft_strlen(join) + 2);
	ft_strlcat(join, var_value, ft_strlen(join) + ft_strlen(var_name) + 2);
	new = ft_lstnew_env(join);
	ft_lstadd_back_env(&ms->env, new);
	free(join);
	return (0);
}
