/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:18 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:19 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks whether delimiter has open (-1), double (0) or single quotes (1)
which would influence the dollar expansion of the read line. */
static int	hdoc_dollar_sign(char *limiter)
{
	int		i;
	int		quote_on;
	int		quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	while (limiter[i] != '\0')
	{
		if ((limiter[i] == 34 || limiter[i] == 39) && quote_on == 0)
			quote_type = limiter[i];
		if (limiter[i] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
		}
		i++;
	}
	if (quote_on != 0)
		return (-1);
	if (quote_on == 0 && quote_type == 39)
		return (1);
	return (0);
}

/* Checks if content of here_doc is subject to dollar sign expansion
with dollar_flag. Cuts quotes from the delimiter. */
int	prepare_hdoc_expansion(t_vars *ms, int *dollar_flag, char **limiter)
{
	char	*temp;

	temp = NULL;
	*dollar_flag = hdoc_dollar_sign(*limiter);
	if (*dollar_flag == -1)
	{
		ms->info.flag = 1;
		printf("Error: open quote in limiter\n");
		return (-1);
	}
	temp = cut_quotes(*limiter);
	ft_free_string(limiter);
	*limiter = ft_strdup(temp);
	ft_free_string(&temp);
	return (0);
}
