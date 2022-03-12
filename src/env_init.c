/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:48 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:49 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* In case of error when initialising t_env: function frees the allocated
memory and prints the error message. */
static int	ft_error_env(t_vars *ms, char **tmp)
{
	printf("Error\n");
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
	free_t_env(&ms->env);
	return (-1);
}

/* Initiates t_env struct by copying the content of env into the struct,
differentiated between the name and content of the row. */
int	init_env(t_vars *ms, char **envp)
{
	int		i;
	char	*tmp;
	t_env	*node;

	i = 0;
	node = NULL;
	tmp = NULL;
	if (!envp)
		return (1);
	ms->envp = copy_strarray(envp);
	while (envp[i] != NULL && envp)
	{
		tmp = ft_strdup(envp[i]);
		if (tmp == NULL)
			return (ft_error_env(ms, &tmp));
		node = ft_lstnew_env(tmp);
		if (node == NULL)
			return (ft_error_env(ms, &tmp));
		ft_lstadd_back_env(&ms->env, node);
		free(tmp);
		i++;
	}
	return (0);
}
