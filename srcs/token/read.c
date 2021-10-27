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

int	main(int ac, char **av, char **env)
{
	int     i;
	int		j;
	char	*line;
	char    *max;
    t_sort  *t_exp;
    t_sort  *temp;
	t_vars	*vars;
	t_list	*tet;
    t_sort  *t_env;
	(void)ac;
	(void)av;

    i = 0;
	j = 0;
    t_env = NULL;
	while (env[i])
        i++;
	i--;
    while (i)
    {
        ft_add_elem(&t_env, env[i]);
        i--;
    }
	i = 0;
    t_exp = NULL;
	temp = t_env;
    while (temp->next)
    {
        ft_add_elem_exp(&t_exp, temp->str);
		temp = temp->next;
    }
    max = ft_return_max(&t_exp);
    while (ft_pile_in_order(&t_exp) != 1)
    {
        if (t_exp && t_exp->next && ft_strcmp(t_exp->str, t_exp->next->str) > 0
		&& ft_strcmp(t_exp->str, max) != 0 && ft_strcmp(t_exp->next->str, max) != 0)
            ft_swap(&t_exp);
        ft_reverse_rotate(&t_exp);
    }
	vars = malloc(sizeof(t_vars));
	vars->shell = RUNNING;
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	vars->tokens = NULL;
	vars->finish_line = FALSE;
	while (vars->shell == RUNNING)
	{
		line = readline(PROMPT);
    //    printf("\033[0;36m\033[1m %s\033[0;m", "Minishell ");
		add_history(line);
		parse(line, vars);
		free(line);
		tet = vars->tokens;
		call_command(vars->tokens, &t_env, &t_exp);
		ft_lstclear(&vars->tokens, free);
	}
//	destroy(vars);
}
