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

int	main(int ac, char **av)
{
	char	*line;
	t_vars	*vars;
	t_list	*tet;
//	int i = 0;
	(void)ac;
	(void)av;

	vars = malloc(sizeof(t_vars));
	vars->shell = RUNNING;
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	vars->tokens = NULL;
	vars->finish_line = FALSE;
//	init_token(vars);
//	vars = initialize();
	while (vars->shell == RUNNING)
	{
		line = readline(PROMPT);
		add_history(line);
		parse(line, vars);
		free(line);
		tet = vars->tokens;
//		while (tet)
//		{
//			printf("i = %d", i);
//			i++;
//			ft_putstr_lst(tet->token);
//			tet = tet->next;
//		}
		ft_lstiter(vars->tokens, ft_putstr_lst);
		ft_putstr_lst("\n");
		ft_lstclear(&vars->tokens, free);
	}
//	destroy(vars);
}
