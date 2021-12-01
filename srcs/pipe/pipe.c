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
	int		i;
	int		count;
	int		file;
	t_list	*temp_1;
	t_list	*temp_2;
	t_list	*temp_3;

	count = 0;
	file = 0;
	temp_1 = (*vars)->tokens;
	while (temp_p)
	{
		i = -1;
		temp_3 = (*vars)->tokens;
		while (temp_3 && ft_strcmp(temp_3->token, "|") != 0)
			temp_3 = temp_3->next;
		if (ft_strcmp(temp_3->token, "|") == 0 && !temp_3->next)
			return (ft_new_readline(vars));
		temp_p->token = ft_strdup(temp_p->cell[0]);
		temp_p->cmd = ft_command_size(temp_p->size + 1);
		while (++i < temp_p->size - 1 && temp_p->size > 1 && ft_is_key(temp_p->cell[i + 1]) == 0)
			temp_p->cmd[i + 1] = ft_strdup(temp_p->cell[i + 1]);
		g.pid = fork();
		if (g.pid < 0)
			return (ft_error("Fork failed"));
		temp_2 = (*vars)->tokens;
		temp_3 = (*vars)->tokens;
		if (g.pid == 0)
		{
/*			while (temp_3 && ft_strcmp(temp_3->token, "|") != 0)
				temp_3 = temp_3->next;
			if (ft_strcmp(temp_3->token, "|") == 0 && !temp_3->next)
			{
				return (ft_new_readline(vars));
				exit (1);
			}
*/			ft_dup(temp_p, count, size, pfd);
			while (temp_2 && ft_strcmp(temp_2->token, "|") != 0)
			{
				if (is_special(*vars, temp_2) == TRUE)
					handle_redirs(temp_2, &file);
				temp_2 = temp_2->next;
			}
			if (ft_is_builtin(temp_p->token) == 1)
			{
				ft_call_builtin(vars, temp_1);
				exit(1);
			}
			else if (is_special(*vars, temp_3) == TRUE && temp_1->next && temp_1->next->next && ft_is_builtin(temp_1->next->next->token) == 1)
			{
				ft_call_builtin(vars, temp_1->next->next);
				exit(1);
			}
			else if (is_special(*vars, temp_3) == TRUE && temp_1->next && temp_1->next->next)
				ft_find_cmd(temp_1->next->next->token, temp_p->cmd, (*vars)->path);
			else
				ft_find_cmd(temp_p->token, temp_p->cmd, (*vars)->path);
		}
		while (temp_1 && ft_strcmp(temp_1->token, "|") != 0)
			temp_1 = temp_1->next;
		if (temp_1 && temp_1->next)
			temp_1 = temp_1->next;
		count += 2;
		temp_p = temp_p->next;
	}
//	exit (1);
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
		while (ft_strcmp(temp_1->token, "|") != 0 && temp_1->next)
		{
			temp_1 = temp_1->next;
			i++;
		}
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
