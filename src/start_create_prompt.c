#include "../header/minishell.h"

/* Looks for current user in envar list and returns the content of it, 
e.g. the user name. */
// char	*get_user(t_vars *ms)//mio
// {
// 	char	*user;

// 	user = NULL;
// 	if (get_env_var(ms, "USER") && get_env_var(ms, "USER")->content)
// 		user = ft_strdup(get_env_var(ms, "USER")->content);
// 	return (user);
// }

/* Looks for current working directory in envar list and returns it if found. */
// char	*get_pwd(t_vars *ms)//mio
// {
// 	char	*pwd;

// 	pwd = NULL;
// 	if (get_env_var(ms, "PWD") && get_env_var(ms, "PWD")->content && ft_strchr(get_env_var(ms, "PWD")->content, '/'))
// 		pwd = ft_strdup(ft_strrchr(get_env_var(ms, "PWD")->content, '/') + 1);
// 	return (pwd);
// }

/* Searches in t_env for the variable PWD and returns the respective node. If 
the name and content of the list element are not NULL and content contains a 
'/', it saves the last bit of the content after it's '/'. */
char	*get_pwd(t_vars *ms)//kathi
{
	char 	*pwd;
	char	*temp_path;
	t_env	*env_pwd;

	pwd = NULL;
	temp_path = NULL;
	env_pwd = get_env_var(ms, "PWD");
	if (env_pwd != NULL && env_pwd->content != NULL 
		&& ft_strchr(env_pwd->content, '/') != NULL)
	{
		temp_path = ft_strrchr(env_pwd->content, '/') + 1;
		pwd = ft_strdup(temp_path);
	}
	return (pwd);
}

/* Searches in t_env for the variable USER and returns the respective node. If it is
not NULL it saves the user name in char *user and returns it. */
char	*get_user(t_vars *ms)//kathi
{
	char	*user;
	t_env	*env_user;

	user = NULL;
	env_user = get_env_var(ms, "USER");
	if (env_user != NULL && env_user->content != NULL)
		user = ft_strdup(env_user->content);
	return (user);
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
	if (user != NULL && pwd != NULL)
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
		ft_free_string(&user);
	if (pwd)
		ft_free_string(&pwd);
	return (prompt);
}
