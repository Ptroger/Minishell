#include "minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	t_vars	*vars;
	(void)ac;
	(void)av;

	vars->shell = RUNNING;
	vars->state = BASIC;
//	vars = initialize();
	while (vars.shell == RUNNING)
	{
		line = readline(PROMPT);
		add_history(line);
		parse(line, vars);
		free(line);
	}
//	destroy(vars);
}
