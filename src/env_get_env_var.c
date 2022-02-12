#include "../header/minishell.h"

/* Circles through envar list, looking for var_name and, if found, returns */
/* pointer to respective node. Else returns NULL.                          */
t_env	*get_env_var(t_vars *ms, char *var_name)
{
	t_env	*current;

	if (!var_name)
		return (NULL);
	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, var_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
