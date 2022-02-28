#include "../header/minishell.h"

static long double	ft_atoll(char *arg)
{
	long long	i;
	long long	sign_flag;
	long double	n;

	n = 0;
	i = 0;
	sign_flag = 1;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-')
	{
		sign_flag = -1;
		i++;
	}
	else if (arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]))
	{
		n = (n * 10) + (arg[i] - 48);
		i++;
	}
	return (n * sign_flag);
}

static int	validate_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_atoll(arg) > 9223372036854775807 \
		|| ft_atoll(arg) < -9223372036854775807)
		return (1);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '-' && arg[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

static void	exit_aux(t_cmd *current, int *e_code)
{
	if (ft_atoi(current->command[1]) < 0)
		*e_code = 256 + ft_atoi(current->command[1]);
	else
		*e_code = ft_atoi(current->command[1]);
}

int	builtin_exit(t_vars *ms, t_cmd *current)
{
	int	e_code;

	e_code = 0;
	ft_putendl_fd("exit", 2);
	if (current->command[1] != NULL && current->command[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (current->command[1] != NULL && validate_arg(current->command[1]) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", \
			current->command[1]);
		e_code = 255;
	}
	if (current->command[1] != NULL && validate_arg(current->command[1]) == 0 \
			&& current->command[2] == NULL)
		exit_aux(current, &e_code);
	rl_clear_history();
	last_free(ms, 0);
	exit(e_code);
}
