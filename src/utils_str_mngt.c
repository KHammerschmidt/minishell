#include "../header/minishell.h"

/* Copies the content of a char array into another, with  mem allocation. */
char	**copy_strarray(char **strarray)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	if (strarray == NULL)
		return (NULL);
	while (strarray[i] != NULL)
		i++;
	ret = (char **)malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (strarray[i] != NULL)
	{
		ret[i] = ft_strdup(strarray[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/* Returns the position of character in a string or -1 if not found. */
int	ft_strchr_pos(const char *s, char c)
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

/* Compares two strings and returns 0 if they are exactly the same, */
/* else returns 1.                                                  */
int	compare_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (s1 && !s2))
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

/* Like ft_strjoin() but only appends one character at a time. */
char	*ft_strjoin_2(char *line, char *str, int i)
{
	char	*tmp;

	tmp = ft_strdup(&str[i]);
	tmp[1] = '\0';
	line = ft_strjoin(line, tmp);
	ft_free_string(&tmp);
	return (line);
}

/* Counts amount of substrings by counting spaces except for when there are
quotes, then it counts the part in quotes as one substring. */
int	ft_count_substrings(char *str)
{
	int	i;
	int	counter;
	int	quote_on;
	int	quote;

	i = 0;
	quote = 0;
	counter = 0;
	quote_on = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == 34 && quote_on == 0) || (str[i] == 39 && quote_on == 0))
			quote = str[i];
		if (str[i] == ' ' && quote_on == 0)
			counter++;
		if (str[i] == quote)
			quote_on++;
		if (quote_on == 2)
			quote_on = 0;
		i++;
	}
	return (counter + 1);
}
