#include "../header/minishell.h"

static void	adjust_envar_list(t_vars *ms, char *start_wd)
{
	t_env	*current;
	int		flag;

	flag = 0;
	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, "OLDPWD") == 0)
		{
			free(current->content);
			current->content = ft_strdup(start_wd);
			flag++;
		}
		if (compare_str(current->name, "PWD") == 0)
		{
			free(current->content);
			current->content = getcwd(NULL, PATH_MAX);
		}
		current = current->next;
	}
	create_old_pwd(ms, flag, start_wd);
}

int	validate_and_change_path(t_vars *ms, char *new_path, char *start_wd)
{
	char	*tmp;

	tmp = NULL;
	if (!(ft_strncmp(new_path, "/", 1) == 0) \
			&& !(ft_strncmp(new_path, ".", 1) == 0))
	{
		tmp = malloc(ft_strlen(new_path) + 3);
		ft_strlcat(tmp, "./", 3);
		ft_strlcat(tmp, new_path, ft_strlen(new_path) + 3);
	}
	if (access(new_path, F_OK) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", new_path);
		return (1);
	}
	chdir(new_path);
	adjust_envar_list(ms, start_wd);
	update_envp_array(ms);
	ft_free_string(&tmp);
	ft_free_string(&start_wd);
	return (0);
}

static int	check_special_cases(t_vars *ms, char **new_path, t_env *home)
{
	if ((*new_path == NULL && home->content) \
			|| (compare_str(*new_path, "~") == 0 && home->content))
		*new_path = home->content;
	if (compare_str(*new_path, "-") == 0 && get_env_var(ms, "OLDPWD") == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (compare_str(*new_path, "-") == 0 && get_env_var(ms, "OLDPWD") != NULL)
		printf("%s\n", *new_path = get_env_var(ms, "OLDPWD")->content);
	return (0);
}

int	check_home_and_path(char *new_path, t_env *home)
{
	if (new_path == NULL || compare_str(new_path, "~") == 0)
	{
		if (home == NULL)
		{
			printf("Error: HOME not set\n");
			return (1);
		}
		else if (home->content[0] == '\0')
		{
			printf("Error: HOME not set\n");
			return (1);
		}
		else
			new_path = home->content;
	}
	return (0);
}

/* Gets home directory from envar list, concatenates and changes path. */
/* Changes OLDPWD and PWD in envar list.                               */
int	builtin_cd(t_vars *ms, t_cmd *current)
{
	char	*start_wd;
	char	*new_path;
	t_env	*home;

	start_wd = getcwd(NULL, PATH_MAX);
	if (start_wd == NULL)
	{
		ms->exit_status = errno;
		return (ms->exit_status);
	}
	new_path = NULL;
	new_path = current->command[1];
	home = get_env_var(ms, "HOME");
	if (check_home_and_path(new_path, home) == 1)
		return (1);
	if (check_special_cases(ms, &new_path, home) == 1)
		return (1);
	if (validate_and_change_path(ms, new_path, start_wd) == 1)
		return (1);
	return (0);
}
