#include "../header/minishell.h"

t_env	*ft_lstnew_env(char *content)
{
	t_env	*new_element;
	char	**tmp;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	new_element = malloc(sizeof(t_env));
	if (new_element == NULL)
		return (NULL);
	tmp = ft_split(content, '=');
	if (tmp == NULL)
	{
		printf("Error\n");
		ft_free_strarray(tmp);
		return (NULL);
	}
	new_element->name = ft_strdup(tmp[i]);
	new_element->content = ft_strdup(tmp[i + 1]);
	new_element->next = NULL;
	ft_free_strarray(tmp);
	return (new_element);
}

static t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*last;

	last = lst;
	if (last == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = new;
}

// void	ft_free_lst_env(t_env **lst)
// {
// 	t_env	*tmp;

// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		lst = &(*lst)->next;
// 		free(tmp);
// 		tmp = *lst;
// 	}
// }

void	ft_free_lst_env(t_env **lst)
{
	t_env	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}

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
