#include "../header/minishell.h"

/* Gets home directory from envar list, concatenates and changes path. */
/* Changes OLDPWD and PWD in envar list.                               */
int	builtin_cd(t_vars *ms, char *dir)
{
	t_env	*current;
	char	*start_wd;
	char	*new_path;
	char	*home;

	current = ms->env;
	if ((start_wd = getcwd(NULL, PATH_MAX)) == NULL)
		perror("cwd");
	new_path = NULL;
	home = ft_strdup((get_env_var(ms, "HOME"))->content);
	printf("%s\n", home);
	if (dir == NULL && home == NULL)
	{
		write(2, "No directory given\n", 19);
		return (1);
	}
	if (dir == NULL && home != NULL)
		dir = home;
	if (ft_strncmp(dir, "/", 1) == 0 || ft_strncmp(dir, ".", 1) == 0)
		new_path = dir;
	else
		new_path = ft_strjoin("./", dir);
	if (access(new_path, F_OK) != 0)
	{
			perror("cd");
			return (errno);
	}
	chdir(new_path);
	while (current != NULL)
	{
		if (compare_str(current->name, "OLDPWD") == 0)
		{
			free(current->content);
			current->content = ft_strdup(start_wd);
		}
		if (compare_str(current->name, "PWD") == 0)
		{
			free(current->content);
			current->content = getcwd(NULL, PATH_MAX);
		}
		current = current->next;
	}
	if (new_path)
		free(new_path);
	if (start_wd)
		free(start_wd);
	return (0);
}
