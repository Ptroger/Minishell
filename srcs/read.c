#include "minishell.h"

void	init_token(t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	vars->tokens = ft_lstnew((void *)token, 0);
}

void	add_token(t_vars *vars)
{
	t_list	*list;
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	list = ft_lstnew((void *)token, 0);
	ft_lstadd_back(&vars->tokens, list);
}

int	main(int ac, char **av)
{
	char	*line;
	t_vars	*vars;
	(void)ac;
	(void)av;

	vars = malloc(sizeof(t_vars));
	vars->shell = RUNNING;
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	init_token(vars);
//	vars = initialize();
	while (vars->shell == RUNNING)
	{
		line = readline(PROMPT);
		add_history(line);
		parse(line, vars);
		free(line);
	}
//	destroy(vars);
}
