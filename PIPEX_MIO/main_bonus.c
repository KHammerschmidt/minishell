/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:48:15 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/22 10:57:31 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/* Function to initiate process if here_doc is given. */
static void	here_doc(t_vars *vars, char **argv, int argc, char **envp)
{
	if (argc < 6)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		exit(EXIT_FAILURE);
	}
	vars->limiter = argv[2];
	vars->cmd_count = argc - 4;
	get_input(vars, argv, envp, 1);
	open_files(vars, 1);
	swap_fd(vars, 1);
	pipex(vars, 1);
	wait(NULL);
	pipex(vars, 0);
}

/* Function to initiate process if no here_doc is given. */
static void	no_here_doc(t_vars *vars, char **argv, int argc, char **envp)
{
	vars->cmd_count = argc - 3;
	get_input(vars, argv, envp, 0);
	open_files(vars, 0);
	swap_fd(vars, 0);
	pipex(vars, 0);
}

/* Main function. Checks for valid number of arguments, whether a here_doc   */
/* is given, calls subsequent functions and initiates while loop to interate */
/* through all commands. Waits for all children processes to end and calls   */
/* destroy_mem() before exit to free allocated memory.                       */
int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	if (argc < 5)
	{
		write(2, "Error: Invalid number of arguments.\n", 36);
		exit(EXIT_FAILURE);
	}
	check_envp(envp);
	init(&vars);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(&vars, argv, argc, envp);
	else
		no_here_doc(&vars, argv, argc, envp);
	(vars.i)++;
	while (vars.i < vars.cmd_count - 1)
	{
		pipex(&vars, 0);
		wait(NULL);
		(vars.i)++;
	}
	last_call(&vars);
	close(vars.fd_out);
	destroy_mem(&vars);
	return (WEXITSTATUS(vars.exit_code));
}
