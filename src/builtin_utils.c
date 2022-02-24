#include "../header/minishell.h"

/* Auxiliary function for builtin_cd(). */
void	create_old_pwd(t_vars *ms, int flag, char *start_wd)
{
	t_env	*new;
	char	*tmp;

	tmp = NULL;
	new = NULL;
	if (flag == 0)
	{
		tmp = ft_strdup("OLDPWD=");
		tmp = ft_strjoin(tmp, start_wd);
		new = ft_lstnew_env(tmp);
		ft_lstadd_back_env(&ms->env, new);
		free(tmp);
		tmp = NULL;
	}
}