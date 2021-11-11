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

int	ft_process(t_vars **vars, t_pipe *temp_p, char **tab, int size, int *pfd)
{
	int		i;
	int		count;
	pid_t	child;

	count = 0;
	while (temp_p)
	{
		i = -1;
		temp_p->token = ft_strdup(temp_p->cell[0]);
		temp_p->cmd = ft_command_size(temp_p->size + 1);
		while (++i < temp_p->size - 1 && temp_p->size > 1)
			temp_p->cmd[i + 1] = ft_strdup(temp_p->cell[i + 1]);
		child = fork();
		if (child < 0)
			return (ft_error("Fork failed"));
		if (child == 0)
		{
			ft_dup(temp_p, count, size, pfd);
			ft_find_cmd(vars, temp_p->token, temp_p->cmd, tab);
		}
		count += 2;
		temp_p = temp_p->next;
	}
	return (1);
}

int	ft_child(t_vars **vars, t_pipe *store, char **tab, int size)
{
	int		i;
	int		status;
	int		*pfd;
	t_pipe	*temp_p;

	i = -1;
	temp_p = store;
	pfd = (int *)malloc(sizeof(int) * (2 * (size - 1)));
	if (!pfd)
		return (-1);
	while (++i < size - 1)
	{
		if (pipe(pfd + i * 2) == -1)
			return (ft_error("pipe failed"));
	}
	ft_process(vars, temp_p, tab, size, pfd);
	i = -1;
	while (++i < (2 * (size - 1)))
		close(pfd[i]);
	i = -1;
	while (++i < 2 * (size - 1) + 1)
		wait(&status);
	return (1);
}

void	ft_store_command_2(t_list **temp_2, t_pipe *temp_p, int i)
{
	int		j;

	j = 0;
	while (ft_strcmp((*temp_2)->token, "|") != 0 && j < i + 1)
	{
		temp_p->cell[j] = ft_strdup((*temp_2)->token);
		if ((*temp_2)->next)
			(*temp_2) = (*temp_2)->next;
		j++;
	}
	if (ft_strcmp((*temp_2)->token, "|") == 0 && (*temp_2)->next)
		(*temp_2) = (*temp_2)->next;
	temp_p->size = j;
}

void	ft_store_command(t_list *tokens, t_pipe *store)
{
	int		i;
	t_list	*temp_1;
	t_list	*temp_2;
	t_pipe	*temp_p;

	temp_1 = tokens;
	temp_2 = tokens;
	temp_p = store;
	while (temp_p)
	{
		i = 0;
		while (ft_strcmp(temp_1->token, "|") != 0 && temp_1->next)
		{
			temp_1 = temp_1->next;
			i++;
		}
		if (ft_strcmp(temp_1->token, "|") == 0 && temp_1->next)
			temp_1 = temp_1->next;
		temp_p->cell = (char **)malloc(sizeof(char *) * i + 1);
		if (!temp_p->cell)
			return ;
		ft_store_command_2(&temp_2, temp_p, i);
		temp_p = temp_p->next;
	}
}

int	ft_pipe(t_vars **vars, t_list *tokens, t_pipe *store, char **tab)
{
	int		i;
	int		size;
	t_list	*temp_1;

	i = 0;
	size = 0;
	temp_1 = tokens;
	while (temp_1)
	{
		if (ft_strcmp(temp_1->token, "|") == 0)
			size++;
		temp_1 = temp_1->next;
	}
	size++;
	while (i < size)
	{
		ft_add_elem_pipe(&store);
		i++;
	}
	ft_store_command(tokens, store);
	ft_child(vars, store, tab, size);
	return (0);
}
