/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:47 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:48 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	reset_info_struct(t_vars *ms)
{
	ft_free_strarray(&ms->info.command);
	ft_free_string(&ms->info.infile);
	ft_free_string(&ms->info.outfile);
	ms->info.input_op = 0;
	ms->info.output_op = 0;
	ms->info.pipe = 0;
	ms->info.fd_in = 0;
	ms->info.fd_out = 1;
	ms->info.flag = 0;
}

/* Passes on the information from command, fds and redirections
to the struct t_cmd. */
void	pass_on_infos_node(t_vars *ms, t_cmd *node)
{
	node->command = copy_strarray(ms->info.command);
	node->input_op = ms->info.input_op;
	node->output_op = ms->info.output_op;
	node->fd_out = ms->info.fd_out;
	node->fd_in = ms->info.fd_in;
	node->flag = ms->info.flag;
	if (ms->info.infile != NULL)
		node->infile = ft_strdup(ms->info.infile);
	else
		node->infile = NULL;
	if (ms->info.outfile != NULL)
		node->outfile = ft_strdup(ms->info.outfile);
	else
		node->outfile = NULL;
	reset_info_struct(ms);
}
