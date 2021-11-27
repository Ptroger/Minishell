#include "../includes/minishell.h"

//const struct sigaction	setup_handler(void (*handler)(int))
//{
//	struct sigaction	sa;
//
//	sa.sa_flags = flag;
//	sa.sa_handler = handler;
//	return ((const struct sigaction )sa);
//}
//void	sig_q(int sig)
//{
//	if (sig == SIGQUIT)
//	{
//		if (term == INTERACTIVE)
//			return ;
//	}
//}

void	sig_c()
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
//	printf("UNUNUNC\n");
	if ((sig == SIGINT || sig == SIGQUIT) && g.pid != 0)
		process(sig);
	else
	{
		if (sig == SIGINT)
			sig_c();
		else if (sig == SIGQUIT)
		{
//			printf("je ne dois jamais voir ca\n");
			ft_putstr_fd("\r", 1);
		}
	}
}
