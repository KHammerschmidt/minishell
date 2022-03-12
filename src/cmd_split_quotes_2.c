/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_quotes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:30 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:31 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Indicates if the found quote is an opening (within_quotes == 0) or closing
(within_quotes == 1) quote and changes the status. */
int	check_open_closed_quote(char *str, int stop, int *within_quotes, int quote)
{
	if (str[stop] == quote && (*within_quotes) == 0)
		(*within_quotes)++;
	else if (str[stop] == quote)
		(*within_quotes) = 0;
	return (*within_quotes);
}

/* Checks the quote status, returns (0) for no quotes, (1) for valid
quotes and (-1) for open quotes. */
int	quote_status(char *str)
{
	int	i;
	int	quote_on;
	int	quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == 34 || str[i] == 39) && quote_on == 0)
			quote_type = str[i];
		if (str[i] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
		}
		i++;
	}
	if (quote_on == 1)
		return (-1);
	if (quote_type == 0)
		return (0);
	return (1);
}
