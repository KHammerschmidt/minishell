/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:45:28 by mortmeie          #+#    #+#             */
/*   Updated: 2022/02/13 14:23:07 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned long	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
	{
		ptr = ft_calloc(1, 1);
		return (ptr);
	}
	else if (len > ft_strlen(s) - start)
		ptr = malloc((ft_strlen(s) - start) * sizeof(char) + 1);
	else
		ptr = malloc(len * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	while (s[start + i] && len > 0 && start < ft_strlen(s))
	{
		ptr[i] = s[start + i];
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
