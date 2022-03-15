/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:01 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 20:30:00 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Writes envar list to corresponding output. */
int	builtin_env(t_vars *ms)
{
	t_env	*tmp;

	tmp = ms->env;
	while (tmp != NULL)
	{
		write(STDOUT_FILENO, tmp->name, ft_strlen(tmp->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, tmp->content, ft_strlen(tmp->content));
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}
