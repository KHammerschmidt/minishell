/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:45:28 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:43:58 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned long	i;

	if (s == 0)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		ptr = malloc(1 * sizeof(char));
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
