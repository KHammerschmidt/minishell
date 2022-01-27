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

void	ft_free_string(char *str)
{
	if (str)
		free(str);
	str = NULL;
}
