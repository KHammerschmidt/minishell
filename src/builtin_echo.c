/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:23:52 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 12:06:16 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	builtin_echo(char *str, int no_nl_flag)
{
	int	i;

	i = 0;
	if (no_nl_flag == 0)
		ft_putstr_fd(str, 1);
	else
	{
		while (str[i] != '\n')
		{
			ft_putchar_fd(str[i], 1);
			i++;
		}
	}
}
