#include "../header/minishell.h"

char	**ft_split_quotes(char *str, t_vars *ms)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**split;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	// if (ms->info->dollar != 0)
	// 		check_dollar_sign(str, ms);					//is there a dollar sign outside the quotes
	split = ft_calloc(1, sizeof(*(split)));
	if (!split)
		printf("MEM ALLOC ERROR\n");
	temp = NULL;
	if (ms->info->double_quote_counter == 1)
		quote = 34;									//double quotes are the outer quotes or are the only quotes
	else if (ms->info->single_quote_counter == 1)
		quote = 39;									//single quotes are the dominant one

	while (str[i] != '\0')
	{
		while (str[i] != quote)						//while no quote has been found we split by spaces
		{
			if (str[i] == ' ')						//iterate until space is found (create substring & save in char **)
			{
				temp = ft_substr(str, j, i);
				split[k] = temp;
				printf("split[%d]: ..%s..\n", k, split[k]);
				free(temp);
				j = j + i + 1;
				i--;
			}
			i++;
		}
		if (str[i] == quote)					//quote has been found, we leave the quotes part in one string
		{
			temp = ft_substr(str, j, i);
			split[k] = temp;
			printf("split[%d]: ..%s..\n", k, split[k]);
			k++;
			free(temp);
			j = j + i + 1;
		}
	i++;
	}
	return (split);
}
