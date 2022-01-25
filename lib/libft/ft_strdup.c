/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:43:02 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:40:59 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc((ft_strlen(s1) * sizeof(char)) + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, (ft_strlen(s1) * sizeof(char)) + 1);
	return (ptr);
}
