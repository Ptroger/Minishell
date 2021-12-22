/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:59:57 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/21 19:10:30 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redir_3(t_vars **vars, t_list *temp, int *file)
{
	char	**cmd;

	(void)temp;

	if (temp->type != H_DOC)
		handle_redirs(*vars, temp, file);
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens);
	else if (is_special((*vars)->tokens) == TRUE && (*vars)->tokens->next
		&& (*vars)->tokens->next->next
		&& ft_is_builtin((*vars)->tokens->next->next->token) == 1)
	{
		ft_call_builtin(vars, (*vars)->tokens->next->next);
		exit(g_g.ret);
	}
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
	if (close(*file) != 0)
	{
		throw_error(NULL, errno);
		clean_exit(*vars, 2);
	}
	clean_exit(*vars, 0);
}

void	ft_check_redir_2(t_vars **vars, t_list *temp)
{
	t_list	*temp_2;
	int		file;

	temp_2 = (*vars)->tokens;
	file = 0;
	if (temp->type == H_DOC)
		handle_redirs(*vars, temp, &file);
	while (temp_2)
	{
		if (ft_strcmp("|", temp_2->token) == 0)
		{
			ft_pipe(vars);
			if (close(file) != 0)
			{
				throw_error(NULL, errno);
				clean_exit(*vars, 2);
			}
			clean_exit(*vars, 0);
			return ;
		}
		temp_2 = temp_2->next;
	}
	ft_check_redir_3(vars, temp, &file);
}

int	ft_check_redir(t_vars **vars)
{
	int		status;
	t_list	*temp;

	(*vars)->size = 1;
	temp = (*vars)->tokens;
	while (temp->next)
	{
		if (is_special(temp) == TRUE && shall_exec(*vars, temp) == TRUE)
		{
			signal(SIGINT, SIG_IGN);
			g_g.pid = fork();
			signal(SIGINT, sig_handler);
			if (g_g.pid == 0)
				ft_check_redir_2(vars, temp);
			wait(&status);
			g_g.ret = WEXITSTATUS(status);
			signal(SIGINT, sig_handler);
			return (TRUE);
		}
		temp = temp->next;
		(*vars)->size++;
	}
	return (FALSE);
}
