/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:42:52 by khammers          #+#    #+#             */
/*   Updated: 2022/02/25 16:52:05 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*cut_unused_quotes(t_vars *ms)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (ms->cmd_line[i] != '\0')
	{
		if ((ms->cmd_line[i] == 34) && (ms->cmd_line[i + 1] == 34))
		{
			i++;
			if (ms->cmd_line[i] == '\0')
				break ;
		}
		else
			temp = ft_strjoin_2(temp, ms->cmd_line, i);
		i++;
	}
	ft_free_string(&ms->cmd_line);
	return (temp);
}


/* Creates the simple command table, e.g. the char **command of struct t_cmd. */
int	create_cmd_table(t_vars *ms)
{
	char	*nxt_cmd_line;
	t_cmd	*new;

	new = NULL;
	nxt_cmd_line = NULL;
	if (ft_strchr_pos(ms->cmd_line, '$') != -1)
	{
		dollar_expansion(ms);
		ms->cmd_line = cut_unused_envar(ms->cmd_line);
		ms->cmd_line = cut_unused_quotes(ms);
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
		new = ft_lstnew_cmd(ms);
		ft_lstadd_back_cmd(&ms->cmd, new);
		if (nxt_cmd_line == NULL)
		{
			ft_free_string(&nxt_cmd_line);
			ft_free_string(&ms->cmd_line);
			break ;
		}
		ft_free_string(&ms->cmd_line);
		ms->cmd_line = ft_strdup(nxt_cmd_line);
		ft_free_string(&nxt_cmd_line);
	}
	return (0);
}
