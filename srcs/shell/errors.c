#include "minishell.h"
#include <stdio.h>

int	throw_error(char *err, int errcode)
{
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errcode), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_g.ret = errcode;
	return (0);
}
