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

#include "../../includes/minishell.h"

void	ft_call_builtin_2(t_vars **vars, t_list *tokens)
{
	int	status;

	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		if (ft_strcmp(tokens->token, "echo") == 0 || ft_strcmp(tokens->token, "/bin/echo") == 0)
		{
			ft_call_echo(tokens);
			exit(0);
		}
		if (ft_strcmp(tokens->token, "env") == 0 || ft_strcmp(tokens->token, "/usr/bin/env") == 0)
			ft_call_env(vars, tokens);
		if (ft_strcmp(tokens->token, "export") == 0)
		{
			ft_export(tokens, &(*vars)->t_env, &(*vars)->t_exp);
//			exit(0);
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

void	ft_call_builtin(t_vars **vars, t_list *tokens)
{
	char	*user;
	t_sort	*temp;

	user = NULL;
	temp = (*vars)->t_env;
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
		ft_cd(vars, tokens, user);
		return ;
	}
	ft_call_builtin_2(vars, tokens);
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
		while (temp && ft_is_key(temp->token) == 0)
		{
			cmd[i] = temp->token;
			temp = temp->next;
			i++;
		}
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		signal(SIGQUIT, &sig_handler);
		signal(SIGINT, &sig_handler);
		ft_find_cmd(*vars, tokens->token, cmd, (*vars)->path);
	}
	wait(&status);
	g_g.ret = WEXITSTATUS(status);
}

void	ft_check_redir_2(t_vars **vars, t_list *temp)
{
	char	**cmd;
	t_list	*temp_2;
	int		file;

	temp_2 = (*vars)->tokens;
	file = 0;
	handle_redirs(*vars, temp, &file);
	while (temp_2)
	{
		if (ft_strcmp("|", temp_2->token) == 0)
		{
			ft_pipe(vars, (*vars)->store);
			if (close(file) != 0)
			{
				throw_error(NULL, errno);
				exit(errno);
			}
			exit(0);
		}
		if (temp_2)
			temp_2 = temp_2->next;
	}
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens);
	else if (is_special(temp) == TRUE && temp->next
	&& temp->next->next && ft_is_builtin((*vars)->tokens->next->next->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens->next->next);
	else if (is_special(temp) == TRUE && temp->next && temp->next->next)
		ft_single_command(vars, (*vars)->tokens->next->next, cmd, (*vars)->size);
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
	free(cmd);
	if (close(file) != 0)
	{
		printf("---------- ICI ---------\n");
		throw_error(NULL, errno);
		exit(errno);
	}
	exit(0);
}

int	ft_check_redir(t_vars **vars)
{
	int		status;
	int		ret;
	char	**cmd;
	t_list	*temp;

	(*vars)->size = 1;
	temp = (*vars)->tokens;
	cmd = NULL;
	ret = 0;
	while (temp->next)
	{
		if (is_special(temp) == TRUE && shall_exec(*vars, temp) == TRUE)
		{
			ret = 1;
			signal(SIGINT, SIG_IGN);
			g_g.pid = fork();
			signal(SIGINT, sig_handler);
			if (g_g.pid == 0)
				ft_check_redir_2(vars, temp);
			wait(&status);
			g_g.ret = WEXITSTATUS(status);
			signal(SIGINT, sig_handler);
		}
		temp = temp->next;
		(*vars)->size++;
	}
	return (ret);
}

void	ft_reset_var(t_vars **vars)
{
	char	*buf;
	t_sort	*temp_env;

	buf = NULL;
	temp_env = (*vars)->t_env;
	while (temp_env && ft_strcmp(temp_env->name, "PWD") != 0 && temp_env->next)
		temp_env = temp_env->next;
	temp_env->info = ft_strdup(getcwd(buf, sizeof(buf)));
	temp_env->data = (char *)malloc(sizeof(char) * ft_strlen(temp_env->info) + 6);
	if (!temp_env->data)
		return ;
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
}

int	call_command(t_vars **vars, int is_child)
{
	char	**cmd;
	t_list	*temp;

	ft_reset_var(vars);
	temp = (*vars)->tokens;
	(*vars)->size = 1;
	if (ft_check_redir(vars) == 1)
		return (0);
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
	(*vars)->size--;
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens);
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
	free(cmd);
	return (0);
}