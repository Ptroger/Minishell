#include "minishell.h"
#include <stdio.h>

int	throw_error(char *err, int errcode)
{
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errcode), STDERR_FILENO);
	return (0);
}
