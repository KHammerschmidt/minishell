/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:36:21 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/19 16:33:33 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

/* Initialises variables inside the struct to be passed around functions. */
int	init(t_vars *vars)
{
	vars->i = 0;
	vars->env = NULL;
	vars->my_paths = NULL;
	ft_bzero(vars->pipe, 2);
	vars->fd_in = 0;
	vars->fd_out = 0;
	vars->input_file = NULL;
	vars->output_file = NULL;
	vars->cmd_count = 0;
	vars->cmds_all = NULL;
	vars->cmd = NULL;
	vars->cmd_path = NULL;
	vars->exit_code = 0;
	vars->limiter = NULL;
	return (0);
}

/* Frees all allocated memory. */
int	destroy_mem(t_vars *vars)
{
	ft_free_strarray(vars->my_paths);
	ft_free_strarray(vars->cmd);
	free(vars->cmd_path);
	vars->cmd_path = NULL;
	return (0);
}

/* Destroys allocated memory before returning perror() */
/* and exiting the process.                            */
void	exit_on_error(t_vars *vars)
{
	destroy_mem(vars);
	perror("Error");
	exit(EXIT_FAILURE);
}
