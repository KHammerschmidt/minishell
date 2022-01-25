/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:41:13 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 17:52:49 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	builtin_pwd(t_ms_vars *ms)
{
	char	*cwd;

	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
	{
		write(2, "Error", 6);
		return ;
	}
	write(ms->fd_out, cwd, ft_strlen(cwd));
	write(ms->fd_out, "\n", 1);
}