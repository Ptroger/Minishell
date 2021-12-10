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

void	ft_call_builtin(t_vars **vars, t_list *tokens)
{
	int		ret;
	char	*buf;
	char	*wd;
	char	*user;
	char	*pwd;
	char	*old_pwd;
	int		status;
	t_sort	*temp;
	t_sort	*temp_env;

	ret = 0;
	user = NULL;
	pwd = NULL;
	old_pwd = NULL;
	buf = NULL;
	wd = NULL;
	temp = (*vars)->t_env;
	temp_env = (*vars)->t_env;
	if (ft_strcmp(tokens->token, "exit") == 0)
	{
		printf("exit\n");
		exit(0);
	}
	while (temp && ft_strcmp(temp->name, "USER") != 0)
		temp = temp->next;
	if (ft_strcmp(temp->name, "USER") == 0)
	{
		user = (char *)malloc(sizeof(char) * ft_strlen(temp->info) + 8);
		user = ft_strcpy(user, "/Users/");
		user = ft_strcat(user, temp->info);
	}
	if (ft_strcmp(tokens->token, "cd") == 0 || ft_strcmp(tokens->token, "/usr/bin/cd") == 0)
	{
		buf = NULL;
		wd = ft_strdup(getcwd(buf, sizeof(buf)));
		if (!tokens->next || ft_strcmp(tokens->next->token, "~") == 0)
			ft_cd(user);
		else if (ft_strcmp(tokens->next->token, "-") == 0)
		{
			while (temp && ft_strcmp(temp->name, "OLDPWD") != 0)
				temp = temp->next;
			if (ft_strcmp(temp->name, "OLDPWD") == 0)
			{
				old_pwd = ft_strdup(temp->info);
				printf("%s\n", old_pwd);
				ft_cd(old_pwd);
			}
		}
		else if (ft_cd(tokens->next->token) == -1)
			ret = errno;
		while (temp_env && ft_strcmp(temp_env->name, "OLDPWD") != 0)
			temp_env = temp_env->next;
		temp_env->info = ft_strdup(wd);
		temp_env->data = (char *)malloc(sizeof(char) * ft_strlen(temp_env->info) + 6);
		if (!temp_env->data)
			return ;
		temp_env->data = ft_strcpy(temp_env->data, "OLDPWD");
		temp_env->data = ft_strcat(temp_env->data, "=");
		temp_env->data = ft_strcat(temp_env->data, temp_env->info);
		return ;
	}
	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		temp = (*vars)->t_env;
		if (ft_strcmp(tokens->token, "echo") == 0 || ft_strcmp(tokens->token, "/bin/echo") == 0)
		{
			if (!tokens->next)
				ft_putstr("\n");
			else if (ft_strcmp(tokens->next->token, "-n") == 0)
				ft_echo_n(tokens->next->next);
			else
				ft_echo(tokens->next);
			exit(0);
		}
		if (ft_strcmp(tokens->token, "env") == 0 || ft_strcmp(tokens->token, "/usr/bin/env") == 0)
		{
			if (tokens->next && (ft_strcmp(tokens->next->token, "yes") == 0 || ft_strcmp(tokens->next->token, "YES") == 0))
			{
				while (1)
					printf("y\n");
				exit (0);
			}
			if (tokens->next && ft_is_key(tokens->next->token) == 0)
			{
				printf("env: %s: No such file or directory\n", tokens->next->token);
				exit(127);
			}
			else
			{
				ft_env(&(*vars)->t_env);
				exit(0);
			}
		}
		if (ft_strcmp(tokens->token, "export") == 0)
		{
			ft_export(tokens, &(*vars)->t_env, &(*vars)->t_exp);
			exit(0);
		}
		if (ft_strcmp(tokens->token, "pwd") == 0 || ft_strcmp(tokens->token, "/bin/pwd") == 0)
		{
			ft_pwd();
			exit(0);
		}
		if (ft_strcmp(tokens->token, "unset") == 0 && tokens->next)
		{
			ft_unset(tokens, &(*vars)->t_env, &(*vars)->t_exp);
			exit(0);
		}
	}
	wait(&status);
	g_g.ret = WEXITSTATUS(status);
}

