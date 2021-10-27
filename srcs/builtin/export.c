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
	tmp = temp->str;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(tmp, temp->str) > 0)
			return (0);
		tmp = temp->str;
	}
	return (1);
}

char	*ft_return_max(t_sort **pile_a)
{
	char	*max;
	t_sort	*temp;

	temp = *pile_a;
	max = temp->str;
	while (temp->next)
	{
		temp = temp->next;
		if (ft_strcmp(max, temp->str) < 0)
			max = temp->str;
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
	new_elem->str = malloc(sizeof(char) * ft_strlen(env) + 3);
	if (!new_elem->str)
		return ;
	while (env[j] != '=')
	{
		new_elem->str[i] = env[j];
		i++;
		j++;
	}
	new_elem->str[i] = env[j];
	i++;
	j++;
	new_elem->str[i] = '"';
	i++;
	while (env[j])
	{
		new_elem->str[i] = env[j];
		i++;
		j++;
	}
	new_elem->str[i] = '"';
	new_elem->str[i + 1] = '\0';
	new_elem->next = *sort;
	*sort = new_elem;
}

void	ft_add_elem(t_sort **sort, char *env)
{
	t_sort	*new_elem;

	new_elem = malloc(sizeof(t_sort));
	if (!new_elem)
		return ;
	new_elem->str = env;
	new_elem->next = *sort;
	*sort = new_elem;
}

void    ft_export(t_list *tokens, t_sort  **t_exp)
{
	int		i;
	int		j;
//    char    *max;
//    t_sort  *t_exp;
    t_sort  *temp;

	i = 0;
	j = 0;
/*    t_exp = NULL;
	temp = *t_env;
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
*/    temp = *t_exp;
	if (tokens->next)
	{
		while (tokens->next->token[j] && tokens->next->token[j] != '=')
			j++;
		if (tokens->next->token[j] == '=' && tokens->next->token[j - 1] != ' ')
		{
			t_sort	*new_elem;

			new_elem = malloc(sizeof(t_sort));
			j = 0;
			while (temp->next)
				temp = temp->next;
			temp->next = new_elem;
			new_elem->str = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
			if (!new_elem->str)
				return ;
			while (tokens->next->token[j] && tokens->next->token[j] != '=')
			{
				new_elem->str[i] = tokens->next->token[j];
				i++;
				j++;
			}
			new_elem->str[i] = tokens->next->token[j];
			i++;
			j++;
			new_elem->str[i] = '"';
			i++;
			while (tokens->next->token[j])
			{
				new_elem->str[i] = tokens->next->token[j];
				i++;
				j++;
			}
			new_elem->str[i] = '"';
			new_elem->str[i + 1] = '\0';
			new_elem->next = NULL;
		}
	}
    temp = *t_exp;
    while (temp->next)
    {
        printf("%s", "declare -x ");
        if (temp->str[0] == '_' && temp->str[1] == '=' && temp->str[2] == '/')
            temp = temp->next;
        printf("%s\n", temp->str);
        temp = temp->next;
    }
    printf("%s", "declare -x ");
    printf("%s\n", temp->str);
}