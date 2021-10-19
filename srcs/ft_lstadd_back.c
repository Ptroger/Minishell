/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:12:53 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/04 19:44:00 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *lst;

	if (!alst)
		return ;
	lst = *alst;
	if (lst)
	{
		while ((lst)->next)
			lst = (lst)->next;
		(lst)->next = new;
	}
	else
		*alst = new;
}
