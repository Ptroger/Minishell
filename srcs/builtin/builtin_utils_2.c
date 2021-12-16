/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:57:00 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 13:05:34 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_key(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

void	ft_add_elem_exp_2(t_sort **sort, t_sort *new_elem, char *env)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (env[++j] != '=')
	{
		new_elem->data[i] = env[j];
		i++;
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

void	ft_add_elem_exp(t_sort **sort, char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return ;
	new_elem->data = malloc(sizeof(char) * ft_strlen(env) + 3);
	if (!new_elem->data)
		return ;
	new_elem->info = NULL;
	new_elem->name = NULL;
	ft_add_elem_exp_2(sort, new_elem, env);
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
