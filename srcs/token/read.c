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

void	ft_set_exp(t_sort  **t_exp, t_sort  **t_env)
{
	char    *max;
	t_sort  *temp;

	temp = *t_env;
    while (temp->next)
    {
        ft_add_elem_exp(t_exp, temp->data);
		temp = temp->next;
    }
    max = ft_return_max(t_exp);
    while (ft_pile_in_order(t_exp) != 1)
    {
        if (*t_exp && (*t_exp)->next && ft_strcmp((*t_exp)->data,
		(*t_exp)->next->data) > 0 && ft_strcmp((*t_exp)->data, max) != 0
		&& ft_strcmp((*t_exp)->next->data, max) != 0)
            ft_swap(t_exp);
        ft_reverse_rotate(t_exp);
    }
}

void	ft_set_env(t_sort  **t_env, char **env)
{
	int     i;
	int		j;
	
	i = 0;
	j = 0;
	while (env[i])
        i++;
    while (i)
    {
        ft_add_elem(t_env, env[i]);
        i--;
    }
}

void	ft_get_env_name(t_sort  **t_env, char **env)
{
	int		i;
	int		j;
	t_sort  *temp;

	i = 0;
	j = 0;
	temp = *t_env;
	while (env[i])
	{
		j = 0;
		temp->name = malloc(sizeof(char) * ft_strlen(env[i]));
		if (!temp->name)
			return ;
		while (env[i][j] != '=')
		{
			temp->name[j] = env[i][j];
			j++;
		}
		temp->name[j] = '\0';
		temp = temp->next;
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_vars	*vars;
	t_list	*tet;
	(void)ac;
	(void)av;

	vars = malloc(sizeof(t_vars));
	vars->shell = RUNNING;
	vars->state = BASIC;
	vars->token_size = TOKENSIZE;
	vars->tokens = NULL;
	vars->finish_line = FALSE;
	vars->t_env = NULL;
	vars->t_exp = NULL;
	vars->store = NULL;
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
		call_command(tet, &vars->t_env, &vars->t_exp, vars->store);
		ft_lstclear(&vars->tokens, free);
	}
}
