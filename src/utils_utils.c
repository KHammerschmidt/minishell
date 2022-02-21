#include "../header/minishell.h"

void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		lst = &(*lst)->next;
		free(tmp);
		tmp = *lst;
	}
}

int	ft_strchr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	else
		return (-1);
}

void	ft_free_string(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	print_lst_last(t_vars *ms)
{
	t_cmd *temp;
	int		len;
	// int		i;

	// i = 0;
	len = ft_lstsize_cmd(ms->cmd);
	temp = NULL;
	temp = ft_lstlast_cmd(ms->cmd);
	if (len <= 1)
	{
		printf("input_op: %d   output_op: %d\n", temp->input_op, temp->output_op);
		return ;
	}
	while (temp->previous != NULL && len >= 1)
	{
		printf("input_op: %d   output_op: %d\n", temp->input_op, temp->output_op);
		temp = temp->previous;
	}
	if (temp->previous == NULL)
		printf("input_op: %d    output_op: %d\n", temp->input_op, temp->output_op);
}

void	print_lst(t_vars *ms)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = NULL;
	current = ms->cmd;
	while (current && current->command != NULL)
	{
		i = 0;
		while (current->command[i] != NULL)
		{
			printf("command...%s... ", current->command[i]);
			i++;
		}
		printf("pipe: %d     infile: %s      outfile: %s\n", current->pipe, current->infile, current->outfile);
		current = current->next;
	}
}

void	free_cmd_struct(t_vars *ms)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = ms->cmd;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_free_strarray(tmp->command);
		ft_free_string(&tmp->execpath);
		ft_free_string(&tmp->infile);
		ft_free_string(&tmp->outfile);
		ft_free_string(&tmp->error_msg);
		// free(tmp);							// Mio: deleted to get rid of "invalid read" / "invalid write" (VALGRIND)
		// tmp = NULL;
	}
	free(current);
	current = NULL;
}

void	reset_info_struct(t_info *info)		// muss hier nicht vorher gefreed werden?
{
	
	ft_free_strarray(info->command);
	ft_free_string(&info->outfile);
	ft_free_string(&info->infile);
	info->input_op = 0;
	info->output_op = 0;
	info->pipe = 0;
}



// void	ft_free_lst(t_list **lst)
// {
// 	t_list	*tmp;

// 	tmp = *lst;
// 	while (tmp)
// 	{
// 		lst = &(*lst)->next;
// 		free(tmp);
// 		tmp = *lst;
// 	}
// }

// int	ft_strchr_pos(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return (-1);
// 	while (s[i] != (unsigned char)c && s[i] != '\0')
// 		i++;
// 	if (s[i] == (unsigned char)c)
// 		return (i);
// 	else
// 		return (-1);
// }

// void	ft_free_string(char *str)
// {
// 	if (str)
// 		free(str);
// 	str = NULL;
// }

// // void	print_lst_last(t_vars *ms)
// // {
// // 	t_cmd *temp;
// // 	// int		len;
// // 	int		i;

// // 	i = 0;
// // 	// len = ft_lstsize_cmd(ms->cmd);
// // 	temp = NULL;
// // 	temp = ms->cmd;
// 	// temp = ft_lstlast_cmd(ms->cmd);
// 	// if (len <= 1)
// 	// {
// 	// 	printf("input_op: %d   output_op: %d\n", temp->input_op, temp->output_op);
// 	// 	return ;
// 	// }
// 	// while (temp->previous != NULL && len >= 1)
// 	// {
// 	// 	printf("input_op: %d   output_op: %d\n", temp->input_op, temp->output_op);
// 	// 	temp = temp->previous;
// 	// }
// 	// if (temp->previous == NULL)
// 	// 	printf("input_op: %d    output_op: %d\n", temp->input_op, temp->output_op);

// // 	while (temp != NULL)
// // 	{
// // 		printf("input_op: ");
// // 		while (temp->input_op[i])
// // 		{
// // 			printf("  %d   ", (int)temp->input_op[i]);
// // 			i++;
// // 		}
// // 		printf("\n");
// // 		temp = temp->next;
// // 	}
// // }

// // void	print_lst(t_vars *ms)
// // {
// // 	t_cmd	*current;
// // 	int		i;

// // 	i = 0;
// // 	current = NULL;
// // 	current = ms->cmd;
// // 	while (current && current->command != NULL)
// // 	{
// // 		i = 0;
// // 		while (current->command[i] != NULL)
// // 		{
// // 			printf("command...%s... ", current->command[i]);
// // 			i++;
// // 		}
// // 		printf("pipe: %d     infile: %s      outfile: %s\n", current->pipe, current->infile, current->outfile);
// // 		current = current->next;
// // 	}
// // }

// void	free_cmd_struct(t_vars *ms)
// {
// 	t_cmd	*current;

// 	current = NULL;
// 	while (current != NULL)								// Mio: Delete command table after each execution.
// 	{
// 		ft_free_strarray(current->command);				// Mio: Replace by function to empty and free the complete list
// 		current = current->next;
// 	}
// 	ms->cmd = NULL;										// Mio: Leaks?!
// }