/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:29:41 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/24 00:25:37 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strarray(char ***arr)
{
	int	i;

	if (*arr == NULL)
		return ;
	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);				// Kathi: has to be in here otherwise it creates 1 leaks for env line
							// Mio: Deleted to get rid of "Invalid read" / "Invalid Write" (VALGRIND)
	*arr = NULL;
}
