/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dollar_expand_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:33 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:34 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	no_envar_found(t_vars *ms, char *var)
{
	if (ms->line == NULL)
	{
		ms->line = ft_strdup("$");
		ms->line = ft_strjoin(ms->line, var);
	}
	else
	{
		ms->line = ft_strjoin(ms->line, "$");
		ms->line = ft_strjoin(ms->line, var);
	}
}
