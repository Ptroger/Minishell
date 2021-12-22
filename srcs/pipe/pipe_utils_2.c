/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:31:40 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/10 10:31:43 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_browse_tmp(t_list **temp, t_pipe **temp_p, int *count)
{
	while (*temp && ft_strcmp((*temp)->token, "|") != 0)
		*temp = (*temp)->next;
	if (*temp && (*temp)->next)
		*temp = (*temp)->next;
	*count += 2;
	(*temp_p) = (*temp_p)->next;
}

void	ft_process_4(t_vars **vars, t_pipe **temp_p, t_list *temp_1)
{
	t_list	*temp_2;

	temp_2 = (*vars)->tokens;
	if (ft_is_builtin((*temp_p)->token) == 1)
	{
		ft_call_builtin(vars, temp_1);
		clean_exit(*vars, g_g.ret);
	}
	else if (is_special(temp_2) == TRUE && temp_1->next
		&& temp_1->next->next && ft_is_builtin(temp_1->next->next->token) == 1)
	{
		ft_call_builtin(vars, temp_1->next->next);
		clean_exit(*vars, g_g.ret);
	}
	else if (is_special(temp_2) == TRUE && temp_1->next
		&& temp_1->next->next && shall_exec(*vars, temp_1) == TRUE)
		ft_find_cmd(*vars, temp_1->next->next->token,
			&(*temp_p)->cmd, (*vars)->path);
	else
		ft_find_cmd(*vars, (*temp_p)->token, &(*temp_p)->cmd, (*vars)->path);
}

void	ft_process_3(t_vars **vars, t_pipe *temp_p, t_list *temp_1)
{
	int		file;
	t_list	*temp;

	file = 0;
	temp = temp_1;
	while (temp_1)
	{
		if (is_special(temp_1) == TRUE && temp_p->redir >= 1)
		{
			handle_redirs(*vars, temp_1, &file);
			ft_process_4(vars, &temp_p, temp);
			close(file);
			clean_exit(*vars, 0);
			return ;
		}
		temp_1 = temp_1->next;
	}
	ft_process_4(vars, &temp_p, temp);
}

int	ft_process_2(t_vars *vars)
{
	int		i;
	int		is_ok;
	t_pipe	**temp_p;

	i = 0;
	temp_p = &vars->store;
	if ((*temp_p)->cell[0] != NULL)
		i--;
	is_ok = find_path_2((*temp_p)->token, vars->path);
	(*temp_p)->token = ft_strdup((*temp_p)->cell[0]);
	if (ft_is_builtin((*temp_p)->token) == 0
		&& is_ok == TRUE)
	{
		(*temp_p)->cmd = ft_command_size((*temp_p)->size + 1);
		while (i < (*temp_p)->size - 1 && (*temp_p)->size > 1
			&& ft_is_key((*temp_p)->cell[i + 1]) == 0)
		{
			(*temp_p)->cmd[i + 1] = dupfree((*temp_p)->cell[i + 1],
					(*temp_p)->cmd[i + 1]);
			i++;
		}
	}
	return (1);
}
