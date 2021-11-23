#include "../includes/minishell.h"

//const struct sigaction	setup_handler(void (*handler)(int))
//{
//	struct sigaction	sa;
//
//	sa.sa_flags = flag;
//	sa.sa_handler = handler;
//	return ((const struct sigaction )sa);
//}
void	sig_q(int sig)
{
	// TODO: voir avec Aristide comment on peut implémenter ca
	if (sig == SIGQUIT)
	{
//		if (term == INTERACTIVE)
			return ;
	}
}

void	sig_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
//		rl_
	}
}