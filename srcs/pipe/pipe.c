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

int	ft_process(t_vars **vars, t_pipe *temp_p, int size, int *pfd)
{
	int		count;
	int		file;
	t_list	*temp;
	t_list	*temp_1;

	count = 0;
	file = 0;
	temp = (*vars)->tokens;
	temp_1 = (*vars)->tokens;
	while (temp_p)
	{
		temp = (*vars)->tokens;
		while (temp && ft_strcmp(temp->token, "|") != 0)
			temp = temp->next;
		if (ft_strcmp(temp->token, "|") == 0 && !temp->next)
			return (ft_new_readline(vars));
		ft_process_2(vars, temp_p);
		g_g.pid = fork();
		if (g_g.pid < 0)
			return (ft_error("Fork failed"));
		if (g_g.pid == 0)
		{
			ft_dup(temp_p, count, size, pfd);
			ft_process_3(vars, temp_p, temp_1, &file);
		}
		ft_browse_tmp(&temp_1);
		count += 2;
		temp_p = temp_p->next;
	}
	return (1);
}

int	ft_child(t_vars **vars, t_pipe *store, int size)
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
	ft_process(vars, temp_p, size, pfd);
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
	while (j < i && ft_strcmp((*temp_2)->token, "|") != 0)
	{
		temp_p->cell[j] = ft_strdup((*temp_2)->token);
		if ((*temp_2)->next)
			(*temp_2) = (*temp_2)->next;
		j++;
	}
	if ((*temp_2)->next && ft_strcmp((*temp_2)->token, "|") == 0)
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
		while (ft_strcmp(temp_1->token, "|") != 0 && temp_1->next && ++i)
			temp_1 = temp_1->next;
		if (ft_strcmp(temp_1->token, "|") == 0 && temp_1->next)
			temp_1 = temp_1->next;
		if (!temp_p->next)
			i++;
		temp_p->cell = (char **)malloc(sizeof(char *) * i);
		if (!temp_p->cell)
			return ;
		if (temp_p->next)
			i++;
		ft_store_command_2(&temp_2, temp_p, i);
		temp_p = temp_p->next;
	}
}

int	ft_pipe(t_vars **vars, t_pipe *store)
{
	int		i;
	int		size;
	t_list	*temp;

	i = 0;
	size = 0;
	temp = (*vars)->tokens;
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") == 0)
			size++;
		temp = temp->next;
	}
	size++;
	while (i < size)
	{
		ft_add_elem_pipe(&store);
		i++;
	}
	ft_store_command((*vars)->tokens, store);
	ft_child(vars, store, size);
	return (0);
}