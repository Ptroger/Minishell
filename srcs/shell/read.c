#include "../../includes/minishell.h"

int	check_str(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

void	read_loop(t_vars *vars)
{
	char	*line;

	while (vars->shell == RUNNING)
	{
		vars->parse_i = 0;
		signal(SIGQUIT, SIG_IGN);
		line = readline(PROMPT);
//		ft_putnbr_fd(g_g.pid, 1);
		if (!line)
		{
			destroy_vars(vars);
			exit(0);
		}
		if (check_str(line) != 0)
			throw_error(vars, "syntax error", 1);
		parse(line, vars);
		add_history(line);
		free(line);
		call_command(&vars, FALSE);
		ft_lstclear(&vars->tokens, free);
		unlink("./temp");
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars				*vars;

	(void)ac;
	(void)av;
	vars = ft_init_vars();
	ft_set_env(&vars->t_env, env);
	ft_get_env_name(&vars->t_env, env);
	ft_set_exp(&vars->t_exp, &vars->t_env);
	signal(SIGINT, sig_handler);
	read_loop(vars);
	destroy_vars(vars);
}
