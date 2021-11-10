/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:23:57 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/09 17:00:41 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_builtin(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	if (ft_strcmp(tokens->token, "cd") == 0)
		ft_cd(tokens->next->token);
	if (ft_strcmp(tokens->token, "echo") == 0)
	{
		if (ft_strcmp(tokens->next->token, "-n") == 0)
			ft_echo_n(tokens->next->next->token);
		else
			ft_echo(tokens->next->token);
	}
	if (ft_strcmp(tokens->token, "env") == 0)
		ft_env(t_env);
	if (ft_strcmp(tokens->token, "exit") == 0)
		exit(1);
	if (ft_strcmp(tokens->token, "export") == 0)
		ft_export(tokens, t_env, t_exp);
	if (ft_strcmp(tokens->token, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(tokens->token, "unset") == 0 && tokens->next)
		ft_unset(tokens, t_env, t_exp);
}

int	ft_is_builtin(char *token)
{
	if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "echo") == 0
		|| ft_strcmp(token, "env") == 0 || ft_strcmp(token, "exit") == 0
		|| ft_strcmp(token, "export") == 0 || ft_strcmp(token, "pwd") == 0
		|| ft_strcmp(token, "unset") == 0)
		return (1);
	return (0);
}

void	ft_single_command(t_list *tokens, char **cmd, char **tab, int size)
{
	int		i;
	pid_t	pid;
	t_list	*temp;

	i = 1;
	temp = tokens;
	if (temp->next)
		temp = temp->next;
	if (size > 1)
	{
		while (temp)
		{
			cmd[i] = temp->token;
			temp = temp->next;
			i++;
		}
	}
	pid = fork();
	wait(NULL);
	if (pid == 0)
		ft_find_cmd(tokens->token, cmd, tab);
}

int	call_command(t_list *tokens, t_sort **t_env, t_sort **t_exp, t_pipe *store)
{
	int		size;
	char	**cmd;
	char	**tab;
	t_list	*temp;

	size = 1;
	tab = ft_split(getenv("PATH"), ':');
	temp = tokens;
	while (temp->next)
	{
		if (ft_strcmp(temp->token, "|") == 0)
			return (ft_pipe(tokens, store, tab));
		temp = temp->next;
		size++;
	}
	cmd = ft_command_size(size);
	if (ft_is_builtin(tokens->token) == 1)
		ft_call_builtin(tokens, t_env, t_exp);
	else
		ft_single_command(tokens, cmd, tab, size);
	return (0);
}
