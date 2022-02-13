/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:11:44 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/19 12:01:02 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/* Tries to open infile, tries to open or create outfile (with O_TRUNC) */
/* when no here_doc is given.                                           */
static void	open_in_and_out(t_vars *vars)
{
	vars->fd_in = open(vars->input_file, O_RDONLY);
	if (vars->fd_in < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	vars->fd_out = open(vars->output_file, O_WRONLY
			| O_TRUNC | O_CREAT, 0644);
	if (vars->fd_out < 0)
	{
		perror("Error opening or creating output file");
		exit(EXIT_FAILURE);
	}
}

/* Calls open_in_and_out() if no here_doc is given. If here_doc is given, */
/* tries to open or to create outfile (with O_APPEND).                    */
void	open_files(t_vars *vars, int h)
{
	if (h == 0)
		open_in_and_out(vars);
	if (h == 1)
	{
		vars->fd_out = open(vars->output_file, O_WRONLY
				| O_APPEND | O_CREAT, 0644);
		if (vars->fd_out < 0)
		{
			perror("Error opening or creating output file");
			exit(EXIT_FAILURE);
		}
	}
}

/* Without here_doc, uses dup2() to swap infile / outfile file   */
/* descriptors with STDIN and STDOUT for main process. Otherwise */
/* just swaps STDOUT with outfile.                               */
void	swap_fd(t_vars *vars, int h)
{
	if (h == 0)
	{
		if (dup2(vars->fd_in, STDIN_FILENO) < 0)
		{
			perror("Error (dup2)");
			exit(EXIT_FAILURE);
		}
		close(vars->fd_in);
	}
	if (h == 0 || h == 1)
	{
		if (dup2(vars->fd_out, STDOUT_FILENO) < 0)
		{
			perror("Error (dup2)");
			exit(EXIT_FAILURE);
		}
	}
}

/* In case of here_doc, uses get_next_line() to read from  */
/* STDIN and writes to STDOUT (pipe[1]). Exits upon        */
/* finding here_doc limiter.                               */
void	stdin_to_pipe(t_vars *vars)
{
	int		len;
	char	*line;

	len = ft_strlen(vars->limiter);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_FAILURE);
		if (line[len] == '\n' && vars->limiter
			&& !ft_strncmp(line, vars->limiter, len))
			exit(EXIT_SUCCESS);
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
		line = NULL;
	}
}
