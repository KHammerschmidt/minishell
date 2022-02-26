#include "../header/minishell.h"

/* Resets a standard fd (STDIN/STDOUT) in the parent process with its previous
value, saved in fd_temp. */
static void	reset_standard_fd(int standard, int fd_temp)
{
	if (dup2(fd_temp, standard) < 0)
		perror("Error: reset standard fd ");
}

/* Duplicates in case of an infile or outfile redirection the fd of
the file with the STDIN/STDOUT. */
static void	dup2_fd_parent_builtin(int fd_in, int standard)
{
	if (dup2(fd_in, standard) < 0)
		perror("Error: dup2 ");
}

/* Duplicates the STDIN/STDOUT fds into temp fds in case of an infile/
outfile redirection. Executes the builtin and swaps STDIN/STDOUT back
to its standard value. */
int	ft_builtin_parent(t_cmd *current, t_vars *ms)
{
	int	temp_fd_in;
	int	temp_fd_out;

	temp_fd_in = dup(STDIN_FILENO);
	temp_fd_out = dup(STDOUT_FILENO);
	if (temp_fd_in == -1 || temp_fd_out == -1)
		perror("Error: dup standard fd failed\n");
	else
	{
		if (current->input_op == -1)
			dup2_fd_parent_builtin(current->fd_in, STDIN_FILENO);
		if (current->output_op == -1 || current->output_op == -2)
			dup2_fd_parent_builtin(current->fd_out, STDOUT_FILENO);
		execute_builtin(ms, current);
		if (STDIN_FILENO != temp_fd_in)
			reset_standard_fd(STDIN_FILENO, temp_fd_in);
		if (STDOUT_FILENO != temp_fd_out)
			reset_standard_fd(STDOUT_FILENO, temp_fd_out);
	}
	close(temp_fd_in);
	close(temp_fd_out);
	return (ms->exit_status);
}
