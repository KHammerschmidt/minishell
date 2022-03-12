/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:17:27 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:28 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Intercepts SIGINT (CTRL+C) during readline call and prevents	*/
/* minishell from quitting, prints empty new line instead.		*/
void	signal_handler_0(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* Intercepts SIGINT (CTRL+C) during heredoc readline call.	*/
/* Exits heredoc and returns to minishell.					*/
void	signal_handler_1(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	rl_replace_line("", 0);
}

/* Initiates signal handling and terminal output for readline(). */
void	rl_init(int i)
{
	struct termios	termios_p;

	if (i == 0)
		signal(SIGINT, signal_handler_0);
	if (i == 1)
		signal(SIGINT, signal_handler_1);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(1, &termios_p);
	if (termios_p.c_lflag & ECHOCTL)
	{
		termios_p.c_lflag &= ~ECHOCTL;
		tcsetattr(1, 0, &termios_p);
	}
}

/* Resets signal handling and terminal output after using readline(). */
void	rl_reset(void)
{
	struct termios	termios_p;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcgetattr(1, &termios_p);
	if (!(termios_p.c_lflag & ECHOCTL))
	{
		termios_p.c_lflag |= ECHOCTL;
		tcsetattr(1, 0, &termios_p);
	}
}
