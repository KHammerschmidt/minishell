/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:44:26 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:42:13 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_string;

	if (s == 0)
		return (0);
	i = 0;
	new_string = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!new_string)
		return (NULL);
	while (s[i] != '\0')
	{
		new_string[i] = (f)(i, s[i]);
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
