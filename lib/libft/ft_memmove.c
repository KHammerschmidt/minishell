/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:41:22 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:47:00 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_tmp;
	char	*src_tmp;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	dst_tmp = (char *)dst;
	src_tmp = (char *)src;
	if (src_tmp < dst_tmp)
	{
		while (len > 0)
		{
			dst_tmp[len - 1] = src_tmp[len - 1];
			len--;
		}
	}
	while (i < len)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dst);
}
