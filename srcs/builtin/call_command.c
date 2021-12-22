/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:23:57 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:09:03 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_reset_var_2(t_vars **vars, t_sort *temp_env)
{
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
	temp_env->data = (char *)malloc(sizeof(char)
			* ft_strlen(temp_env->info) + 6);
	if (!temp_env->data)
		return ;
	ft_reset_var_2(vars, temp_env);
}

void	ft_call_command_2(t_vars **vars)
{
	char	**cmd;

	(*vars)->size--;
	cmd = ft_command_size((*vars)->size);
	if (ft_is_builtin((*vars)->tokens->token) == 1)
	{
		ft_call_builtin(vars, (*vars)->tokens);
		destroy_tab(cmd);
	}
	else
		ft_single_command(vars, (*vars)->tokens, cmd, (*vars)->size);
}

int	call_command(t_vars **vars, int is_child)
{
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
				return (ft_pipe(vars));			
			if (temp)
				temp = temp->next;
			(*vars)->size++;
		}
	}
	ft_call_command_2(vars);
	return (0);
}
