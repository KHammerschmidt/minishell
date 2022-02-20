/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:29:41 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/20 19:22:41 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strarray(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_intarray(int **arr)
{
	int	i;

	i = 0;
	if (arr == 0)
		return ;
	while (arr[i] != 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}