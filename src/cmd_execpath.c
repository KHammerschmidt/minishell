#include "../header/minishell.h"

/* The command's executable path is being searched in the environment
variable and then the string splitted using ft_split(). Afterwards
a '/' is appended to append the cmd later. */
// void	ft_get_exec_path(t_vars *ms)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (ms->env[j] != NULL)
// 	{
// 		if (ft_strnstr(ms->env[j], "PATH=", 5) != 0)
// 			break ;
// 		j++;
// 	}
// 	ms->cmd->execpath = ft_split(&(ms->env[j][5]), ':');
// 	while (ms->cmd->execpath[i])
// 	{
// 		tmp = ft_strjoin(ms->cmd->execpath[i], "/");
// 		free(ms->cmd->execpath[i]);
// 		ms->cmd->execpath[i] = *tmp;
// 		i++;
// 	}
// }






// -------------------------------------------------------------------------------------------------------------------
// void	ft_get_exec_path(char *envp[], t_struct *data)
// {
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (envp[j] != NULL)
// 	{
// 		if (ft_strnstr(envp[j], "PATH=", 5) != 0)
// 			break ;
// 		j++;
// 	}
// 	data->execpath = ft_split(&envp[j][5], ':');
// 	while (data->execpath[i])
// 	{
// 		tmp = ft_strjoin(data->execpath[i], "/");
// 		free(data->execpath[i]);
// 		data->execpath[i] = tmp;
// 		i++;
// 	}
// }