/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_qhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:21 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 11:30:28 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	handle_dquotes(char *str, int *i, int quote_type, char **line)
{
	while (str[*i] != quote_type)
	{
		*line = ft_strjoin_2(*line, str, *i);
		(*i)++;
	}
	*line = ft_strjoin_2(*line, str, *i);
}

void	handle_squotes(char *str, int *i, int quote_2, char **line)
{
	if (quote_2 == 39 && closed_single_quote_in_double_quote(str, *i) == 0)
	{
		while (str[*i] != quote_2)
		{
			if (str[*i] == ' ')
				*line = ft_strjoin_2(*line, str, *i);
			(*i)++;
		}
		*line = ft_strjoin_2(*line, str, *i);
	}
	else
	{
		while (str[*i] != 34)
		{
			*line = ft_strjoin_2(*line, str, *i);
			(*i)++;
		}
	}
}

void	handle_dsign(t_quotes *qt, char *str)
{
	if (str[qt->i] == '$' && ft_isspace(str[qt->i + 1]) == 0 \
		&& str[qt->i + 1] != '\0')
	{
		if (qt->quote_type == 39)
			handle_dquotes(str, &qt->i, qt->quote_type, &qt->line);
		else if (qt->quote_type == 34)
			handle_squotes(str, &qt->i, qt->quote_2, &qt->line);
		else
		{
			while (ft_isspace(str[qt->i]) == 0 && str[qt->i] != '\0' \
				&& str[qt->i] != 34 && str[qt->i] != 39)
				qt->i++;
			return ;
		}
		qt->quote_type = 0;
		qt->quote_on = 0;
	}
	else
		qt->line = ft_strjoin_2(qt->line, str, qt->i);
	qt->i++;
}
