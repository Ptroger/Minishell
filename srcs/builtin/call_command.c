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

void	ft_call_builtin_3(t_vars **vars, t_list *tokens)
{
	int	status;

	g_g.pid = fork();
	if (g_g.pid == 0)
	{
		if (ft_strcmp(tokens->token, "echo") == 0 || ft_strcmp(tokens->token, "/bin/echo") == 0)
			ft_call_echo(tokens);
		else if (ft_strcmp(tokens->token, "env") == 0 || ft_strcmp(tokens->token, "/usr/bin/env") == 0)
			ft_call_env(vars, tokens);
		else if (ft_strcmp(tokens->token, "pwd") == 0 || ft_strcmp(tokens->token, "/bin/pwd") == 0)
			ft_pwd(*vars, tokens);
		clean_exit(*vars, 0);
	}
	wait(&status);
	g_g.ret = WEXITSTATUS(status);
}

void	ft_call_builtin_2(t_vars **vars, t_list *tokens)
{
	if (ft_strcmp(tokens->token, "export") == 0)
	{
		ft_export(tokens, &(*vars)->t_env, &(*vars)->t_exp);
		return ;
	}
	else if (ft_strcmp(tokens->token, "unset") == 0 && tokens->next)
		ft_unset(tokens, &(*vars)->t_env, &(*vars)->t_exp);
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
	if (ft_strcmp(tokens->token, "cd") == 0 || ft_strcmp(tokens->token, "/usr/bin/cd") == 0)
	{
		ft_cd(vars, tokens, user);
		return ;
	}
	if (user)
		free(user);
	ft_call_builtin_2(vars, tokens);
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

void	ft_single_command_2(t_vars **vars, t_list *tokens, char ***cmd)
{
	int		status;
	
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
		g_g.ret =  WEXITSTATUS(status);
	}
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
			cmd[i] = temp->token;
			temp = temp->next;
			i++;
		}
	}
	if (ft_strcmp(tokens->token,"./minishell") != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sig_handler);
	}
	ft_single_command_2(vars, tokens, &cmd);
}

void	ft_check_redir_3(t_vars **vars, t_list *temp, int *file)
{
	char	**cmd;
	
	handle_redirs(*vars, temp, file);
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
		ft_call_builtin(vars, (*vars)->tokens);
	else if (is_special((*vars)->tokens) == TRUE && (*vars)->tokens->next
		&& (*vars)->tokens->next->next && ft_is_builtin((*vars)->tokens->next->next->token) == 1)
	{
		ft_call_builtin(vars, (*vars)->tokens->next->next);
		exit(g_g.ret);
	}
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);	
	free(cmd);
	if (close(*file) != 0)
	{
		throw_error(NULL, errno);
		clean_exit(*vars, errno);
	}
	clean_exit(*vars, 0);
}

void	ft_check_redir_2(t_vars **vars, t_list *temp)
{
	t_list	*temp_2;
	int		file;

	temp_2 = (*vars)->tokens;
	file = 0;
	while (temp_2)
	{
		if (ft_strcmp("|", temp_2->token) == 0)
		{
			ft_pipe(vars, (*vars)->store);
			if (close(file) != 0)
			{
				throw_error(NULL, errno);
				clean_exit(*vars, errno);
			}
			clean_exit(*vars, 0);
			return ;
		}
		temp_2 = temp_2->next;
	}
	handle_redirs(*vars, temp, &file);
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

void	ft_reset_var(t_vars **vars)
{
	t_sort	*temp_env;

	temp_env = (*vars)->t_env;
	while (temp_env && ft_strcmp(temp_env->name, "PWD") != 0 && temp_env->next)
		temp_env = temp_env->next;
	if (temp_env && temp_env->info)
		free(temp_env->info);
	temp_env->info = getcwd(NULL, 0);
	if (temp_env->data)
		free(temp_env->data);
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
	{
		if ((*vars)->path)
			destroy_tab((*vars)->path);
		(*vars)->path = ft_split(getenv("PATH"), ':');
	}
	else
		(*vars)->path = NULL;
}

int	call_command(t_vars **vars, int is_child)
{
	char	**cmd;
	t_list	*temp;
	t_list	*temp2;

	ft_reset_var(vars);
	temp = (*vars)->tokens;
	temp2 = (*vars)->tokens;
	(*vars)->size = 1;
	while (temp2)
		temp2 = temp2->next;
	if (ft_check_redir(vars) == TRUE)
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
	if (cmd)
		free(cmd);
	return (0);
}