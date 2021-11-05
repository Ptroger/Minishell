/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:48:49 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/28 10:48:51 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pile(t_sort	**pile_a)
{
	t_sort		*temp;

	while (*pile_a)
	{
		temp = *pile_a;
		(*pile_a) = (*pile_a)->next;
		free(temp);
	}
}

void    ft_unset(t_list *tokens, t_sort **t_env, t_sort  **t_exp)
{
    int     i;
    int     j;
    t_sort  *temp;
    t_sort  *temp_1;
    t_sort  *temp_2;
    t_sort  *temp_3;

    i = 0;
    temp = *t_env;
    temp_1 = temp;
    temp_2 = temp;
    temp_3 = temp;
    while (temp->next && ft_strcmp(tokens->next->token, temp->name) != 0)
    {
        temp = temp->next;
        i++;
    }
    i--;
    j = i - 1;
    if (ft_strcmp(tokens->next->token, temp->name) == 0)
    {
        while (i--)
            temp_2 = temp_2->next;
        while (j--)
            temp_1 = temp_1->next;
        temp_3 = temp_2->next;
        temp_2->next = NULL;
        temp_1->next = temp_3;
    }
    ft_free_pile(t_exp);
    *t_exp = NULL;
    ft_set_exp(t_exp, t_env);
}