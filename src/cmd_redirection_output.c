/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirection_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:16:13 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:14 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	outfile_permission_denied(t_vars *ms)
{
	ft_putstr_fd("Error: permission denied: ", 2);
	ft_putendl_fd((ms->info.outfile), 2);
	ms->exit_status = 1;
	ms->info.fd_out = STDOUT_FILENO;
	ms->info.flag = -1;
}

int	outfile_fd(t_vars *ms)
{
	if (ms->info.fd_out != STDOUT_FILENO)
	{
		close(ms->info.fd_out);
		ms->info.fd_out = STDOUT_FILENO;
	}
	if (ms->info.output_op == -1)
	{
		ms->info.fd_out = open(ms->info.outfile,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (ms->info.output_op == -2)
	{
		if (ms->info.fd_out != STDOUT_FILENO)
			close(ms->info.fd_out);
		ms->info.fd_out = open(ms->info.outfile,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else if (ms->info.fd_out == -1 || access(ms->info.outfile, W_OK) != 0)
	{
		outfile_permission_denied(ms);
		return (1);
	}
	return (0);
}

/* Cuts out the redirections associated with the outfile from the cmd_line. */
void	cut_outfile_red(char **string, int fd_out)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < fd_out)
	{
		tmp = ft_strnjoin(tmp, (*string)[i], 1);
		i++;
	}
	while ((*string)[i] == '>')
		i++;
	while ((*string)[i] == ' ')
		i++;
	while ((*string)[i] != ' ' && (*string)[i] != '>' && (*string)[i] != '\0')
		i++;
	while ((*string)[i] != '\0')
		tmp = ft_strnjoin(tmp, (*string)[i++], 1);
	ft_free_string(string);
	*string = ft_strdup(tmp);
	ft_free_string(&tmp);
}

/* Saves the outfile in the t_info struct. */
void	expansion_outfile_red(char **string, t_vars *ms, int j)
{
	int		k;
	char	*tmp;

	k = 0;
	while (((*string)[j] == '>' || (*string)[j] == ' ') && (*string)[j] != '\0')
		j++;
	k = j;
	while ((*string)[k] != ' ' && (*string)[k] != '>' && (*string)[k] != '\0')
		k++;
	tmp = ft_substr((*string), j, k - j);
	ft_free_string(&ms->info.outfile);
	ms->info.outfile = tmp;
}

int	output_redirection(t_vars *ms, char **string, int red_out)
{
	while (red_out != -1)
	{
		if ((*string)[red_out] == '>' && valid_red(*string, red_out) == 0)
		{
			if ((*string)[red_out + 1] == '>')
				ms->info.output_op = -2;
			else
				ms->info.output_op = -1;
		}
		else
		{
			red_out = ft_strchr_pos_red(*string, '>', red_out + 2);
			continue ;
		}
		expansion_outfile_red(string, ms, red_out);
		cut_outfile_red(string, red_out);
		if (outfile_fd(ms) == 1)
			return (1);
		red_out = ft_strchr_pos(&(*string)[red_out], '>');
	}
	return (0);
}
