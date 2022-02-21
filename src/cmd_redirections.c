/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:01:57 by khammers          #+#    #+#             */
/*   Updated: 2022/02/21 10:02:55 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Searches for redirections signs ('<' & '>') and saves information in t_info.
Sets the fd for input and output to standard value. */
void	handle_redirections(char **string, t_vars *ms)
{
	int		red_in;
	int		red_out;

	red_in = 0;
	red_out = 0;
	red_in = ft_strchr_pos(*string, '<');
	ms->info->fd_in = STDIN_FILENO;
	if (red_in != -1)
		input_redirection(ms, string, red_in);
	else
		ms->info->input_op = 0;
	red_out = ft_strchr_pos(*string, '>');
	ms->info->fd_out = STDOUT_FILENO;
	if (red_out != -1)
		output_redirection(ms, string, red_out);
	else
		ms->info->output_op = 0;
}
