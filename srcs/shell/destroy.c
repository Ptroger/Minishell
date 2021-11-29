#include "minishell.h"

void	destroy_tokens(t_list *tokens)
{
	if (tokens)
	{
		while (tokens)
		{
			if (tokens->token)
				free(tokens->token);
			tokens = tokens->next;
		}
		free(tokens);
	}
}

void	destroy_env(t_sort *envs)
{
	if (envs)
	{
		while (envs)
		{
			if (envs->name)
				free(envs->name);
			if (envs->data)
				free(envs->data);
			if (envs->info)
				free(envs->info);
			envs = envs->next;
		}
		free(envs);
	}
}

void	destroy_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	destroy_store(t_pipe *store)
{
	if (store)
	{
		while (store)
		{
			if (store->token)
				free(store->token);
			destroy_tab(store->cmd);
			destroy_tab(store->cell);
			store = store->next;
		}
		free(store);
	}
}

void	destroy_vars(t_vars *vars)
{
	if (vars)
	{
		destroy_tokens(vars->tokens);
		destroy_env(vars->t_env);
		destroy_env(vars->t_exp);
		destroy_store(vars->store);
		free(vars);
	}
}
