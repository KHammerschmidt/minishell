/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mio_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:24:24 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 17:59:52 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms_vars	ms;

	argc = 0;
	argv = NULL;
	ms.env = envp;
	ms.cwd = getcwd(NULL, PATH_MAX);
	ms.fd_out = 1;
	while (1)
	{
		ms.line = readline("Type away: ");
		if (ft_strncmp(ms.line, "cd", 2) == 0)
		{
			printf("%s\n", ms.cwd);
			ms.new_wd = builtin_cd(&ms, "../07_minitalk");
			chdir(ms.new_wd);
			ms.cwd = getcwd(NULL, PATH_MAX);
			printf("%s\n", ms.cwd);
		}
		if (ft_strncmp(ms.line, "pwd", 3) == 0)
			builtin_pwd(&ms);
		if (ft_strncmp(ms.line, "env", 3) == 0)
			builtin_env(&ms);
		if (ft_strncmp(ms.line, "exit", 4) == 0)
			exit(0);
	}
	return (0);
}
