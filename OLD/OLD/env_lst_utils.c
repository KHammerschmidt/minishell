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

t_env	*ft_lstlast_env(t_env *lst)
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

void	ft_free_lst_env(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		lst = &(*lst)->next;
		free(tmp);
		tmp = *lst;
	}
}
