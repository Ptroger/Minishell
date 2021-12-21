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

int	ft_find_redir(t_vars **vars, t_pipe **temp_p_2, t_list **temp_2)
{
	int		i;
	t_list	*temp;

	temp = (*vars)->tokens;
	while (*temp_p_2 && (*temp_p_2)->redir == 0)
	{
		i = 0;
		while (i < (*temp_p_2)->size)
		{
			if (ft_is_redir((*temp_p_2)->cell[i]) == 1)
			{
				while (*temp_2 && is_special(*temp_2) == FALSE)
					*temp_2 = (*temp_2)->next;
				(*temp_p_2)->redir = 1;
				if (*temp_2 && (*temp_2)->type == H_DOC)
				{
					(*temp_p_2)->redir = 2;
					return (0);
				}
			}
			i++;
		}
		(*temp_p_2) = (*temp_p_2)->next;
	}
//	while (temp->next)
//		temp = temp->next;
//	if (ft_strcmp(temp->token, "|") == 0)
//		return (ft_new_readline(vars));
	return (0);
}

int	ft_process(t_vars **vars, t_pipe **temp_p, int size, int *pfd)
{
	int		count;
	t_list	*temp_2;
	t_list	*temp_1;
	t_pipe	*temp_p_2;

	count = 0;
	temp_1 = (*vars)->tokens;
	temp_2 = (*vars)->tokens;
	temp_p_2 = *temp_p;
	(*vars)->original = (*vars)->store;
	while (*temp_p)
	{
		if (ft_find_redir(vars, &temp_p_2, &temp_2) == 1)
		{
			printf("YO\n");
			return (1);
		}
		ft_process_2(temp_p);
		g_g.pid = fork();
		if (g_g.pid < 0)
			return (throw_error("Fork failed", errno));
		if (g_g.pid == 0)
		{
			ft_dup(*temp_p, count, size, pfd);
			ft_process_3(vars, *temp_p, temp_1);
		}
		ft_browse_tmp(&temp_1, temp_p, &count);
		count += 2;
		(*temp_p) = (*temp_p)->next;
	}
	return (1);
}

void	ft_close_pfd(int *pfd, int size)
{
	int		i;
	int		status;

	i = -1;
	while (++i < (2 * (size - 1)))
		close(pfd[i]);
	free(pfd);
	i = -1;
	while (++i < 2 * (size - 1) + 1)
	{
		wait(&status);
		g_g.ret = WEXITSTATUS(status);
	}
}

int	ft_child(t_vars **vars, t_pipe **store, int size)
{
	int		i;
	int		*pfd;

	i = -1;
	pfd = (int *)malloc(sizeof(int) * (2 * (size - 1)));
	if (!pfd)
		return (-1);
	while (++i < size - 1)
	{
		if (pipe(pfd + i * 2) == -1)
		{
			free(pfd);
			return (throw_error("pipe failed", 2));
		}
	}
	ft_process(vars, store, size, pfd);
	ft_close_pfd(pfd, size);
	return (1);
}

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
	while (temp)
	{
		if (ft_strcmp(temp->token, "|") == 0)
		{
			pipe_add_back(&(*vars)->store, ft_add_elem_pipe());
			size++;
		}
		temp = temp->next;
	}
	pipe_add_back(&(*vars)->store, ft_add_elem_pipe());
	size++;
	ft_store_command((*vars)->tokens, &(*vars)->store);
	ft_child(vars, &(*vars)->store, size);
	return (0);
}
