/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:04:59 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/20 16:05:00 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pile_in_order(t_sort **pile_a)
{
	char    *tmp;
	t_sort	*temp;

	temp = *pile_a;
	tmp = temp->data;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(tmp, temp->data) > 0)
			return (0);
		tmp = temp->data;
	}
	return (1);
}

char	*ft_return_max(t_sort **pile_a)
{
	char	*max;
	t_sort	*temp;

	temp = *pile_a;
	max = temp->data;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(max, temp->data) < 0)
			max = temp->data;
	}
	return (max);
}

void	ft_swap(t_sort **pile)
{
	t_sort	*temp_1;
	t_sort	*temp_2;
	t_sort	*temp_3;

	temp_1 = *pile;
	temp_2 = temp_1->next;
	temp_3 = temp_2->next;
	*pile = temp_1->next;
	temp_1->next = temp_3;
	temp_2->next = temp_1;
}

void	ft_reverse_rotate(t_sort **pile)
{
	t_sort	*last;
	t_sort	*second_last;

	last = *pile;
	second_last = *pile;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	second_last->next = NULL;
	last->next = *pile;
	*pile = last;
}

void	ft_add_elem_exp(t_sort **sort, char *env)
{
	int		i;
	int		j;
	t_sort	*new_elem;

	i = 0;
	j = 0;
	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return ;
	new_elem->data = malloc(sizeof(char) * ft_strlen(env) + 3);
	if (!new_elem->data)
		return ;
	while (env[j] != '=')
	{
		new_elem->data[i] = env[j];
		i++;
		j++;
	}
	new_elem->data[i] = env[j];
	i++;
	j++;
	new_elem->data[i] = '"';
	i++;
	while (env[j])
	{
		new_elem->data[i] = env[j];
		i++;
		j++;
	}
	new_elem->data[i] = '"';
	new_elem->data[i + 1] = '\0';
	new_elem->next = *sort;
	*sort = new_elem;
}

void	ft_add_elem(t_sort **sort, char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return ;
	new_elem->data = env;
	new_elem->next = *sort;
	*sort = new_elem;
}

void    ft_export(t_list *tokens, t_sort **t_env, t_sort  **t_exp)
{
	int		i;
	int		j;
    t_sort  *temp_exp;
    t_sort  *temp_env;
	t_sort	*new_exp;
	t_sort	*new_env;

	i = 0;
	j = 0;
	temp_exp = *t_exp;
	temp_env = *t_env;
	if (tokens->next)
	{
		while (tokens->next->token[j] && tokens->next->token[j] != '=')
			j++;
		if (tokens->next->token[j] == '=' && tokens->next->token[j - 1] != ' ')
		{
			j = 0;
			new_exp = malloc(sizeof(t_sort));
			if (!new_exp)
				return ;
			new_env = malloc(sizeof(t_sort));
			if (!new_env)
				return ;
			while (temp_exp->next)
				temp_exp = temp_exp->next;
			while (temp_env->next)
				temp_env = temp_env->next;
			temp_exp->next = new_exp;
			temp_env->next = new_env;
			new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
			new_env->data = ft_strdup(tokens->next->token);
			new_env->next = NULL;
			if (!new_exp->data)
				return ;
			while (tokens->next->token[j] && tokens->next->token[j] != '=')
			{
				new_exp->data[i] = tokens->next->token[j];
				i++;
				j++;
			}
			new_exp->data[i] = tokens->next->token[j];
			i++;
			j++;
			new_exp->data[i] = '"';
			i++;
			while (tokens->next->token[j])
			{
				new_exp->data[i] = tokens->next->token[j];
				i++;
				j++;
			}
			new_exp->data[i] = '"';
			new_exp->data[i + 1] = '\0';
			new_exp->next = NULL;
		}
	}
	else
	{
		while (temp_exp->next)
		{
			printf("%s", "declare -x ");
			if (temp_exp->data[0] == '_' && temp_exp->data[1] == '=' && temp_exp->data[2] == '/')
				temp_exp = temp_exp->next;
			printf("%s\n", temp_exp->data);
			temp_exp = temp_exp->next;
		}
		printf("%s", "declare -x ");
		printf("%s\n", temp_exp->data);
	}
}