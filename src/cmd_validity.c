#include "../header/minishell.h"

// void	num_quotes(char *str, t_ms *ms, int quote_type)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (quote_type == 0 && str[i] == 34)		//""
// 			ms->input->doublequote_counter++;
// 		if (quote_type == 1 && str[i] == 39)		//''
// 			ms->input->singlequote_counter++;
// 		i++;
// 	}
// }

// int		input_double_quotes(char *str, int i, t_ms *ms)
// {
// 	int		k;
// 	int		j;

// 	k = i;
// 	j = 0;
// 	while (str[k] != '\0' && k < ft_strchr_pos(str, 34))		//solange kein anders Anführungszeichen gefunden wird
// 	{
// 		num_quotes(str, ms);									//Anzahl an " (set ms->doublequote_counter);
// 		if ((ms->doublequote_counter % 2) != 0)					//check if open or closed " "	//error msg?
// 		{
// 			printf("ERROR: OPEN QUOTES\n");
// 			return (-1);
// 		}
// 		ms->quoting = DOUBLE_QUOTES;
// 		ms->special_char++;
// 		if (ft_strchr(str, '$') != NULL)						//$ in " " has no meaning
// 		{
// 			j = k + 1;						//eine pos weiter als $
// 			if (ft_isprintf(str[j]) == 1)	//nach dem dollar sign kommt noch etaws, also wird		< 33 nicht 32
// 			{
// 				while (str[j] != " ")
// 				{
// 					//ignore this part of the string
// 					//echo "hallo hier $bin ich" ---> printet "hallo hier  ich"
// 				}
// 				ms->dollar++;				//
// 			}
// 		}
// 		k++;
// 	}
// 	return (0);
// }

// int quoting(char *str, t_ms *ms)				//find out what does each character mean :)
// {
// 	int		i;
// 	int		counter;

// 	i = 0;
// 	counter = 0;
// 	while (str && str[i] != '\0')
// 	{
// 		if(ft_strchr(str, 34) != NULL)				//"
// 		{
// 			// input_double_quotes(str, i, ms) != NULL);
// 			num_quotes(str, ms, 0);
// 		}
// 		if (ft_strchr(str, 39) != NULL)				// '
// 		{
// 			// input_single_quotes(str, i ms) != NULL);
// 			num_quotes(str, ms, 1);

// 		}
// 		else
// 			i++;
// 	}
// 	return (i);
// }

int	ft_strrchr_pos(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (c == '\0')
		return (i + 1);
	while (i > 0)
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i--;
	}
	if (s[0] == (unsigned char)c)
		return (i);
	return (-1);
}

int	cmd_validity(char *str)			// check if string consists of only quotes, or some quotes, or open quotes
{
	// char	**arr;

	// arr = NULL;
	// quoting(str, ms);
	// num_quotes(str, ms);
	if (ft_strchr_pos(str, 34) == -1)				// no quotes
		return (0);
	if (str[0] == 34 && str[1] == 34)
		return (-1);
	printf("%d   | %d   | %zu\n", ft_strchr_pos(str, 34), ft_strrchr_pos(str, 34), ft_strlen(str));

	if (ft_strchr_pos(str, 34) == 0 && ft_strrchr_pos(str, 34) + 1 == (int)ft_strlen(str)	//only quotes at beginning & end
		&& ft_strchr_pos(str, 34) != ft_strrchr_pos(str, 34))
		return (1);

	// if (ft_strchr_pos(str, 34) != NULL)				//there are quotes
	// {
	// 	arr = ft_split(str, 34);					//is whole cmd a quote?

	// }
	// if ((ms->input->double_quote_counter % 2) != 0)		//open quotes
	// 	return (1);
	return (-1);
}
