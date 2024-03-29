/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:22 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:23 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	validate_arg(char *command)
{
	int	i;

	i = 0;
	if (ft_isdigit(command[0]) == 1)
	{
		printf("minishell: unset: `%s': not a valid identifier\n", command);
		return (1);
	}
	while (command[i] != '\0')
	{
		if (ft_isalpha(command[i]) == 0 && command[i] != '=' \
				&& ft_isdigit(command[i]) == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", command);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_first_element(t_vars *ms, char *command)
{
	t_env	*current;

	current = ms->env;
	if (current == NULL)
	{
		write(2, "Error. No environment variables found.\n", 39);
		return (2);
	}
	if (validate_arg(command) == 1)
		return (1);
	if (compare_str(current->name, command) == 0)
	{
		ms->env = current->next;
		free(current->name);
		free(current->content);
		free(current);
		current = NULL;
		return (1);
	}
	return (0);
}

int	check_other_elements(t_env **prev, t_env **current, char *command)
{
	if (compare_str((*current)->name, command) == 0)
	{
		(*prev)->next = (*current)->next;
		free((*current)->name);
		free((*current)->content);
		free(*current);
		*current = NULL;
		return (1);
	}
	*prev = *current;
	*current = (*current)->next;
	return (0);
}

static void	auxiliary(t_env *prev, t_env *tmp, t_cmd *current, int *i)
{
	prev = tmp;
	tmp = tmp->next;
	while (tmp != NULL)
		check_other_elements(&prev, &tmp, current->command[*i]);
	(*i)++;
}

/* Looks for var_name in envar list and deletes the respective node if found. */
int	builtin_unset(t_vars *ms, t_cmd *current)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (current->command[i] != NULL)
	{
		tmp = ms->env;
		prev = NULL;
		if (check_first_element(ms, current->command[i]) == 1)
		{
			i++;
			continue ;
		}
		else if (check_first_element(ms, current->command[i]) == 2)
			return (1);
		else
			auxiliary(prev, tmp, current, &i);
	}
	update_envp_array(ms);
	return (0);
}
