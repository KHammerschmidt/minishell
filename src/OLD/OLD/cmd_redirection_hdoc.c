/* Counts the number of simple infile redirections and here_doc. */
// static int	ft_count_hdoc(char **string)
// {
// 	int	i;
// 	int	cnt_hdoc;

// 	i = 0;
// 	cnt_hdoc = 0;
// 	while ((*string)[i] != '\0')
// 	{
// 		if ((*string)[i] == '<')
// 		{
// 			if ((*string)[i + 1] == '<')
// 				cnt_hdoc++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	return (cnt_hdoc);
// }

// /* Allocates memory space for the struct t_here_doc and the int array input_op. */
// int	mem_alloc_hdoc(t_vars *ms, char **string)
// {
// 	int	cnt_hdoc;
// 	int	j;

// 	j = 0;
// 	cnt_hdoc = ft_count_hdoc(string);
// 	if (cnt_hdoc == 0)
// 		ms->info->here_doc = NULL;
// 	else
// 	{
// 		ms->info->here_doc = (t_here_doc **)ft_calloc(sizeof(t_here_doc *), cnt_hdoc);
// 		if (!(ms->info->here_doc))
// 		{
// 			printf("Mem allocation error here_doc\n");
// 			// ft_free_hdoc();		funktion bauen!
// 			return (1);
// 		}
// 		while (j < cnt_hdoc)
// 		{
// 			ms->info->here_doc[j] = ft_calloc(1, sizeof(t_here_doc));
// 			if (!(ms->info->here_doc))
// 			{
// 				printf("Mem allocation error here_doc\n");
// 				// ft_free_hdoc();		funktion bauen!
// 				return (1);
// 			}
// 			j++;
// 		}
// 	}
// 	return (0);
// }