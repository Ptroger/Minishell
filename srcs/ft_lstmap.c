/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:23:51 by ptroger           #+#    #+#             */
/*   Updated: 2020/01/05 19:30:10 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new_lst;

	if (!lst || !f)
		return (NULL);
	if (lst)
	{
		new_lst = ft_lstnew(f(lst->content));
		new_lst->next = ft_lstmap(lst->next, f, del);
		return (new_lst);
	}
	return (NULL);
}
