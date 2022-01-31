#include "../header/minishell.h"

static int	validate_arg(char *command)
{
	int	i;

	i = 0;
	if (ft_isdigit(command[0]) == 1)
	{
		printf("minishell: export: %s: not a valid identifier\n", command);
		return (1);
	}
	while (command[i] != '\0')
	{
		if (ft_isalpha(command[i]) == 0 && command[i] != '=' && ft_isdigit(command[i]) == 0)
		{
			printf("minishell: export: %s: not a valid identifier\n", command);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Looks for var_name in envar list. If found, changes var_value or, if not */
/* found, creates new node with respective name and content.                */
int	builtin_export(t_vars *ms)
{
	t_env	*current;
	t_env	*new;
	char	*var_name;
	char	*var_val;
	int		i;
	int		j;
	int		k;

	k = 1;
	while (ms->cmd->command[k] != NULL)
	{
		current = ms->env;
		new = NULL;
		var_name = NULL;
		var_val = NULL;
		i = 0;
		j = 0;
		if (validate_arg(ms->cmd->command[k]) == 1)
			return (1);
		while (ms->cmd->command[k][i] != '=' && ms->cmd->command[k][i] != '\0')
			i++;
		if (ms->cmd->command[k][i] == '\0')
		{
			k++;
			continue ;
		}
		var_name = malloc(i + 1);
		var_val = malloc(ft_strlen(ms->cmd->command[1]) - i);
		i = 0;
		while (ms->cmd->command[k][i] != '=')
		{
			var_name[i] = ms->cmd->command[k][i];
			i++;
		}
		var_name[i] = '\0';
		i++;
		while (ms->cmd->command[k][i] != '\0')
		{
			var_val[j] = ms->cmd->command[k][i];
			i++;
			j++;
		}
		var_val[j] = '\0';
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
				i = 0;
				break ;
			}
			current = current->next;
		}
		if (i != 0)
		{
			new = ft_lstnew_env(ms->cmd->command[k]);
			ft_lstadd_back_env(&ms->env, new);
		}
		free(var_name);
		free(var_val);
		k++;
	}
	return (0);
}
