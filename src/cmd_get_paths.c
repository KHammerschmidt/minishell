/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:40 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:41 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_paths(t_vars *ms)
{
	int		i;
	t_env	*current;

	i = 0;
	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, "PATH") == 0)
		{
			ms->paths = ft_split(current->content, ':');
			break ;
		}
		current = current->next;
	}
	if (ms->paths != NULL)
	{
		i = 0;
		while (ms->paths[i] != NULL)
		{
			ms->paths[i] = ft_strjoin(ms->paths[i], "/");
			i++;
		}
	}
	return (0);
}
