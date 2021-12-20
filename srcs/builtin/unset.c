/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:48:49 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:21:07 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pile(t_sort **pile_a)
{
	t_sort		*temp;

	while (*pile_a)
	{
		temp = *pile_a;
		(*pile_a) = (*pile_a)->next;
		free(temp);
	}
}

void	ft_free_pile_p(t_pipe **pile_a)
{
	t_pipe		*temp;

	while (*pile_a)
	{
		temp = *pile_a;
		(*pile_a) = (*pile_a)->next;
		free(temp);
	}
}

void	ft_unset_exp(t_sort **t_env, int i)
{
	int		j;
	t_sort	*temp_1;
	t_sort	*temp_2;
	t_sort	*temp_3;

	j = i - 1;
	temp_1 = *t_env;
	temp_2 = *t_env;
	temp_3 = *t_env;
	while (i-- && temp_2)
		temp_2 = temp_2->next;
	while (j-- && temp_1)
		temp_1 = temp_1->next;
	temp_3 = temp_2->next;
	temp_2->next = NULL;
	temp_1->next = temp_3;
}

void	ft_unset_env(t_sort **t_env, int i)
{
	int		j;
	t_sort	*temp_1;
	t_sort	*temp_2;
	t_sort	*temp_3;

	j = i - 1;
	temp_1 = *t_env;
	temp_2 = *t_env;
	temp_3 = *t_env;
	while (i-- && temp_2->next)
		temp_2 = temp_2->next;
	while (j-- && temp_1)
		temp_1 = temp_1->next;
	temp_3 = temp_2->next;
	temp_2->next = NULL;
	temp_1->next = temp_3;
}

void	ft_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	char	*tmp;
	t_list	*temp;

	tmp = NULL;
	temp = tokens;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0
		&& is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0
			&& is_special(temp->next) == FALSE)
		{
			tmp = ft_strdup(temp->next->token);
			ft_parse_unset(temp, t_env, t_exp, tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
}
