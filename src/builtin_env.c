/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:53:34 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 18:05:35 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	builtin_env(t_ms_vars *ms)
{
	int		i;

	i = 0;
	while (ms->env[i] != NULL)
	{
		write(ms->fd_out, ms->env[i], ft_strlen(ms->env[i]));		// Achtung: Hier muessen aktualisierte VALUES geprintet werden! Muss in builtin_cd() eingefuegt werden!
		write(ms->fd_out, "\n", 1);
		i++;
	}
}