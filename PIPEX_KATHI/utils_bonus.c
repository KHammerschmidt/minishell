/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:00:30 by khammers          #+#    #+#             */
/*   Updated: 2022/02/05 14:29:11 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
** Prototype: int	ft_strncmp(const char *s1, const char *s2, size_t n);
**
** The function ft_strncmp() compares lexicographically the null-terminated
** strings s1 and s2 but not more than n characters. Characters that appear
** after null-terminator are not compared. The function returns an integer
** greater than, equal to or less than 0, according as s1 is greater than,
** equal to or less than string 2. Comparison is done using unsigned
** characters.
** (1) if n=0 return 0;
** (2) loop through the strings while they are equal;
** (3) if the next iteration (i+1==n) is equal to n, the loop is stopped (as i
** n characters are compared then);
** (4) if (i+1='\0') the difference between the next position in the string
** is returned (as otherwise the function jumps out of the while loop too
** early);
** (5) the difference between the strings i returned;
*/
int	ft_strncmp_pipex(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (s1[i] == s2[i])
	{
		if (s1[i + 1] == '\0' && s2[i + 1] == '\0')
			return ((unsigned char)s1[i + 1] - (unsigned char)s2[i + 1]);
		if ((i + 1) == n)
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


/* Function frees an array. */
void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr != NULL)
	{
		free(arr);
		arr = NULL;
	}
}

/* The command's executable path is being searched in the environment
variable and then the string splitted using ft_split(). Afterwards
a '/' is appended to append the cmd later. */
void	ft_get_exec_path(char *envp[], t_struct *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[j] != NULL)
	{
		if (ft_strnstr(envp[j], "PATH=", 5) != 0)
			break ;
		j++;
	}
	data->execpath = ft_split(&envp[j][5], ':');
	while (data->execpath[i])
	{
		tmp = ft_strjoin(data->execpath[i], "/");
		free(data->execpath[i]);
		data->execpath[i] = tmp;
		i++;
	}
}

/* Function initialises the struct's variables. */
void	ft_initialise(t_struct *data, int argc, char *argv[], char *envp[])
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->pipe_fd[0] = 0;
	data->pipe_fd[1] = 0;
	data->pid1 = 0;
	data->pid2 = 0;
	data->execpath = NULL;
	data->infile = 0;
	data->outfile = 0;
	data->exit_status = 0;
	data->cmd_nbr = 2 ;
	data->tmp_fd = 0;
	data->flag = 0;
}

/* In case pipe or process IDs could not be estalished this function prints the
according error message to STDERR. */
void	ft_error(t_struct *data, int msg)
{
	if (msg == 1)
	{
		perror("No pipe could be established");
		exit(1);
	}
	if (msg == 2)
	{
		perror("No process ID was established\n");
		ft_free_arr(data->execpath);
		exit(1);
	}
}
