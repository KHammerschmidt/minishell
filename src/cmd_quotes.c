#include "../header/minishell.h"

/* Checks the quote status, returns (0) for no quotes, (1) for valid
quotes and (-1) for open quotes. */
int	check_quote_status(char *str)
{
	int	i;
	int	quote_on;
	int	quote_type;

	i = 0;
	quote_on = 0;
	quote_type = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && quote_on == 0)
			quote_type = 34;
		if (str[i] == 39 && quote_on == 0)
			quote_type = 39;
		if (str[i++] == quote_type)
		{
			if (quote_on == 1)
				quote_on = -1;
			quote_on++;
		}
	}
	if (quote_on == 1)
		return (-1);
	if (quote_type == 0)
		return (0);
	return (1);
}

// -------------------------------------------------------------------------------------------------
/* Compares the number of double and single quotes to find out which one are the
active ones, e.g. surrounding the other ones. Thereby the number of both quote types
is compared before the location of the quotes is compared. The unactive quote type is
set to 0 again while the active quote type is set to 1. */
// int	quote_infos(t_vars *ms, char *str)
// {
// 	if (ms->info->single_quote_counter == 0 && ms->info->double_quote_counter != 0)			//only double quotes in string
// 	{
// 		ms->info->double_quote_counter = 1;	// printf("ONLY DOUBLE QUOTES\n");
// 		return (1);
// 	}
// 	else if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter != 0)	//only single quotes in string
// 	{
// 		ms->info->single_quote_counter = 1;	// printf("ONLY SINGLE QUOTES\n");
// 		return (1);
// 	}
// 	if (ft_strchr_pos(str, 34) < ft_strchr_pos(str, 39))	//pos double quotes < pos single quotes, double quotes are surrounding
// 	{
// 		ms->info->double_quote_counter = 1;					// double quotes are activated (can be trimmed afterwards)
// 		ms->info->single_quote_counter = 0;					//single quotes are deactivated
// 	}
// 	else if (ft_strchr_pos(str, 34) > ft_strchr_pos(str, 39))	//pos single quotes < pos double quotes, single quotes are surrounding
// 	{
// 		ms->info->single_quote_counter = 1;					//single quotes activated (can be trimmed afterwards)
// 		ms->info->double_quote_counter = 0;					//double quotes deactivated
// 	}
// 	return (1);
// }

/* Counts the number of quotes in the input string and counts the number of dollar signs.
If there is no even number of the same quote types it means that there are open quotes
and therefore an error should occur. If there are no quotes 0 is returned, otherwise
quote_infos() is called and returned. */
// int	check_quote_validity(char *str, t_vars *ms)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == 34)						//double_quotes
// 			ms->info->double_quote_counter++;
// 		if (str[i] == 39)						//single quotes
// 			ms->info->single_quote_counter++;
// 		if (ms->info->double_quote_counter != 0 && str[i] == '$')			//valid quotes and $ sign in there
// 			ms->info->dollar++;
// 		i++;
// 	}
// 	if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter == 0)					//no quotes
// 		return (0);
// 	if ((ms->info->double_quote_counter % 2) != 0 || (ms->info->single_quote_counter % 2) != 0)		//open quotes
// 		return (-1);
// 	return (quote_infos(ms, str));
// }
