#include "../header/minishell.h"

/* Intercepts SIGINT (CTRL+C) and prevents minishell from quitting, prints */
/* empty new line instead. Does nothing for SIGQUIT (CTRL+/).              */
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	rl_redisplay();
}

/* Initialises signal handling and terminal output for readline(). */
void	rl_init(void)
{
	struct termios	termios_p;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
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
