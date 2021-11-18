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

void	ft_call_builtin(t_vars **vars)
{
	if (ft_strcmp((*vars)->tokens->token, "cd") == 0)
		ft_cd((*vars)->tokens->next->token);
	if (ft_strcmp((*vars)->tokens->token, "echo") == 0)
	{
        if (!(*vars)->tokens->next)
            ft_putstr("\n");
		else if (ft_strcmp((*vars)->tokens->next->token, "-n") == 0)
            ft_echo_n((*vars)->tokens->next->next);
		else
            ft_echo((*vars)->tokens->next);
	}
	if (ft_strcmp((*vars)->tokens->token, "env") == 0)
		ft_env(&(*vars)->t_env);
	if (ft_strcmp((*vars)->tokens->token, "exit") == 0)
		exit(1);
	if (ft_strcmp((*vars)->tokens->token, "export") == 0)
		ft_export((*vars)->tokens, &(*vars)->t_env, &(*vars)->t_exp);
	if (ft_strcmp((*vars)->tokens->token, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp((*vars)->tokens->token, "unset") == 0 && (*vars)->tokens->next)
		ft_unset((*vars)->tokens, &(*vars)->t_env, &(*vars)->t_exp);
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

void	ft_single_command(t_vars **vars, t_list *tokens, char **cmd, int size)
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
		ft_find_cmd(vars, tokens->token, cmd, (*vars)->path);
}

int	call_command(t_vars **vars, int is_child)
{
	char	**cmd;
	t_list	*temp;
	pid_t	child;

	(*vars)->path = ft_split(getenv("PATH"), ':');
	temp = (*vars)->tokens;
	(*vars)->size = 1;
	child = 0;
	if (is_child == FALSE)
	{
		while (temp->next)
		{
			if (ft_strcmp("|", temp->token) == 0)
			{
				return (ft_pipe(vars, (*vars)->store));
	//			printf("temp->token = %s\n", temp->token);
	//			return (handle_redirs(vars, temp, (*vars)->store));
			}
			temp = temp->next;
			(*vars)->size++;
		}
	}
	temp = (*vars)->tokens;
	while (temp->next)
	{
		if (ft_strcmp(">", temp->token) == 0 || ft_strcmp("<", temp->token) == 0)
		{
			child = fork();
			if (child == 0)
			{
				handle_redirs(vars, temp, (*vars)->store);
				cmd = ft_command_size((*vars)->size);
				if (ft_is_builtin((*vars)->tokens->token) == 1)
					ft_call_builtin(vars);
				else
					ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
				free(cmd);
				exit(1);
				return (1);
			}
		}
		temp = temp->next;
		(*vars)->size++;
	}
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars);
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
	free(cmd);
	return (0);
}
