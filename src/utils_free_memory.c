#include "../header/minishell.h"

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

void	ft_free_string(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}


static void	free_env_list(t_vars *ms)
{
	t_env	*current;
	t_env	*tmp;

	current = ms->env;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->name != NULL)
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		if (tmp->content != NULL)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
	free(current);
	current = NULL;
}

static void	free_cmd_list(t_vars *ms)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = ms->cmd;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->command != NULL)
		{
			ft_free_strarray(tmp->command);
			tmp->command = NULL;
		}
		if (tmp->execpath != NULL)
		{
			free(tmp->execpath);
			tmp->execpath = NULL;
		}
		if (tmp->error_msg != NULL)
		{
			free(tmp->error_msg);
			tmp->error_msg = NULL;
		}
		// Mio: add additional allocated memory to be freed.
		free(tmp);
		tmp = NULL;
	}
	free(current);
	current = NULL;
}

void	free_builtin_list(t_vars *ms)
{
	free_list(&ms->builtins);
}

void	free_and_exit(t_vars *ms, int e_flag, int e_code)
{
	free_env_list(ms);
	free_cmd_list(ms);
	free_builtin_list(ms);
	if (ms->cmd_line)
	{
		free(ms->cmd_line);
		ms->cmd_line = NULL;
	}
	if (ms->envp)
	{
		ft_free_strarray(ms->envp);
		ms->envp = NULL;
	}
	if (ms->paths)
	{
		ft_free_strarray(ms->paths);
		ms->paths = NULL;
	}
	if (e_flag == 1)
		exit(e_code);
}








// Kathi

/* Frees the content of each t_env element as well as element itself. */
void	free_t_env(t_env **env)	//mit double pointer
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
