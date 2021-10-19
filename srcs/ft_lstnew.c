/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:09:25 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/04 17:55:14 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content, int i)
{
	t_list *elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (elem);
	elem->token = (void *)content;
	elem->i = i;
	elem->next = NULL;
	return (elem);
}
