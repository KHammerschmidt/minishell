#include "../header/minishell.h"

static int	validate_arg(char *command, int *i)
{
	if (ft_isdigit(command[0]) == 1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", command);
		return (1);
	}
	export_aux(command, i);
	*i = 0;
	while (command[*i] != '=' && command[*i] != '\0')
		(*i)++;
	if (command[*i] == '\0')
		return (1);
	return (0);
}

static int	create_variable(char **var_name, char **var_val, \
		char *command, int i)
{
	int	j;

	j = 0;
	*var_name = malloc(i + 1);
	if (*var_name == NULL)
		return (1);
	*var_val = malloc(ft_strlen(command) - i);
	if (*var_val == NULL)
		return (1);
	i = 0;
	while (command[i] != '=')
	{
		(*var_name)[i] = command[i];
		i++;
	}
	(*var_name)[i] = '\0';
	i++;
	while (command[i] != '\0')
	{
		(*var_val)[j] = command[i];
		i++;
		j++;
	}
	(*var_val)[j] = '\0';
	return (0);
}

static int	insert_variable(t_vars *ms, char *var_name,
		char *var_val, char *command)
{
	t_env	*current;
	t_env	*new;

	current = ms->env;
	new = NULL;
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
			current->content = ft_strdup(var_val);
			return (0);
		}
		current = current->next;
	}
	new = ft_lstnew_env(command);
	ft_lstadd_back_env(&ms->env, new);
	return (0);
}

static int	export_loop(t_vars *ms, t_cmd *current, int *k)
{
	char	*var_name;
	char	*var_val;
	int		i;

	var_name = NULL;
	var_val = NULL;
	i = 0;
	if (validate_arg(current->command[*k], &i) == 1)
	{
		(*k)++;
		return (0);
	}
	if (create_variable(&var_name, &var_val, current->command[*k], i) == 1)
		return (1);
	if (insert_variable(ms, var_name, var_val, current->command[*k]) == 1)
		return (1);
	ft_free_string(&var_name);
	ft_free_string(&var_val);
	(*k)++;
	return (0);
}

/* Looks for var_name in envar list. If found, changes var_value or, if not */
/* found, creates new node with respective name and content.                */
int	builtin_export(t_vars *ms, t_cmd *current)
{
	int		k;

	k = 1;
	if (current->command[k] == NULL)
	{
		declare_x(ms, current);
		return (0);
	}
	while (current->command[k] != NULL)
	{
		if (export_loop(ms, current, &k) == 1)
			return (1);
	}
	update_envp_array(ms);
	return (0);
}
