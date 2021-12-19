/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:54:04 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/09 16:54:06 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str)
{
	ft_putendl(str);
	return (-1);
}

char	**ft_command_size(int size)
{
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	while (size)
	{
		cmd[size] = NULL;
		size--;
	}
	cmd[0] = ft_strdup("tmp");
	return (cmd);
}

t_pipe	*ft_add_elem_pipe()
{
	t_pipe	*new_elem;

	new_elem = malloc(sizeof(t_pipe));
	if (!new_elem)
		return (NULL);
	new_elem->cell = NULL;
	new_elem->cmd = NULL;
	new_elem->size = 0;
	new_elem->token = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd)
{
	int		i;

	i = 0;
	if (temp_p->next)
		dup2(pfd[count + 1], 1);
	if (count != 0)
		dup2(pfd[count - 2], 0);
	while (i < (2 * (size - 1)))
	{
		close(pfd[i]);
		i++;
	}
}

void	pipe_add_back(t_pipe **sort, t_pipe *new)
{
	t_pipe	*lst;
	int 	i; 
	
	i = 0;
	if (!sort)
		return ;
	if (!*sort)
	{
		*sort = new;
		return ;
	}
	lst = *sort;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	lst->next = new;
}
