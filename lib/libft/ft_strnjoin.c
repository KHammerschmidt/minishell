/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:07:11 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/26 17:07:13 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Joins two strings. */
char	*ft_strnjoin(char *s1, char s2, ssize_t bytes)
{
	char	*strnw;
	int		i;

	i = 0;
	if (s1 != NULL)
		bytes = ft_strlen(s1);
	strnw = (char *)ft_calloc(bytes + 2, sizeof(char));
	if (strnw == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		strnw[i] = s1[i];
		i++;
	}
	strnw[i] = s2;
	strnw[i + 1] = '\0';
	if (s1)
		free(s1);
	return (strnw);
}
