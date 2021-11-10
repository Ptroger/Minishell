#include "minishell.h"

void	init_token(t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	vars->tokens = ft_lstnew((void *)token);
}

void	add_token(t_vars *vars)
{
	t_list	*list;
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	list = ft_lstnew((void *)token);
	ft_lstadd_back(&vars->tokens, list);
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
	vars->t_env = NULL;
	vars->t_exp = NULL;
	vars->store = NULL;
	return (vars);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_vars	*vars;
	t_list	*tet;

	(void)ac;
	(void)av;
	vars = ft_init_vars();
	ft_set_env(&vars->t_env, env);
	ft_get_env_name(&vars->t_env, env);
	ft_set_exp(&vars->t_exp, &vars->t_env);
	while (vars->shell == RUNNING)
	{
		line = readline(PROMPT);
		add_history(line);
		parse(line, vars);
		free(line);
		tet = vars->tokens;
		call_command(&vars);
	//	call_command(tet, &vars->t_env, &vars->t_exp, vars->store);
		ft_lstclear(&vars->tokens, free);
	}
}
