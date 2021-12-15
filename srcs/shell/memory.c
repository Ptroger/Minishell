#include "minishell.h"

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
	vars->tab_size = 0;
	vars->real_envs = NULL;
	g_g.ret = 0;
	g_g.pid = 0;
	return (vars);
}

void	destroy_env(t_sort **envs)
{
	t_sort	*temp;

	while (*envs)
	{
		temp = *envs;
		if (temp->data)
			free(temp->data);
		if (temp->name)
			free(temp->name);
		if (temp->info)
			free(temp->info);
		*envs = (*envs)->next;
		free(temp);
	}
	*envs = NULL;
}

void	destroy_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	destroy_store(t_pipe *store)
{
	while (store)
	{
		if (store->token)
			free(store->token);
//		destroy_tab(store->cmd);
//		destroy_tab(store->cell);
		store = store->next;
	}
	free(store);
}

void	destroy_vars(t_vars *vars)
{
	if (vars)
	{
		ft_lstclear(&vars->tokens, free);
		destroy_env(&vars->t_exp);
		destroy_env(&vars->t_env);
		destroy_tab(vars->real_envs, vars->tab_size);
		destroy_store(vars->store);
		free(vars);
	}
}
