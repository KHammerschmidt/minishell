#include "../header/minishell.h"

static int	validate_arg(char *command, int *i)
{
	if (ft_isdigit(command[0]) == 1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", command);
		return (1);
	}
	while (command[*i] != '\0')
	{
		if (ft_isalpha(command[*i]) == 0 && command[*i] != '=' \
				&& command[*i] != '_' && ft_isdigit(command[*i]) == 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n", command);
			return (1);
		}
		(*i)++;
	}
	*i = 0;
	while (command[*i] != '=' && command[*i] != '\0')
		(*i)++;
	if (command[*i] == '\0')
		return (2);
	return (0);
}

static int	create_variable(char **var_name, char **var_val, \
		char *command, int i)
{
	int	j;

	j = 0;
	*var_name = malloc(i + 1);
	if (*var_name == NULL)
		return (1);													// TODO: exit status
	*var_val = malloc(ft_strlen(command) - i);
	if (*var_val == NULL)
		return (1);													// TODO: exit status
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

static int	insert_variable(t_vars *ms, char *var_name, char *var_val, int k)
{
	t_env	*current;
	t_env	*new;
	int		i;

	current = ms->env;
	new = NULL;
	i = 0;
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
	new = ft_lstnew_env(ms->cmd->command[k]);
	ft_lstadd_back_env(&ms->env, new);
	return (0);
}

/* Looks for var_name in envar list. If found, changes var_value or, if not */
/* found, creates new node with respective name and content.                */
int	builtin_export(t_vars *ms)
{
	t_env	*current;
	char	*var_name;
	char	*var_val;
	int		i;
	int		k;

	k = 1;
	while (ms->cmd->command[k] != NULL)
	{
		current = ms->env;
		var_name = NULL;
		var_val = NULL;
		i = 0;
		if (validate_arg(ms->cmd->command[k], &i) == 1)
			return (1);													// TODO: exit status
		if (validate_arg(ms->cmd->command[k], &i) == 2)
		{
			k++;
			continue ;
		}
		create_variable(&var_name, &var_val, ms->cmd->command[k], i);
		if (insert_variable(ms, var_name, var_val, k) == 1)
			return (1);													// TODO: exit status
		free(var_name);
		free(var_val);
		k++;
	}
	return (0);
}
