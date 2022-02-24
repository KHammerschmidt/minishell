/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:42:52 by khammers          #+#    #+#             */
/*   Updated: 2022/02/24 16:42:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
void	create_cmd_table(t_vars *ms)
{
	char	*nxt_cmd_line;
	t_cmd	*new;

	nxt_cmd_line = NULL;
	new = NULL;
	if (ft_strchr_pos(ms->cmd_line, '$') != -1)
		dollar_expansion(ms);
	while (ms->cmd_line != NULL)
	{
		nxt_cmd_line = lexer_parser(ms);
		new = ft_lstnew_cmd(&ms->info);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (nxt_cmd_line == NULL)
		{
			ft_free_string(&nxt_cmd_line);
			ft_free_string(&ms->cmd_line);			//freeing error
			break ;
		}
		ft_free_string(&ms->cmd_line);
		ms->cmd_line = ft_strdup(nxt_cmd_line);
		ft_free_string(&nxt_cmd_line);
	}
}