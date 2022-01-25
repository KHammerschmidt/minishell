/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:44:43 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:42:49 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(str2) == 0)
		return ((char *)str1);
	while (str1[i] && i < len)
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (str1[i + j] == str2[j] && (i + j) < len)
			{
				if (str2[j + 1] == '\0')
					return ((char *)str1 + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
