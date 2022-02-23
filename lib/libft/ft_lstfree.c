/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:21:50 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/22 16:42:45 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_list(t_list **head)
{
	t_list	*tmp;

	tmp = NULL;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		tmp = NULL;
	}
}
