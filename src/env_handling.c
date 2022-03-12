/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:45 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:46 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Auxiliary function to update_envp_array(). */
static void	create_envarr_update(t_vars *ms, t_env *current)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (current != NULL)
	{
		tmp = ft_strdup(current->name);
		tmp = ft_strjoin(tmp, "=");
		tmp = ft_strjoin(tmp, current->content);
		ms->envp[i] = ft_strdup(tmp);
		free(tmp);
		tmp = NULL;
		current = current->next;
		i++;
	}
	ms->envp[i] = NULL;
}

/* Takes data from the env list and updates       */
/* env array (for use with execve()) accordingly. */
void	update_envp_array(t_vars *ms)
{
	t_env	*current;
	int		i;

	ft_free_strarray(&ms->envp);
	current = ms->env;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	ms->envp = (char **)malloc((i + 1) * sizeof(char *));
	current = ms->env;
	create_envarr_update(ms, current);
}
