/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:37:55 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 14:39:25 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*conversion_if_positve(char *result, int digits, long int b)
{
	result[digits] = '\0';
	while (digits > 0)
	{
		result[digits - 1] = (b % 10) + '0';
		b = b / 10;
		digits--;
	}
	return (result);
}

static char	*conversion_if_negative(char *result, int digits, long int b)
{
	result[digits + 1] = '\0';
	while (digits > 0)
	{
		result[digits] = (b % 10) + '0';
		b = b / 10;
		digits--;
	}
	result[0] = '-';
	return (result);
}

static void	aux_operations(int n, int *sign, int *digits, long int *b)
{
	if (*b < 0)
	{
		*sign = 1;
		*b = *b * -1;
	}
	if (n == 0)
		*digits = *digits + 1;
	while (*b >= 1)
	{
		*b = *b / 10;
		*digits = *digits + 1;
	}
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	b;
	int			digits;
	int			sign;

	digits = 0;
	sign = 0;
	b = (long int)n;
	aux_operations(n, &sign, &digits, &b);
	result = malloc(digits * sizeof(char) + sign + 1);
	if (!result)
		return (0);
	if (sign == 1)
	{
		b = (long int)n * -1;
		result = conversion_if_negative(result, digits, b);
	}
	else
	{
		b = (long int)n;
		result = conversion_if_positve(result, digits, n);
	}
	return (result);
}
