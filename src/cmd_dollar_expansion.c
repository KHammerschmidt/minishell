/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dollar_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:36 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 22:00:24 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

static void	add_expanded_var(t_vars *ms, int *i, int *j)
{
	char	*tmp;
	char	*var;

	var = ft_substr(ms->cmd_line, *j, *i - *j);
	tmp = search_for_var(ms, var);
	if (tmp == NULL)
		no_envar_found(ms, var);
	else
	{
		if (ms->line == NULL)
			ms->line = ft_strdup(tmp);
		else
			ms->line = ft_strjoin(ms->line, tmp);
	}
	*j = *i;
	ft_free_string(&var);
	ft_free_string(&tmp);
}

static void	replicate_text(t_vars *ms, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(ms->cmd_line, *j, *i - *j);
	if (ms->line == NULL)
		ms->line = ft_strdup(tmp);
	else
		ms->line = ft_strjoin(ms->line, tmp);
	ft_free_string(&tmp);
	(*i)++;
	*j = *i;
}

static void	generate_new_line(t_vars *ms, int *i, int *j)
{
	replicate_text(ms, i, j);
	while (ft_isspace(ms->cmd_line[*i]) == 0 && ms->cmd_line[*i] != '\0' \
		&& ms->cmd_line[*i] != 34 && ms->cmd_line[*i] != 39 \
		&& ms->cmd_line[*i] != '/')
		(*i)++;
	add_expanded_var(ms, i, j);
}

/* Looks for $-signs and expands if respective variable is found in envar
list. */
void	dollar_expansion(t_vars *ms)
{
	int		i;
	int		j;
	int		quote_on;
	int		quote_type;

	i = 0;
	j = 0;
	quote_on = 0;
	quote_type = 0;
	while (ms->cmd_line[i] != '\0')
	{
		quote_type = valid_dollar_sign(ms, i, &quote_on, quote_type);
		if (ms->cmd_line[i] == '$' && quote_type != 39)
			generate_new_line(ms, &i, &j);
		else
			i++;
	}
	replicate_text(ms, &i, &j);
	ft_free_string(&ms->cmd_line);
	ms->cmd_line = ft_strdup(ms->line);
}
