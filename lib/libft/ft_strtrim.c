/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:45:06 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 15:43:30 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	set_start_end(const char *set, const char *s1, int *start, int *end)
{
	while (in_set(set, s1[*start]) == 1 && s1[*start] != '\0')
		*start = *start + 1;
	while (in_set(set, s1[*end]) == 1 && *end > 0)
		*end = *end - 1;
	*end = *end + 1;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	set_start_end(set, s1, &start, &end);
	if (start > end)
		ptr = malloc(1 * sizeof(char));
	else
		ptr = malloc((end - start) * sizeof(char) + 1);
	if (!ptr)
		return (0);
	if (start > end)
		ptr[0] = '\0';
	else
	{
		ft_memmove(ptr, &s1[start], (end - start));
		ptr[(end - start)] = '\0';
	}
	return (ptr);
}
