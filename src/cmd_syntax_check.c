/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:56:31 by katharinaha       #+#    #+#             */
/*   Updated: 2022/03/11 16:33:41 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	set_quote_index(char *str, int *i, int *quote_type, int *quote_on)
{
	if (*quote_on == 0)
		*quote_type = str[*i];
	if (str[*i] == *quote_type)
	{
		if (*quote_on == 1)
			*quote_on = -1;
		(*quote_on)++;
		(*i)++;
	}
}

static int	ft_syntax_error(t_vars *ms)
{
	printf("Error: syntax error\n");
	ms->exit_status = 258;
	return (1);
}

/* Checks input for open quotes or multiple pipes. */
int	ft_syntax_check(char *str, t_vars *ms)
{
	int	i;
	int	quote_on;
	int	quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	if (quote_status(str) == -1)
		return (ft_syntax_error(ms));
	while (str[i] != '\0')
	{
		if (str[i] == 34 | str[i] == 39)
			set_quote_index(str, &i, &quote_type, &quote_on);
		if (((str[i] == '|' && str[i + 1] == '|')
				|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
				|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			&& quote_on == 0)
			return (ft_syntax_error(ms));
		i++;
	}
	return (0);
}
