#include "../header/minishell.h"

int	quote_infos(t_vars *ms, char *str)
{
	if (ms->info->single_quote_counter == 0 && ms->info->double_quote_counter != 0)			//only double quotes in string
	{
		ms->info->double_quote_counter = 1;
		printf("ONLY DOUBLE QUOTES\n");
		return (1);
	}
	else if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter != 0)	//only single quotes in string
	{
		ms->info->single_quote_counter = 1;
		printf("ONLY SINGLE QUOTES\n");
		return (1);
	}
	if (ft_strchr_pos(str, 34) < ft_strchr_pos(str, 39))	//pos double quotes < pos single quotes, double quotes are surrounding
	{
		ms->info->double_quote_counter = 1;					// double quotes are activated (can be trimmed afterwards)
		ms->info->single_quote_counter = 0;					//single quotes are deactivated
		printf("double quotes are outer quotes!\n");
	}
	else if (ft_strchr_pos(str, 34) > ft_strchr_pos(str, 39))	//pos single quotes < pos double quotes, single quotes are surrounding
	{
		ms->info->single_quote_counter = 1;					//single quotes activated (can be trimmed afterwards)
		ms->info->double_quote_counter = 0;					//double quotes deactivated
		printf("single quotes are outer quotes!\n");
	}
	printf("HERE 2\n");
	return (1);
}

int	check_quote_validity(char *str, t_vars *ms)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)						//double_quotes
			ms->info->double_quote_counter++;
		if (str[i] == 39)						//single quotes
			ms->info->single_quote_counter++;
		if (ms->info->double_quote_counter != 0 && str[i] == '$')			//valid quotes and $ sign in there
			ms->info->dollar++;
		i++;
	}
	printf("double:[%d]   single[%d]\n", ms->info->double_quote_counter, ms->info->single_quote_counter);
	if (ms->info->double_quote_counter == 0 && ms->info->single_quote_counter == 0)						//no quotes
	{
		printf("no quotes!\n");
		return (0);
	}
	if ((ms->info->double_quote_counter % 2) != 0 || (ms->info->single_quote_counter % 2) != 0)			//open quotes
	{
		printf("open quotes!\n");
		return (-1);
	}
	return (quote_infos(ms, str));
}

