/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:59:43 by khammers          #+#    #+#             */
/*   Updated: 2021/11/18 12:05:06 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* Main function checks if number of arguments is correct and if environment
variable can be accessed. If so, the struct is initialised. The number of the
first command is set by testing if either a here_doc should be opened or the
usual ft_pipex() function called. */
int	main(int argc, char *argv[], char *envp[])
{
	t_struct	data;

	if (argc < 5)
	{
		ft_putstr_fd("Error: ./pipex file1 cmd1 cmd2 ... file2\n", 1);
		exit(1);
	}
	if (!envp)
	{
		ft_putstr_fd("No environment variable found\n", 1);
		exit(1);
	}
	ft_initialise(&data, argc, argv, envp);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		data.cmd_nbr = 3;
		return (ft_here_doc(&data));
	}
	data.cmd_nbr = 2;
	return (ft_pipex(&data));
}
