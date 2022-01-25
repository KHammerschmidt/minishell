/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:49:48 by mortmeie          #+#    #+#             */
/*   Updated: 2022/01/18 17:39:42 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*builtin_cd(t_ms_vars *ms, char *dir)
{
	char	*start_wd;
	char	*home;
	char	*new_path;

	start_wd = getcwd(NULL, PATH_MAX);
	if (start_wd == NULL)
		write(2, "Error.", 6);
	new_path = NULL;
	// home = get_env_var(ms, "HOME");			// eigene Funktion nicht benoetigt, wenn wir getenv() aus stdlib.h nutzen duerfen
	home = getenv("HOME");
	if (dir == NULL && home == NULL)
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	else if (dir == NULL && home != NULL)
		dir = home;
	if (ft_strncmp(dir, "/", 1) == 0)
		new_path = dir;
	else if ((ft_strncmp(dir, ".", 1) == 0 && ft_strncmp(dir, "..", 2) != 0) || ft_strncmp(dir, "..", 2) == 0)
		new_path = dir;
	else
	{
		new_path = ft_strjoin(".", "/");
		new_path = ft_strjoin(new_path, dir);
		if (access(new_path, F_OK) != 0)
			new_path = NULL;
	}
	if (new_path == NULL)
		write(2, "Error with new_path\n", 20);
	else if (ft_strncmp(new_path, "/", 1) != 0)
	{
		new_path = ft_strjoin(start_wd, "/");
		new_path = ft_strjoin(new_path, dir);
	}
	// printf("start_wd: %s\n", start_wd);
	// printf("home:     %s\n", home);
	// printf("dir:      %s\n", dir);
	// printf("new_path:  %s\n", new_path);
	free(ms->line);			// nur fuer den Moment, um "unused parameter" error zu beheben.
	return (new_path);
}
