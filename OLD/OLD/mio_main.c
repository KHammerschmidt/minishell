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

/* Main function, mainly for testing builtins. However, a few */
/* lines (x) will have to be incoprated into the final main.  */
int	main(int argc, char **argv, char **envp)
{
	t_vars	ms;
	// char	*prompt;
 
	argc = 0;
	argv = NULL;
	ms = (t_vars) {0};								// (x)
	init_env(&ms, envp);
	ms.cwd = getcwd(NULL, PATH_MAX);
	ms.fd_out = 1;
	// prompt = NULL;
	// while (1)
	// {
	// 	if (prompt)
	// 	{
	// 		free (prompt);
	// 		prompt = NULL;
	// 	}
	// 	prompt = create_prompt(&ms);				// (x)
	// 	if (ms.line)
	// 	{
	// 		free (ms.line);
	// 		ms.line = NULL;
	// 	}
	// 	rl_init();									// (x)
	// 	if (prompt)
	// 		ms.line = readline(prompt);
	// 	else
	// 		ms.line = readline("minishell #  ");
	// 	rl_reset();									// (x)
	// 	if (ms.line == NULL)						// (x) Makes CTRL+D work.
	// 	{
	// 		exit(EXIT_SUCCESS);						// Achtung: exit() durch eigene Funktion ersetzen, inkl. free() etc.
	// 	}
	// 	if (ms.line && *ms.line)
	// 		add_history (ms.line);
		// if (compare_str(ms.line, "cd") == 0)
		// 	builtin_cd(&ms, NULL);
		// if (compare_str(ms.line, "echo") == 0)
		// 	builtin_echo(&ms, "Hello world.", 0);
		// if (compare_str(ms.line, "pwd") == 0)
		// 	builtin_pwd(&ms);
		// if (compare_str(ms.line, "env") == 0)
		// 	builtin_env(&ms);
		// if (compare_str(ms.line, "unset") == 0)
		// 	builtin_unset(&ms, "USER");
		// if (compare_str(ms.line, "export") == 0)
		// 	builtin_export(&ms, "TEST", "test23");
		// if (compare_str(ms.line, "exit") == 0)
		// 	break ;
	}
	free(prompt);
	free(ms.line);
	free(ms.cwd);
	ft_free_lst_env(&ms.env);
	system("leaks minishell > leaks.txt");
	return (0);
}
