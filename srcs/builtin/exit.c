#include "minishell.h"

int	get_args(t_list *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}	
	return (i);
}

int	is_ok(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
		i++;
	if (!token[i])
		return (FALSE);
	while (token[i])
	{
		if (ft_isdigit(token[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	many_args(void)
{
	throw_error("exit: too many arguments", 2);
	g_g.ret = 1;
}

void	ft_exit(t_vars *vars, t_list *tokens)
{
	int				count;
	long long int	code;

	count = get_args(tokens);
	code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (tokens->next && tokens->next->token)
	{
		if (is_ok(tokens->next->token) == -1)
		{
			throw_error("exit: numeric argument required", 2);
			clean_exit(vars, 2);
		}
	}
	else if (count > 1)
		many_args();
	else if (count == 0)
	{
		code = ft_atoi(tokens->next->token);
		code = code % 256;
		clean_exit(vars, code);
	}
	exit(0);
}
