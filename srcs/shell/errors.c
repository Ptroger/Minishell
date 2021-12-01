#include "minishell.h"
#include <stdio.h>

void	throw_error(t_vars *vars, char *err, int errcode)
{
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errcode), STDERR_FILENO);
	destroy_vars(vars);
	exit(errcode);
}
