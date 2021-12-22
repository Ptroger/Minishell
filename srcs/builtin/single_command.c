/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:58:33 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 15:58:34 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_single_command_2(t_vars **vars, t_list *tokens, char ***cmd)
{
	int		status;

	signal(SIGINT, sig_handler);
	cmd[0][0] = ft_strdup("tmp");
	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ft_find_cmd(*vars, tokens->token, cmd, (*vars)->path);
	}
	else
	{
		wait(&status);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		g_g.ret = WEXITSTATUS(status);
	}
	destroy_tab(*cmd);
}

void	ft_single_command(t_vars **vars, t_list *tokens, char **cmd, int size)
{
	int		i;
	t_list	*temp;

	i = 1;
	temp = tokens;
	if (temp->next)
		temp = temp->next;
	if (size > 1)
	{
		while (temp && ft_is_key(temp->token) == 0)
		{
			cmd[i] = dupfree(temp->token, cmd[i]);
			temp = temp->next;
			i++;
		}
	}
	if (ft_strcmp(tokens->token, "./minishell") != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sig_handler);
	}
	ft_single_command_2(vars, tokens, &cmd);
}
