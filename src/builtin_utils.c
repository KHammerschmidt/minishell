/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:26 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:27 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Auxiliary function for builtin_cd(). */
void	create_old_pwd(t_vars *ms, int flag, char *start_wd)
{
	t_env	*new;
	char	*tmp;

	tmp = NULL;
	new = NULL;
	if (flag == 0)
	{
		tmp = ft_strdup("OLDPWD=");
		tmp = ft_strjoin(tmp, start_wd);
		new = ft_lstnew_env(tmp);
		ft_lstadd_back_env(&ms->env, new);
		free(tmp);
		tmp = NULL;
	}
}

int	export_aux(char *command, int *i)
{
	while (command[*i] != '=' && command[*i] != '\0')
	{
		if (ft_isalpha(command[*i]) == 0 && command[*i] != '=' \
				&& command[*i] != '_' && ft_isdigit(command[*i]) == 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n", command);
			return (1);
		}
		(*i)++;
	}
	while (command[*i] != '\0')
	{
		if (ft_isalpha(command[*i]) == 0 && command[*i] != '=' \
				&& command[*i] != '_' && ft_isdigit(command[*i]) == 0 \
				&& command[*i] != '/' && command[*i] != '-' \
				&& command[*i] != ' ')
		{
			printf("minishell: export: `%s': not a valid identifier\n", command);
			return (1);
		}
		(*i)++;
	}
	return (0);
}
