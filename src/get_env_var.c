/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:19:30 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 12:06:19 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_env_var(t_ms_vars *ms, char *var_name)
{
	int		i;

	i = -1;
	while (ms->env[++i] != NULL)
	{
		if (ft_strncmp(ms->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			return (&ms->env[i][ft_strlen(var_name) + 1]);
		}
	}
	return (NULL);
}
