/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:44:51 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/22 19:14:53 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			tmp = &((char *)s)[i];
			i++;
		}
		else
			i++;
	}
	if (s[i] == (unsigned char)c)
		tmp = &((char *)s)[i];
	return (tmp);
}
