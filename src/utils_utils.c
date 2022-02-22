#include "../header/minishell.h"

void	print_lst_last(t_vars *ms)
{
	t_cmd	*temp;
	int		len;

	len = ft_lstsize_cmd(ms->cmd);
	temp = NULL;
	temp = ft_lstlast_cmd(ms->cmd);
	if (len <= 1)
	{
		printf("input_op: %d   output_op: %d\n",
			temp->input_op, temp->output_op);
		return ;
	}
	while (temp->previous != NULL && len >= 1)
	{
		printf("input_op: %d   output_op: %d\n",
			temp->input_op, temp->output_op);
		temp = temp->previous;
	}
	if (temp->previous == NULL)
		printf("input_op: %d    output_op: %d\n",
			temp->input_op, temp->output_op);
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
		printf("infile: %s outfile: %s\n", current->infile, current->outfile);
		current = current->next;
	}
}

// void	free_cmd_struct(t_vars *ms)
// {
// 	t_cmd	*current;
// 	t_cmd	*tmp;

// 	current = ms->cmd;
// 	while (current != NULL)
// 	{
// 		tmp = current;
// 		current = current->next;
// 		ft_free_strarray(tmp->command);
// 		ft_free_string(&tmp->execpath);
// 		ft_free_string(&tmp->infile);
// 		ft_free_string(&tmp->outfile);
// 		ft_free_string(&tmp->error_msg);
// 		// free(tmp);							// Mio: deleted to get rid of "invalid read" / "invalid write" (VALGRIND)
// 		// tmp = NULL;
// 	}
// 	free(current);
// 	current = NULL;
// }

void	free_cmd_struct(t_vars *ms)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = ms->cmd;
	tmp = current;
	while (tmp != NULL)
	{
		ft_free_strarray(current->command);
		ft_free_string(&current->execpath);
		ft_free_string(&current->infile);
		ft_free_string(&current->outfile);
		ft_free_string(&current->error_msg);
		tmp = current->next;
		free(current);							// Mio: deleted to get rid of "invalid read" / "invalid write" (VALGRIND)
		current = NULL;							// Wirklich auf NULL setzen?!
		current = tmp;
	}
}
