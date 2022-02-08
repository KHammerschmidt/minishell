/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:57:58 by khammers          #+#    #+#             */
/*   Updated: 2021/11/18 14:53:51 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* This function executes the corresponding command in the child process. Cmd
is splitted into the cmd and it's arguments calling ft_split(). It is checked
if the input already is a path, indicated by a '/' in the string, otherwise
the cmd is appended to the path of the command of env. If the command line arg
is a path, it is tested if this path actually exists in the environment
variable. If so the allocated memory is freed and execve called. If not the
error message is printed and the child exited with an error. */
static int	ft_child_execve(t_struct *data)
{
	char	**cmd_line_args;
	char	*cmd;
	char	**tmp;
	int		i;

	i = 0;
	cmd_line_args = ft_split(data->argv[data->cmd_nbr], ' ');
	if (ft_strchr(data->argv[data->cmd_nbr], '/') != NULL)
		execve(data->argv[data->cmd_nbr], cmd_line_args, data->envp);
	else
	{
		while (data->execpath[i])
		{
			cmd = ft_strjoin(data->execpath[i], cmd_line_args[0]);
			if (access(cmd, F_OK) == 0)
				execve(cmd, cmd_line_args, data->envp);
			tmp = &data->execpath[i];
			free(cmd);
			i++;
		}
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd_line_args[0], 2);
	ft_free_arr(cmd_line_args);
	exit(127);
}

/* This function duplicates the STDIN of every child process. First the reading
part of the pipe is closed. If it is the first cmd, the correct permissions are
tested (reading permissions) and it is tested if the file actually exists. Then
the infile is opened and duplicated into STDIN before closing it. It is is not
the first cmd, the tmp_fd is duplicated into STDIN before 0 is returned in
case no error occur. */
static int	ft_handle_stdin(t_struct *data)
{
	close(data->pipe_fd[0]);
	if (data->cmd_nbr == 2)
	{
		if (access(data->argv[1], R_OK) != 0)
		{
			perror("Error");
			ft_free_arr(data->execpath);
			exit(1);
		}
		if (access(data->argv[1], F_OK) != 0)
		{
			ft_putstr_fd("zsh: No such file or directory: ", 2);
			ft_putendl_fd(data->argv[1], 2);
			ft_free_arr(data->execpath);
			exit(1);
		}
		data->infile = open(data->argv[1], O_RDONLY);
		if (dup2(data->infile, STDIN_FILENO) < 0)
			perror("dup2 infile1: ");
		close(data->infile);
		return (0);
	}
	if (dup2(data->tmp_fd, STDIN_FILENO) < 0)
		perror("dup2 infile2: ");
	return (0);
}

/* If here_doc is called, this function duplicates the STDOUT of the cmd. In
case it is not the last command, the writing part of the pipe is duplicated into
STDOUT, otherwise the designated outfile is duplicated into the STDOUT while
checking its writing permission. */
static int	ft_here_doc_out(t_struct *data)
{
	if (data->cmd_nbr != (data->argc - 2))
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2 STDOUT heredoc pipe");
		close(data->pipe_fd[1]);
	}
	else
	{
		close(data->pipe_fd[1]);
		data->outfile = open(data->argv[data->argc - 1],
				O_RDWR | O_CREAT | O_APPEND, 0644);
		if (data->outfile == -1
			|| access(data->argv[data->argc - 1], W_OK) != 0)
		{
			perror("Error");
			ft_free_arr(data->execpath);
			exit(1);
		}
		if (dup2(data->outfile, STDOUT_FILENO) < 0)
			perror("dup2 outfile1: ");
	}
	return (0);
}

/* Function checks if here_doc is called, if so calles specified function.
Otherwise it is checked if the cmd is the last one, then the designated
outfile is duplicated into STDOUT while checking the right permission right.
Otherwise the writing part of the pipe is duplicated into STDOUT. If no
error appears, 0 is returned. */
static int	ft_handle_stdout(t_struct *data)
{
	if (ft_strncmp(data->argv[1], "here_doc", ft_strlen(data->argv[1])) == 0)
		ft_here_doc_out(data);
	else if (data->cmd_nbr == (data->argc - 2))
	{
		close(data->pipe_fd[1]);
		data->outfile = open(data->argv[data->argc - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (data->outfile == -1
			|| access(data->argv[data->argc - 1], W_OK) != 0)
		{
			perror("Error");
			ft_free_arr(data->execpath);
			exit(1);
		}
		if (dup2(data->outfile, STDOUT_FILENO) < 0)
			perror("dup2 outfile1: ");
	}
	else
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
			perror("dup2 outfile2: ");
	}
	return (0);
}

/* Pipe is created, filepath of pipe commands is extracted from env and two
processes forked. The parent waits for the child, closes pipe file descriptors
and frees allocated memory. */
int	ft_pipex(t_struct *data)
{
	while (data->cmd_nbr < (data->argc - 1))
	{
		if (pipe(data->pipe_fd) == -1)
			ft_error(data, 1);
		ft_get_exec_path(data->envp, data);
		data->pid1 = fork();
		if (data->pid1 < 0)
			ft_error(data, 3);
		if (data->pid1 == 0)
		{
			ft_handle_stdin(data);
			ft_handle_stdout(data);
			ft_child_execve(data);
		}
		close(data->pipe_fd[1]);
		close(data->tmp_fd);
		if (dup2(data->pipe_fd[0], data->tmp_fd) < 0)
			perror("dup2 fd[0] into tmp_fd: ");
		close(data->pipe_fd[0]);
		waitpid(data->pid1, &data->exit_status, 0);
		ft_free_arr(data->execpath);
		data->cmd_nbr++;
	}
	close(data->tmp_fd);
	return (WEXITSTATUS(data->exit_status));
}
