/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:24:38 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 09:39:32 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_sort **t_env)
{
	t_sort	*temp;

	temp = *t_env;
	while (temp->next)
	{
		printf("%s\n", temp->data);
		temp = temp->next;
	}
}
