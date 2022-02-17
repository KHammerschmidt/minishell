#include "../header/minishell.h"

/* Auxiliary function to update_envp_array(). */
static void	create_envarr_update(t_vars *ms, t_env *current)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (current != NULL)
	{
		tmp = ft_strdup(current->name);
		tmp = ft_strjoin(tmp, "=");
		tmp = ft_strjoin(tmp, current->content);
		ms->envp[i] = ft_strdup(tmp);
		// printf("%s\n", ms->envp[i]);
		free(tmp);
		tmp = NULL;
		current = current->next;
		i++;
	}
	ms->envp[i] = NULL;
}

/* Takes data from the env list and updates       */
/* env array (for use with execve()) accordingly. */
void	update_envp_array(t_vars *ms)
{
	t_env	*current;
	int		i;

	ft_free_strarray(ms->envp);
	current = ms->env;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	// printf("ms->env: %d\n", i);
	ms->envp = (char **)malloc(i * sizeof(char *));
	current = ms->env;
	create_envarr_update(ms, current);
}
