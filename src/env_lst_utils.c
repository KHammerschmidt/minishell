/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:51 by khammers          #+#    #+#             */
/*   Updated: 2022/03/14 19:55:58 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	create_element_name(char *content, char *tmp, \
	t_env *new_element, int *i)
{
	while (content[*i] != '=')
		(*i)++;
	tmp = malloc((*i + 1) * (sizeof(char)));
	*i = 0;
	while (content[*i] != '=')
	{
		tmp[*i] = content[*i];
		(*i)++;
	}
	tmp[*i] = '\0';
	new_element->name = ft_strdup(tmp);
	ft_free_string(&tmp);
	(*i)++;
}

static void	create_element_content(char *content, char *tmp, \
	t_env *new_element, int i)
{
	int		j;

	j = i;
	i = 0;
	while (content[i] != '\0')
		i++;
	tmp = malloc((i + 1) * sizeof(char));
	i = j;
	j = 0;
	while (content[i] != '\0')
	{
		tmp[j] = content[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	new_element->content = ft_strdup(tmp);
	ft_free_string(&tmp);
}

t_env	*ft_lstnew_env(char *content)
{
	t_env	*new_element;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	new_element = malloc(sizeof(t_env));
	if (new_element == NULL)
		return (NULL);
	create_element_name(content, tmp, new_element, &i);
	create_element_content(content, tmp, new_element, i);
	new_element->next = NULL;
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
