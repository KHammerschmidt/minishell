/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_create_prompt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:33 by khammers          #+#    #+#             */
/*   Updated: 2022/03/14 19:05:14 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Looks for current user in envar list and returns the content of it,
e.g. the user name. */
char	*get_user(t_vars *ms)
{
	char	*user;

	user = NULL;
	if (get_env_var(ms, "USER") && get_env_var(ms, "USER")->content)
		user = ft_strdup(get_env_var(ms, "USER")->content);
	return (user);
}

/* Looks for current working directory in envar list and returns it if found. */
char	*get_pwd(t_vars *ms)
{
	char	*pwd;

	pwd = NULL;
	if (get_env_var(ms, "PWD") && get_env_var(ms, "PWD")->content
		&& ft_strchr(get_env_var(ms, "PWD")->content, '/'))
		pwd = ft_strdup(ft_strrchr(get_env_var(ms, "PWD")->content, '/') + 1);
	return (pwd);
}

/* Tries to concatenate user and current working directory to create a prompt */
/* to be used with readline().                                                */
char	*create_prompt(t_vars *ms)
{
	char	*prompt;
	char	*user;
	char	*pwd;

	prompt = NULL;
	user = get_user(ms);
	pwd = get_pwd(ms);
	if (user != NULL && pwd != NULL)
	{
		prompt = ft_strdup(user);
		prompt = ft_strjoin(prompt, "@");
		prompt = ft_strjoin(prompt, pwd);
		prompt = ft_strjoin(prompt, " ॐ  ");
		ft_free_string(&user);
		ft_free_string(&pwd);
	}
	return (prompt);
}
