#include "includes/minishell.h"

int main()
{
	g.pid = fork();
	signal(SIGQUIT, SIG_IGN);
	if (g.pid == 0)
	{
		signal(SIGQUIT, sig_handler);
		printf("ici\n");
		while (1)
			;
	}
	wait(NULL);
}