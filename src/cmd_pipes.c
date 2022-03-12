/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:06 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:07 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Checks if single and double quotes are even numbered until a
pipe is hit. */
int	valid_pipe(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[i] != '|')
	{
		if (str[i] == 34)
			double_quote++;
		if (str[i] == 39)
			single_quote++;
		i++;
	}
	if ((double_quote % 2) != 0 || (single_quote % 2) != 0)
		return (1);
	return (0);
}
