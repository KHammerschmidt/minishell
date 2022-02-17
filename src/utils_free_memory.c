#include "../header/minishell.h"

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
	}
	ms->env = NULL;
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
	}
	ms->cmd = NULL;
}

// static void	free_bi_list(t_vars *ms)
// {

// }

void	free_and_exit(t_vars *ms, int e_flag, int e_code)
{
	free_env_list(ms);
	free_cmd_list(ms);
	// free_bi_list(ms);
	free_list(&ms->builtins);
	if (ms->cmd_line)
	{
		free(ms->cmd_line);
		ms->cmd_line = NULL;
	}
	// if (ms->envp)					// malloc double free error after update_env_array()
	// {
	// 	ft_free_strarray(ms->envp);
	// 	ms->envp = NULL;
	// }
	if (ms->paths)
	{
		ft_free_strarray(ms->paths);
		ms->paths = NULL;
	}
	if (e_flag == 1)
		exit(e_code);
}