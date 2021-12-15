/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:24:38 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 14:57:37 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_exp(t_sort **t_exp, t_sort **t_env)
{
	char	*max;
	t_sort	*temp;

	temp = *t_env;
	while (temp && temp->next)
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

void	ft_set_env(t_sort **t_env, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	while (i--)
		ft_add_elem(t_env, env[i]);
}

void	ft_get_env_name(t_sort **t_env, char **env)
{
	int		i;
	int		j;
	int		k;
	t_sort	*temp;

	i = 0;
	temp = *t_env;
	while (env[i])
	{
		j = 0;
		k = 0;
		temp->name = malloc(sizeof(char) * ft_strlen(env[i]));
		temp->info = malloc(sizeof(char) * ft_strlen(env[i]));
		if (!temp->name)
			return ;
		while (env[i][j] != '=')
		{
			temp->name[j] = env[i][j];
			j++;
		}
		temp->name[j] = '\0';
		j++;
		while (env[i][j])
		{
			temp->info[k] = env[i][j];
			j++;
			k++;
		}
		temp->info[k] = '\0';
		temp = temp->next;
		i++;
	}
}

void	ft_env(t_sort **t_env)
{
	t_sort	*temp;

	temp = *t_env;
	while (temp)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
}

void	ft_call_env(t_vars **vars, t_list *tokens)
{
	if (tokens->next && (ft_strcmp(tokens->next->token, "yes") == 0
		|| ft_strcmp(tokens->next->token, "YES") == 0))
	{
		while (1)
			printf("y\n");
		exit(0);
	}
	if (tokens->next && ft_is_key(tokens->next->token) == 0)
	{
		printf("env: %s: No such file or directory\n", tokens->next->token);
		exit(127);
	}
	else
	{
		ft_env(&(*vars)->t_env);
		exit(0);
	}
}
