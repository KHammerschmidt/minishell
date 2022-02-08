/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:56:28 by khammers          #+#    #+#             */
/*   Updated: 2022/02/05 14:29:22 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 1

typedef struct s_struct
{
	int		argc;
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	char	**execpath;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	int		exit_status;
	int		cmd_nbr;
	int		tmp_fd;
	int		flag;
}				t_struct;

int		main(int argc, char *argv[], char *envp[]);
void	ft_initialise(t_struct *data, int argc, char *argv[], char *envp[]);
void	ft_error(t_struct *data, int msg);
void	ft_get_exec_path(char *envp[], t_struct *data);
void	ft_free_arr(char **arr);
int		ft_pipex(t_struct *data);
int		ft_here_doc(t_struct *data);
int		ft_strncmp_pipex(const char *s1, const char *s2, size_t n);

#endif