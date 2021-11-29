#include "../includes/minishell.h"

void	sig_c(void)
{
	printf("\n");
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
}

void	process(int sig)
{
	if (!kill(g.pid, sig))
	{
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: Core dumped\n", 1);
			g.ret = 131;
		}
		else if (sig == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g.ret = 130;
		}
	}
	if (sig == SIGINT)
		sig_c();
}

void	sig_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g.pid != 0)
		process(sig);
	else
	{
		if (sig == SIGINT)
			sig_c();
		else if (sig == SIGQUIT)
			ft_putstr_fd("\r", 1);
	}
}
