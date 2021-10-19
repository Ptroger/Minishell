/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:19:12 by ptroger           #+#    #+#             */
/*   Updated: 2019/11/13 19:16:58 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **alst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*first;

	first = *alst;
	if (!alst || !del)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		del((*alst)->content);
		free(*alst);
		*alst = tmp;
	}
	first = NULL;
}
