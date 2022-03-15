/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_abc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:08 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 20:32:42 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	swap_elements(char *tmp1[], char *tmp2[])
{
	char	*tmp_str;

	tmp_str = *tmp1;
	*tmp1 = *tmp2;
	*tmp2 = tmp_str;
}

static void	print_sorted_envp(char **tmp, int i, int j)
{
	i = 0;
	while (tmp[i] != NULL)
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (tmp[i][j] != '=' && tmp[i][j] != '\0')
		{
			ft_putchar_fd(tmp[i][j], STDOUT_FILENO);
			j++;
		}
		if (tmp[i][j] == '=')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			j++;
			while (tmp[i][j] != '\0')
			{
				ft_putchar_fd(tmp[i][j], STDOUT_FILENO);
				j++;
			}
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		i++;
	}
	ft_free_strarray(&tmp);
}

void	declare_x(t_vars *ms)
{
	char	**tmp;
	int		arr_size;
	int		i;
	int		j;

	tmp = NULL;
	i = 0;
	j = 0;
	tmp = copy_strarray(ms->envp);
	while (tmp[i] != NULL)
		i++;
	arr_size = i;
	i = 0;
	while (tmp[i] != NULL)
	{
		j = 0;
		while (j < arr_size)
		{
			if (ft_strncmp(tmp[i], tmp[j], ft_strlen(tmp[i])) < 0)
				swap_elements(&tmp[i], &tmp[j]);
			j++;
		}
		i++;
	}
	print_sorted_envp(tmp, i, j);
}
