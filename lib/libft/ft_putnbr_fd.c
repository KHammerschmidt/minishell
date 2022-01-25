/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:41:58 by mortmeie          #+#    #+#             */
/*   Updated: 2021/07/14 14:42:23 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printborder(int fd)
{
	write(fd, "-2147483648", 11);
}

static void	display_number(char *number, int i, int fd)
{
	while (i >= 1)
	{
		ft_putchar_fd(number[i - 1], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num_str[11];
	int		i;

	if (n == -2147483648)
		ft_printborder(fd);
	else if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		i = 0;
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		while (n != 0)
		{
			num_str[i] = (n % 10) + '0';
			n = n / 10;
			i++;
		}
		display_number(num_str, i, fd);
	}
}
