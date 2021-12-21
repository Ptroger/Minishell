/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:59:54 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/09 16:53:06 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_store_command_2(t_list **temp_2, t_pipe **temp_p, int i)
{
	int		j;

	j = 0;
	while ((*temp_2) && j < i && ft_strcmp((*temp_2)->token, "|") != 0)
	{
		(*temp_p)->cell[j] = ft_strdup((*temp_2)->token);
		(*temp_2) = (*temp_2)->next;
		j++;
	}
	if (*temp_2 && (*temp_2)->next && ft_strcmp((*temp_2)->token, "|") == 0)
		(*temp_2) = (*temp_2)->next;
	(*temp_p)->size = j;
}

void	ft_set_store(t_pipe	**temp_p, int i)
{
	(*temp_p)->cell = (char **)malloc(sizeof(char *) * (i + 1));
	(*temp_p)->cell[i] = NULL;
	(*temp_p)->redir = 0;
	(*temp_p)->index = 0;
	if (!(*temp_p)->cell)
		return ;
}

void	ft_store_command(t_list *tokens, t_pipe **store)
{
	int		i;
	t_list	*temp_1;
	t_list	*temp_2;
	t_pipe	*temp_p;

	temp_1 = tokens;
	temp_2 = tokens;
	temp_p = *store;
	while (temp_p)
	{
		i = 0;
		while (ft_strcmp(temp_1->token, "|") != 0 && temp_1->next && ++i)
			temp_1 = temp_1->next;
		if (ft_strcmp(temp_1->token, "|") == 0 && temp_1->next)
			temp_1 = temp_1->next;
		if (!temp_p->next)
			i++;
		ft_set_store(&temp_p, i);
		if (temp_p->next)
			i++;
		ft_store_command_2(&temp_2, &temp_p, i);
		temp_p = temp_p->next;
	}
}

int	ft_pipe(t_vars **vars)
{
	int		size;
	t_list	*temp;

	size = 0;
	temp = (*vars)->tokens;
	pipe_add_back(&(*vars)->store, ft_add_elem_pipe());
	size++;
	(*vars)->original = (*vars)->store;
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") == 0)
		{
			pipe_add_back(&(*vars)->store, ft_add_elem_pipe());
			size++;
		}
		temp = temp->next;
	}
	ft_store_command((*vars)->tokens, &(*vars)->store);
	ft_child(vars, &(*vars)->store, size);
	return (0);
}
