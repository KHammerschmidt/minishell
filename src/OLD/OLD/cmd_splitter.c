#include "../header/minishell.h"

void	ft_free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL && arr)			//NULL or '\0'
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

// void	reset_info_struct(t_info *info)
// {
// 	info->command = NULL;
// 	info->outfile = NULL;
// 	info->infile = NULL;
// 	info->input_op = 0;
// 	info->output_op = 0;
// 	info->pipe = 0;
// }



// ------------------------------------------------------------------------------------------------------------------------------
// char    *copy_str_without_quotes(char *str)             //INFO: $sign has to work
// {
//     char    *tmp;
//     char    *argument;

//     tmp = "\"\\";
//     argument = ft_strtrim(str, tmp);                    //if no command -> access wirft command not found aus!
//     return (argument);
// }

// void fill_operators(char *str, t_cmd *element)
// {
//  int op;
//  int i;

//  i =0 ;
//  op = 0;
//  while (str[i] != '\0')                  //what happens when there are more redirections?
//  {
//      if (ft_strnstr(str, "<", ft_strlen(str)) != 0)
//          element->op = LESS;
//      if (ft_strnstr(str, "<<", ft_strlen(str)) != 0)
//          element->op = LESSLESS;
//      if (ft_strnstr(str, ">", ft_strlen(str)) != 0)
//          element->op = GREATER;
//      if (ft_strnstr(str, ">>", ft_strlen(str)) != 0)
//          element->op = GREATERGREATER;
//      i++;
//  }
// }
