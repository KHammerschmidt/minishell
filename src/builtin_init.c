#include "../header/minishell.h"

void	add_builtin(t_vars *ms, char *builtin)		//lst
{
	t_list	*element;

	element = ft_lstnew(builtin);
	ft_lstadd_back(&ms->lst, element);
	// printf("%s\n", element->content);
}

void	init_builtin(t_vars *ms)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (i == 0)
			add_builtin(ms, "echo");
		if (i == 1)
			add_builtin(ms, "cd");
		if (i == 2)
			add_builtin(ms, "pwd");
		if (i == 3)
			add_builtin(ms, "export");
		if (i == 4)
			add_builtin(ms, "unset");
		if (i == 5)
			add_builtin(ms, "env");
		if (i == 6)
			add_builtin(ms, "exit");
		i++;
	}
}


// ---------------------	---------------------	---------------------	---------------------
// void	init_builtin(t_vars *ms)			//arr
// {
// 	int	i;

// 	i = 0;
// 	ms->arr[i] = ft_strdup("echo");
// 	ms->arr[i + 1] = ft_strdup("cd");
// 	ms->arr[i + 2] = ft_strdup("pwd");
// 	ms->arr[i + 3] = ft_strdup("export");;
// 	ms->arr[i + 4] = ft_strdup("unset");
// 	ms->arr[i + 5] = ft_strdup("env");
// 	ms->arr[i + 6] = ft_strdup("exit");
// 	ms->arr[i + 7] = NULL;

// 	i = 0;
// 	while (ms->arr[i])
// 		printf("%s\n", ms->arr[i++]);
// }
