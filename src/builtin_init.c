/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:15:14 by khammers          #+#    #+#             */
/*   Updated: 2022/03/12 20:15:15 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Creates a new node for every builtin and adds it to the end of t_list. */
static int	add_builtin(t_vars *ms, char *builtin)
{
	t_list	*element;

	element = ft_lstnew(builtin);
	if (element == NULL)
	{
		printf("Error\n");
		free_builtin_list(ms);
		return (1);
	}
	ft_lstadd_back(&ms->builtins, element);
	return (0);
}

/* Intialises the specified builtins. */
int	init_builtin(t_vars *ms)
{
	if ((add_builtin(ms, "echo") != 0)
		|| (add_builtin(ms, "cd") != 0)
		|| (add_builtin(ms, "pwd") != 0)
		|| (add_builtin(ms, "export") != 0)
		|| (add_builtin(ms, "unset") != 0)
		|| (add_builtin(ms, "env") != 0)
		|| (add_builtin(ms, "exit") != 0))
		return (1);
	return (0);
}
