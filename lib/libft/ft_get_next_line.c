/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortmeie <mortmeie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:09:49 by mortmeie          #+#    #+#             */
/*   Updated: 2021/11/22 17:38:15 by mortmeie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_tmp(char **tmp)
{
	free(*tmp);
	*tmp = NULL;
	return (NULL);
}

static char	*get_new_line(char *tmp)
{
	char	*new_line;
	int		c;

	c = 0;
	while (tmp[c] != '\n' && tmp[c] != '\0')
		c++;
	new_line = malloc(c + 1);
	if (!new_line)
		return (NULL);
	c = 0;
	while (tmp[c] != '\n' && tmp[c] != '\0')
	{
		new_line[c] = tmp[c];
		c++;
	}
	new_line[c] = '\0';
	return (new_line);
}

static char	*modify_tmp(char *tmp, int len)
{
	char	*new_tmp;
	int		i;

	i = 0;
	new_tmp = malloc(ft_strlen(&tmp[len + 1]) + 1);
	if (!new_tmp)
		return (NULL);
	while (tmp[len + 1] != '\0')
	{
		new_tmp[i] = tmp[len + 1];
		i++;
		len++;
	}
	new_tmp[i] = '\0';
	free(tmp);
	return (new_tmp);
}

static char	*output(char *line)
{
	static char	*tmp;
	char		*result;

	if (!tmp)
		tmp = ft_calloc(1, 1);
	if (!tmp)
		return (NULL);
	if (ft_strlen(line) > 0)
		tmp = ft_strjoin(tmp, line);
	free(line);
	if (ft_strlen(tmp) == 0)
		return (free_tmp(&tmp));
	result = get_new_line(tmp);
	if (tmp[ft_strlen(result)] == '\n')
	{
		tmp = modify_tmp(tmp, ft_strlen(result));
		return (ft_strjoin(result, "\n"));
	}
	else
	{
		free(tmp);
		tmp = NULL;
		return (result);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	int			buf_count;

	buf = malloc(1 + 1);
	line = ft_calloc(1, 1);
	if (1 <= 0 || !buf || !line)
		return (NULL);
	buf_count = read(fd, buf, 1);
	while (buf_count > 0)
	{
		buf[buf_count] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			line = ft_strjoin(line, buf);
			break ;
		}
		else
		{
			line = ft_strjoin(line, buf);
			buf_count = read(fd, buf, 1);
		}
	}
	free(buf);
	return (output(line));
}
