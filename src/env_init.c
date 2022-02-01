#include "../header/minishell.h"

int	init_env(t_vars *ms, char **envp)
{
	int		i;
	char	*tmp;
	t_env	*node;

	node = NULL;
	i = 0;
	if (!envp)
		return (1);
	while (envp[i] != '\0' && envp)
	{
		tmp = ft_strdup(envp[i]);
		if (tmp == NULL)
		{
			printf("Error\n");
			free(tmp);
			ft_free_lst_env(&ms->env);
			return (-1);
		}
		node = ft_lstnew_env(tmp);
		if (node == NULL)
		{
			printf("Error\n");
			free(tmp);
			ft_free_lst_env(&ms->env);
			return (-1);
		}
		ft_lstadd_back_env(&ms->env, node);
		free(tmp);
		i++;
	}
	return (0);
}


// int	init_env(t_vars *ms, char **envp)					//lst
// {
// 	int		i;
// 	char	*tmp;
// 	t_env	*node;

// 	node = NULL;
// 	i = 0;
// 	if (!envp)
// 		return (1);
// 	while (envp[i] != '\0' && envp)
// 	{
// 		tmp = ft_strdup(envp[i]);
// 		if (tmp == NULL)
// 		{
// 			free(tmp);
// 			ft_free_lst_env(&ms->env);
// 			return (1);
// 		}
// 		node = ft_lstnew_env(tmp);
// 		ft_lstadd_back_env(&ms->env, node);
// 		free(tmp);
// 		i++;
// 	}
// 	return (0);
// }

//  --------------------- ---------------------	---------------------	---------------------
// int	init_env(t_vars *ms, char **envp)			//arr
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	if (!envp)
// 		return (-1);
// 	printf("HERE\n");
// 	while (envp[i] != '\0')						///here is the error!
// 	{
// 		tmp = ft_strdup(envp[i]);
// 		ms->env[i] = ft_strdup(tmp);
// 		free(tmp);
// 		printf("HERE\n");
// 		i++;
// 	}
// 	envp[i] = NULL;
// 	return (0);
// }