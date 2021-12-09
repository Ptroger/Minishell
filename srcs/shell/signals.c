#include "../includes/minishell.h"

void	sig_c(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_parent(int sig)
{
	if (kill(g_g.pid, sig) == 0)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			g_g.ret = 130;
		}
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3 Core dumped\n", STDERR_FILENO);
			g_g.ret = 131;
		}
	}
	else if (sig == SIGINT)
	{
		g_g.ret = 1;
		sig_c();
	}
}

void	sig_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_g.pid != 0)
		handle_parent(sig);
	else
	{
		if (sig == SIGINT)
		{
			sig_c();
			g_g.ret = 1;
		}
		else if (sig == SIGQUIT)
			ft_putstr_fd("\b\b \b\b", 1);
	}
}
