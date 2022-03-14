/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:43 by khammers          #+#    #+#             */
/*   Updated: 2022/03/14 19:24:59 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Frees a string passed on with its address. */
void	ft_free_string(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

/* Frees the element of the list t_list. */
void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		lst = &(*lst)->next;
		free(tmp);
		tmp = NULL;
		tmp = *lst;
	}
}

/* Frees the elements and content of t_list. */
void	free_builtin_list(t_vars *ms)
{
	free_list(&ms->builtins);
}

/* Frees the content of each t_env element as well as element itself. */
void	free_t_env(t_env **env)
{
	t_env	*env_tmp;

	env_tmp = *env;
	while (*env != NULL)
	{
		free((*env)->name);
		free((*env)->content);
		env_tmp = (*env)->next;
		free(*env);
		*env = NULL;
		*env = env_tmp;
	}
}

/* Frees all allocated memory and exits the program if necessary. */
void	last_free(t_vars *ms, int e_flag)
{
	free_t_env(&ms->env);
	ft_free_strarray(&ms->envp);
	free_builtin_list(ms);
	free_cmd_struct(ms);
	ft_free_strarray(&ms->paths);
	ft_free_string(&ms->cmd_line);
	ft_free_string(&ms->line);
	if (e_flag == 1)
		exit(ms->exit_status);
}
