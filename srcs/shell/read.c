#include "../../includes/minishell.h"

void	init_token(t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	vars->tokens = ft_lstnew((void *)token, 0);
}

void	ft_putstr_lst(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		write(1, &token[i], 1);
		i++;
	}
}

t_vars	*ft_init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->shell = RUNNING;
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	vars->tokens = NULL;
	vars->finish_line = FALSE;
	vars->exit_status = 0;
	vars->t_env = NULL;
	vars->t_exp = NULL;
	vars->store = NULL;
	g.ret = 0;
	g.pid = 0;
	g.sig_int = FALSE;
	g.sig_q = FALSE;
	vars->prompt = ft_strdup("\033[0;36m\033[1mMinishell> \033[0;m");
	return (vars);
}

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
		}
		else if (!line)
			exit(0);
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
