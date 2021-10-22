/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:22:49 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/04 19:41:44 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstiter(t_list *lst, void (*f)(char *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->token);
		lst = lst->next;
	}
}
