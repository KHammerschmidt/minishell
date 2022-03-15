/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:18 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 20:33:10 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Gets current working directory and writes it to the corresponding output. */
int	builtin_pwd(t_vars *ms)
{
	char	*cwd;

	(void)ms;
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		ms->exit_status = errno;
		return (ms->exit_status);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (0);
}
