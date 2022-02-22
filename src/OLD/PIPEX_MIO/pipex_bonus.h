/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:28:29 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/19 16:32:27 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* ************************************************************************ */
/*								INCLUDES									*/
/* ************************************************************************ */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"

/* ************************************************************************ */
/*								STRUCTS										*/
/* ************************************************************************ */

typedef struct s_vars
{
	int		i;
	char	**env;
	char	**my_paths;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	char	*input_file;
	char	*output_file;
	int		cmd_count;
	char	**cmds_all;
	char	**cmd;
	char	*cmd_path;
	int		exit_code;
	char	*limiter;
}	t_vars;

/* ************************************************************************ */
/*								PROTOYPES									*/
/* ************************************************************************ */

/* input_bonus.c */
int		check_envp(char **envp);
int		check_cmd(t_vars *vars);
int		get_input(t_vars *vars, char **argv, char **envp, int h);

/* utils_bonus.c */
int		init(t_vars *vars);
int		destroy_mem(t_vars *vars);
void	exit_on_error(t_vars *vars);

/* utils2_bonus.c */
void	open_files(t_vars *vars, int h);
void	swap_fd(t_vars *vars, int h);
void	stdin_to_pipe(t_vars *vars);

/* pipex_bonus.c */
int		pipex(t_vars *vars, int h);
void	last_call(t_vars *vars);

#endif
