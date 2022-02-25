/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:42:52 by khammers          #+#    #+#             */
/*   Updated: 2022/02/25 11:54:54 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
int	create_cmd_table(t_vars *ms)
{
	char	*nxt_cmd_line;
	t_cmd	*new;

	nxt_cmd_line = NULL;
	new = NULL;
	if (ft_strchr_pos(ms->cmd_line, '$') != -1)
	{
		dollar_expansion(ms);
		ms->cmd_line = cut_unused_envar(ms->cmd_line);
	}
	while (ms->cmd_line != NULL)
	{
		nxt_cmd_line = lexer_parser(ms);
		if (nxt_cmd_line == NULL && ms->flag == 1)
		{
			printf("Error: Open quotes\n");
			ms->exit_status = 1;
			ms->flag = 0;
			return (1);
		}
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
	return (0);
}