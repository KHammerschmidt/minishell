#include "../header/minishell.h"

int	get_paths(t_vars *ms)
{
	int		i;
	t_env	*current;

	i = 0;
	current = ms->env;
	while (current != NULL)
	{
		if (compare_str(current->name, "PATH") == 0)
		{
			ms->paths = ft_split(current->content, ':');				//alloc memory
			if (!ms->paths)
				// free_and_exit(ms, 1, 1);
				return (1);				// change to correct exit code
			break ;
		}
		current = current->next;
	}
	i = 0;
	while (ms->paths[i] != NULL)
	{
		ms->paths[i] = ft_strjoin(ms->paths[i], "/");
		// if (!ms->paths)							// brauchen wir das? wozu?
		// 	free_and_exit(ms, 1, 1);				// change to correct exit code
		i++;
	}
	return (0);
}

// int	get_paths(t_vars *ms)
// {
// 	int		i;
// 	t_env	*current;
// 	char	**temp;

// 	i = 0;
// 	temp = NULL;
// 	current = ms->env;
// 	while (current != NULL)
// 	{
// 		if (compare_str(current->name, "PATH") == 0)
// 		{
// 			temp = ft_split(current->content, ':');				//alloc memory
// 			i++;
// 			if (!temp)
// 				// free_and_exit(ms, 1, 1);
// 				return (1);				// change to correct exit code
// 			break ;
// 		}
// 		current = current->next;
// 	}
// 	ms->paths = (char **)ft_calloc(sizeof(char *), i + 1);
// 	i = 0;
// 	while (temp != NULL && temp[i] != NULL)
// 	{
// 		printf("temp[i] = %s\n", temp[i]);
// 		ms->paths[i] = ft_strjoin(temp[i], "/");
// 		// temp[i] = ft_strjoin(temp[i], "/");
// 		// ms->paths[i] = ft_strjoin(temp[i], "/");
// 		printf("ms->paths[i] = %s\n", ms->paths[i]);
// 		// if (!ms->paths)							// brauchen wir das? wozu?
// 		// 	free_and_exit(ms, 1, 1);				// change to correct exit code
// 		i++;
// 	}
// 	return (0);
// }
