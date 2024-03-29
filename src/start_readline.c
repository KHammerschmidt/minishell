/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:39 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:40 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Reads user input and saves readline() in ms struct. */
int	read_line(t_vars *ms)
{
	char	*prompt;

	prompt = create_prompt(ms);
	if (ms->cmd_line)
		ft_free_string(&ms->cmd_line);
	rl_init(0);
	if (prompt)
		ms->cmd_line = readline(prompt);
	else
		ms->cmd_line = readline("minishell ॐ  ");
	rl_reset();
	if (ms->cmd_line == NULL)
		last_free(ms, 1);
	if (ms->cmd_line && *ms->cmd_line)
		add_history (ms->cmd_line);
	ft_free_string(&prompt);
	return (0);
}
