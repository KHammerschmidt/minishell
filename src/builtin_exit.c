#include "../header/minishell.h"

int	validate_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	builtin_exit(t_vars *ms)
{
	int	e_code;

	e_code = 0;
	ft_putendl_fd("exit", 2);
	if (ms->cmd->command[1] != NULL && ms->cmd->command[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		e_code = 1;
	}
	if (ms->cmd->command[1] != NULL && validate_arg(ms->cmd->command[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ms->cmd->command[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		e_code = 255;
	}
	if (ms->cmd->command[1] != NULL && validate_arg(ms->cmd->command[1]) == 0)
		e_code = ft_atoi(ms->cmd->command[1]);
	rl_clear_history();
	free_and_exit(ms, 1, e_code);
	return (e_code);
}