#include "../header/minishell.h"

/* Looks for current user in envar list and returns it if found. */
char	*get_user(t_vars *ms)
{
	char	*user;

	user = NULL;
	if (get_env_var(ms, "USER") && get_env_var(ms, "USER")->content)
		user = ft_strdup(get_env_var(ms, "USER")->content);
	return (user);
}

/* Looks for current working directory in envar list and returns it if found. */
char	*get_pwd(t_vars *ms)
{
	char	*pwd;

	pwd = NULL;
	if (get_env_var(ms, "PWD") && get_env_var(ms, "PWD")->content && ft_strchr(get_env_var(ms, "PWD")->content, '/'))
	{
		pwd = ft_strdup(ft_strrchr(get_env_var(ms, "PWD")->content, '/') + 1);
	}
	return (pwd);
}

/* Tries to concatenate user and current working directory to create a prompt */
/* to be used with readline().                                                */
char	*create_prompt(t_vars *ms)
{
	char	*prompt;
	char	*user;
	char	*pwd;

	prompt = NULL;
	user = get_user(ms);
	pwd = get_pwd(ms);
	if (user && pwd)
	{
		prompt = ft_calloc(ft_strlen(user) + ft_strlen(pwd) + 6, sizeof(char));
		if (prompt)
		{
			ft_strlcat(prompt, user, ft_strlen(user) + 1);
			ft_strlcat(prompt, "@", ft_strlen(prompt) + 2);
			ft_strlcat(prompt, pwd, ft_strlen(prompt) + ft_strlen(pwd) + 2);
			ft_strlcat(prompt, " ॐ  ", ft_strlen(prompt) + ft_strlen(pwd) + 6);
		}
	}
	if (user)
		free(user);
	if (pwd)
		free(pwd);
	return (prompt);
}
