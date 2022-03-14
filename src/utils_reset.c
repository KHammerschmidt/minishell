/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:46 by khammers          #+#    #+#             */
/*   Updated: 2022/03/14 19:23:28 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Frees euch element of t_cmd. */
static void	ft_free_lst_cmd(t_cmd **element)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (*element != NULL)
	{
		tmp = *element;
		*element = (*element)->next;
		free(tmp);
		tmp = NULL;
	}
}

/* Frees the content of t_cmd struct and then every element.  */
void	free_cmd_struct(t_vars *ms)
{
	t_cmd	*current;

	current = ms->cmd;
	while (current != NULL)
	{
		ft_free_strarray(&current->command);
		ft_free_string(&current->execpath);
		ft_free_string(&current->infile);
		ft_free_string(&current->outfile);
		current = current->next;
	}
	ft_free_lst_cmd(&ms->cmd);
}

/* Resets the allocated memory and variables needed for the next input. */
void	reset(t_vars *ms)
{
	ft_free_string(&ms->cmd_line);
	ft_free_strarray(&ms->paths);
	free_cmd_struct(ms);
	ft_free_string(&ms->line);
	if (ms->tmp_fd != STDIN_FILENO)
	{
		close(ms->tmp_fd);
		ms->tmp_fd = dup(STDIN_FILENO);
	}
}
