/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:56:30 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 15:56:31 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_builtin_3(t_vars **vars, t_list *tokens)
{
	int	status;

	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		if (ft_strcmp(tokens->token, "echo") == 0
			|| ft_strcmp(tokens->token, "/bin/echo") == 0)
			ft_call_echo(tokens);
		else if (ft_strcmp(tokens->token, "pwd") == 0
			|| ft_strcmp(tokens->token, "/bin/pwd") == 0)
			ft_pwd(*vars, tokens);
		clean_exit(*vars, 0);
	}
	wait(&status);
	g_g.ret = WEXITSTATUS(status);
}

int	ft_call_builtin_2(t_vars **vars, t_list *tokens)
{
	if (ft_strcmp(tokens->token, "export") == 0)
	{
		ft_export(tokens, &(*vars)->t_env, &(*vars)->t_exp);
		return (1) ;
	}
	else if (ft_strcmp(tokens->token, "unset") == 0)
	{
		if (tokens->next)
			ft_unset(tokens, &(*vars)->t_env, &(*vars)->t_exp);
		return (1);
	}
	else if (ft_strcmp(tokens->token, "env") == 0
		|| ft_strcmp(tokens->token, "/usr/bin/env") == 0)
	{
		ft_call_env(vars, tokens);
		return (1);
	}
	return (0);
}

void	ft_call_builtin(t_vars **vars, t_list *tokens)
{
	char	*user;
	t_sort	*temp;

	user = NULL;
	temp = (*vars)->t_env;
	if (ft_strcmp(tokens->token, "exit") == 0)
		ft_exit(*vars, tokens);
	while (temp && ft_strcmp(temp->name, "USER") != 0)
		temp = temp->next;
	if (ft_strcmp(temp->name, "USER") == 0)
	{
		user = (char *)malloc(sizeof(char) * ft_strlen(temp->info) + 8);
		user = ft_strcpy(user, "/Users/");
		user = ft_strcat(user, temp->info);
	}
	if (ft_strcmp(tokens->token, "cd") == 0
		|| ft_strcmp(tokens->token, "/usr/bin/cd") == 0)
	{
		ft_cd(vars, tokens, user);
		return ;
	}
	if (user)
		free(user);
	if (ft_call_builtin_2(vars, tokens) == 0)
		ft_call_builtin_3(vars, tokens);
}

int	ft_is_builtin(char *token)
{
	if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "/usr/bin/cd") == 0
		|| ft_strcmp(token, "echo") == 0 || ft_strcmp(token, "/bin/echo") == 0
		|| ft_strcmp(token, "env") == 0 || ft_strcmp(token, "/usr/bin/env") == 0
		|| ft_strcmp(token, "exit") == 0 || ft_strcmp(token, "export") == 0
		|| ft_strcmp(token, "pwd") == 0 || ft_strcmp(token, "/bin/pwd") == 0
		|| ft_strcmp(token, "unset") == 0)
		return (1);
	return (0);
}