int	ft_is_builtin(char *token)
{
	if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "/usr/bin/cd") == 0 || ft_strcmp(token, "echo") == 0 || ft_strcmp(token, "/bin/echo") == 0
		|| ft_strcmp(token, "env") == 0 || ft_strcmp(token, "/usr/bin/env") == 0 || ft_strcmp(token, "exit") == 0
		|| ft_strcmp(token, "export") == 0 || ft_strcmp(token, "pwd") == 0 || ft_strcmp(token, "/bin/pwd") == 0
		|| ft_strcmp(token, "unset") == 0)
		return (1);
	return (0);
}

void	ft_single_command(t_vars **vars, t_list *tokens, char **cmd, int size)
{
	int		i;
	int		status;
	t_list	*temp;

	i = 1;
	temp = tokens;
	if (temp->next)
		temp = temp->next;
	if (size > 1)
	{
		while (temp && is_special(temp) == FALSE)
		{
			cmd[i] = temp->token;
			temp = temp->next;
			i++;
		}
	}
	g_g.pid = fork();
	if (g_g.pid == 0)
	{
 		signal(SIGQUIT, &sig_handler);
		ft_find_cmd(tokens->token, cmd, (*vars)->path);
	}
	wait(&status);
	g_g.ret = WEXITSTATUS(status);
}

int	call_command(t_vars **vars, int is_child)
{
	char	*buf;
	int		file;
	int		status;
	char	**cmd;
	t_list	*temp;
	t_sort	*temp_env;

	buf = NULL;
	temp_env = (*vars)->t_env;
	while (temp_env && ft_strcmp(temp_env->name, "PWD") != 0 && temp_env->next)
		temp_env = temp_env->next;
	temp_env->info = ft_strdup(getcwd(buf, sizeof(buf)));
	temp_env->data = (char *)malloc(sizeof(char) * ft_strlen(temp_env->info) + 6);
	if (!temp_env->data)
		return (-1);
	temp_env->data = ft_strcpy(temp_env->data, "PWD");
	temp_env->data = ft_strcat(temp_env->data, "=");
	temp_env->data = ft_strcat(temp_env->data, temp_env->info);
	temp_env = (*vars)->t_env;
	while (temp_env && ft_strcmp(temp_env->name, "PATH") != 0)
		temp_env = temp_env->next;
	if (temp_env && ft_strcmp(temp_env->name, "PATH") == 0)
		(*vars)->path = ft_split(getenv("PATH"), ':');
	else
		(*vars)->path = NULL;
	temp = (*vars)->tokens;
	(*vars)->size = 1;
	file = 0;
	if (is_child == FALSE)
	{
		while (temp)
		{
			if (ft_strcmp("|", temp->token) == 0)
				return (ft_pipe(vars, (*vars)->store));
			if (temp)
				temp = temp->next;
			(*vars)->size++;
		}
	}
	(*vars)->size = 1;
	temp = (*vars)->tokens;
	while (temp->next)
	{
		if (is_special(temp) == TRUE)
		{
			g_g.pid = fork();
			if (g_g.pid == 0)
			{
				handle_redirs(*vars, temp, &file);
				cmd = ft_command_size((*vars)->size);
				if (ft_is_builtin((*vars)->tokens->token) == 1)
					ft_call_builtin(vars, (*vars)->tokens);
				else if (is_special(*vars, temp) == TRUE && temp->next && temp->next->next && ft_is_builtin((*vars)->tokens->next->next->token) == 1)
					ft_call_builtin(vars, (*vars)->tokens->next->next);
				else if (is_special(*vars, temp) == TRUE && temp->next && temp->next->next) 
					ft_single_command(vars, (*vars)->tokens->next->next, cmd, (*vars)->size);
				else
					ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
				free(cmd);
				close(file);
				exit(1);
			}
			wait(&status);
			signal(SIGINT, sig_handler);
			return (1);
		}
		temp = temp->next;
		(*vars)->size++;
	}
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens);
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
	free(cmd);
	return (0);
}
