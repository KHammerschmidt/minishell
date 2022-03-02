#include "../header/minishell.h"

/* Intercepts SIGINT (CTRL+C) and prevents minishell from quitting, prints */
/* empty new line instead. Does nothing for SIGQUIT (CTRL+\).              */
void	signal_handler_0(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_1(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

/* Initialises signal handling and terminal output for readline(). */
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
