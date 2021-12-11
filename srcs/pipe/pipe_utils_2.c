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

void	ft_browse_tmp(t_list **temp)
{
	while (*temp && ft_strcmp((*temp)->token, "|") != 0)
		*temp = (*temp)->next;
	if (*temp && (*temp)->next)
		*temp = (*temp)->next;
}

void	ft_process_4(t_vars **vars, t_pipe *temp_p, t_list *temp_1)
{
	t_list	*temp_2;

	temp_2 = (*vars)->tokens;
	if (ft_is_builtin(temp_p->token) == 1)
	{
		ft_call_builtin(vars, temp_1);
		exit(0);
	}
	else if (is_special(temp_2) == TRUE && temp_1->next
		&& temp_1->next->next && ft_is_builtin(temp_1->next->next->token) == 1)
	{
		ft_call_builtin(vars, temp_1->next->next);
		exit(0);
	}
	else if (is_special(temp_2) == TRUE && temp_1->next
		&& temp_1->next->next)
		ft_find_cmd(temp_1->next->next->token, temp_p->cmd, (*vars)->path);
	else
		ft_find_cmd(temp_p->token, temp_p->cmd, (*vars)->path);
}

void	ft_process_3(t_vars **vars, t_pipe *temp_p, t_list *temp_1, int *file)
{
	t_list	*temp;

	temp = (*vars)->tokens;
	while (temp)
	{
		if (is_special(temp) == TRUE)
		{
			handle_redirs(*vars, temp, file);
			ft_process_4(vars, temp_p, temp_1);
			return ;
		}
		temp = temp->next;
	}
	ft_process_4(vars, temp_p, temp_1);
}

int	ft_process_2(t_vars **vars, t_pipe *temp_p)
{
	int		i;
//	t_list	*temp;

	i = -1;
	(void)vars;
/*	temp = (*vars)->tokens;
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
	if (ft_strcmp(temp->token, "|") == 0 && !temp->next)
		return (ft_new_readline(vars));
*/	temp_p->token = ft_strdup(temp_p->cell[0]);
	temp_p->cmd = ft_command_size(temp_p->size + 1);
	while (++i < temp_p->size - 1 && temp_p->size > 1
		&& ft_is_key(temp_p->cell[i + 1]) == 0)
		temp_p->cmd[i + 1] = ft_strdup(temp_p->cell[i + 1]);
	return (1);
}