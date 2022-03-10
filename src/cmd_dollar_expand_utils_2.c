#include "../header/minishell.h"

void	no_envar_found(t_vars *ms, char *var)
{
	if (ms->line == NULL)
	{
		ms->line = ft_strdup("$");
		ms->line = ft_strjoin(ms->line, var);
	}
	else
	{
		ms->line = ft_strjoin(ms->line, "$");
		ms->line = ft_strjoin(ms->line, var);
	}
}
