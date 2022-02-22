/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:29:41 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/21 18:41:54 by mortmeie         ###   ########.fr       */
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
	// free(arr);				// Mio: Deleted to get rid of "Invalid read" / "Invalid Write" (VALGRIND)
	// arr = NULL;
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