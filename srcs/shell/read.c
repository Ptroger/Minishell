#include "../../includes/minishell.h"

void	read_loop(t_vars *vars)
{
	char	*line;

	while (vars->shell == RUNNING)
	{
		vars->parse_i = 0;
		signal(SIGQUIT, SIG_IGN);
		line = readline(PROMPT);
		if (line && *line)
		{
			add_history(line);
			parse(line, vars);
			free(line);
			signal(SIGQUIT, sig_handler);
			call_command(&vars, FALSE);
			ft_lstclear(&vars->tokens, free);
			unlink("./temp");
		}
		else if (!line)
		{
			destroy_vars(vars);
			exit(0);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sa;
	t_vars				*vars;

	(void)ac;
	(void)av;
	vars = ft_init_vars();
	ft_set_env(&vars->t_env, env);
	ft_get_env_name(&vars->t_env, env);
	ft_set_exp(&vars->t_exp, &vars->t_env);
	sa.sa_handler = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	read_loop(vars);
	destroy_vars(vars);
}
