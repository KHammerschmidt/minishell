#include "../header/minishell.h"

/* In case of error when initialising t_env: function frees the allocated
memory and prints the error message. */
static int	ft_error_env(t_vars *ms, char **tmp)
{
	printf("Error\n");//explicit error messages?
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	// ft_free_lst_env(&ms->env);
	free_t_env(&ms->env);
	return (-1);
}

/* Initiates t_env struct by copying the content of env into the struct,
differentiated between the name and content of the row. */
int	init_env(t_vars *ms, char **envp)
{
	int		i;
	char	*tmp;
	t_env	*node;

	i = 0;
	node = NULL;
	tmp = NULL;
	if (!envp)
		return (1);
	ms->envp = copy_strarray(envp);
	while (envp[i] != NULL && envp)	// NULL ersetzen durch '\0'
	{
		tmp = ft_strdup(envp[i]);
		if (tmp == NULL)
			return (ft_error_env(ms, &tmp));
		node = ft_lstnew_env(tmp);				//mem alloc for list element env
		if (node == NULL)
			return (ft_error_env(ms, &tmp));
		ft_lstadd_back_env(&ms->env, node);
		free(tmp);
		i++;
	}
	return (0);
}
