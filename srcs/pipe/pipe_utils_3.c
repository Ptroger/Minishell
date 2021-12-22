/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:53:48 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/21 18:53:49 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_redir(t_vars **vars, t_pipe **temp_p_2, t_list **temp_2)
{
	int		i;

	(void)vars;
	printf("je suis = %s\n", (*temp_2)->token);
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
				printf("temp_p2 == %s\n", (*temp_2)->token);
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
	*temp_2 = (*temp_2)->next;
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
	while (*temp_p)
	{
		if (ft_find_redir(vars, &temp_p_2, &temp_2) == 1)
			return (1);
		ft_process_2(vars);
		g_g.pid = fork();
		if (g_g.pid < 0)
			return (throw_error("Fork failed", errno));
		if (g_g.pid == 0)
		{
			ft_dup(*temp_p, count, size, pfd);
			ft_process_3(vars, *temp_p, temp_1);
		}
		ft_browse_tmp(&temp_1, temp_p, &count);
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
