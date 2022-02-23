#include "../header/minishell.h"

t_env	*ft_lstnew_env(char *content)
{
	t_env	*new_element;
	char	**split;
	int		i;

	i = 0;
	new_element = malloc(sizeof(t_env));			//malloc new element env
	if (new_element == NULL)
		return (NULL);
	split = ft_split(content, '=');
	if (split == NULL)
	{
		printf("Error\n");
		ft_free_strarray(&split);
		return (NULL);
	}
	new_element->name = ft_strdup(split[i]);
	new_element->content = ft_strdup(split[i + 1]);
	new_element->next = NULL;
	ft_free_strarray(&split);
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
		*lst = new;
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}

// void	ft_free_lst_env(t_env **lst)		//OLD
// {
// 	t_env	*temp;

// 	while (*lst != NULL)
// 	{
// 		temp = *lst;
// 		*lst = (*lst)->next;
// 		free(temp->name);
// 		free(temp->content);
// 		free(temp);
// 	}
// }

/* Function deletes content of every element in the
list t_env. */
// void	ft_free_env_content(t_env **lst)
// {
// 	t_env	*temp;

// 	temp = *lst;
// 	while (temp != NULL)
// 	{
// 		free(temp->name);
// 		free(temp->content);
// 		temp = temp->next;
// 	}
// }

// /* Function deletes every element of the list t_env. */
// void	ft_free_env_list(t_env **lst)
// {
// 	t_env	*temp;

// 	temp = NULL;
// 	while (*lst != NULL)
// 	{
// 		temp = (*lst)->next;
// 		free((*lst));
// 		(*lst) = NULL;
// 		(*lst) = temp;
// 	}
// }
