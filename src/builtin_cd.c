#include "../header/minishell.h"

static void	create_old_pwd(t_vars *ms, int flag, char *start_wd)
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
	int		flag;

	tmp = NULL;
	flag = 0;
	if (!(ft_strncmp(new_path, "/", 1) == 0) \
			&& !(ft_strncmp(new_path, ".", 1) == 0))
	{
		tmp = malloc(ft_strlen(new_path) + 3);
		ft_strlcat(tmp, "./", 3);
		ft_strlcat(tmp, new_path, ft_strlen(new_path) + 3);
		flag = 1;
	}
	if (access(new_path, F_OK) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", new_path);
		return (1);
	}
	chdir(new_path);
	adjust_envar_list(ms, start_wd);
	update_envp_array(ms);
	if (flag == 1)
		free(tmp);
	if (start_wd)
		free(start_wd);
	return (0);
}

static int	check_special_cases(t_vars *ms, char **new_path, t_env *home)
{
	if ((*new_path == NULL && home->content) || (compare_str(*new_path, "~") == 0 && home->content))
		*new_path = home->content;
	if (compare_str(*new_path, "-") == 0 && get_env_var(ms, "OLDPWD") == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	if (compare_str(*new_path, "-") == 0 && get_env_var(ms, "OLDPWD") != NULL)
		printf("%s\n" ,*new_path = get_env_var(ms, "OLDPWD")->content);
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
		current->error_flag = 1;
		current->error_msg = ft_strdup(strerror(errno));
		return (1);
	}
	new_path = NULL;
	new_path = current->command[1];
	home = get_env_var(ms, "HOME");
	// create separate function to check home directory:
	if (new_path == NULL || compare_str(new_path, "~") == 0)
	{
		if (home == NULL)
		{
			current->error_flag = 1;									// Brauchen wir oder koennen wir einfach mit prinft arbeiten.
			current->error_msg = ft_strdup("Error: HOME not set");		// Dito.
			// for testing until error handling complete:
			printf("Error: HOME not set\n");
			return (1);
		}
		else if (home->content[0] == '\0')
		{
			current->error_flag = 1;
			current->error_msg = ft_strdup("Error: HOME not set");
			// for testing until error handling complete:
			printf("Error: HOME not set\n");
			return (1);
		}
		else
			new_path = home->content;
	}
	if (check_special_cases(ms, &new_path, home) == 1)
		return (1);
	if (validate_and_change_path(ms, new_path, start_wd) == 1)
		return (1);
	return (0);
}
