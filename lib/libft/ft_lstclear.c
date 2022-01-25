/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:39:57 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 14:39:59 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;
	t_list	*delete;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		delete = current->content;
		(del)(delete);
		free(current);
		current = next;
	}
	*lst = NULL;
}
