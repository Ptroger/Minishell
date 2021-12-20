/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:56:57 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 14:56:58 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_data(t_list *tokens, t_sort *new_exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens->next->token[j] && tokens->next->token[j] != '+'
        && tokens->next->token[j] != '=')
		new_exp->data[i++] = tokens->next->token[j++];
	if (tokens->next->token[j] == '=' || tokens->next->token[j] == '+')
	{
		if (tokens->next->token[j] == '+')
			j++;
		new_exp->data[i] = tokens->next->token[j];
		i++;
		j++;
		new_exp->data[i] = '"';
		i++;
		while (tokens->next->token[j])
			new_exp->data[i++] = tokens->next->token[j++];
		new_exp->data[i] = '"';
		new_exp->data[i + 1] = '\0';
	}
	else
		new_exp->data[i] = '\0';
	new_exp->next = NULL;
}

void	ft_update_var_3(t_list *tokens, t_sort *temp_env, t_sort *temp_exp, t_sort *temp_exp_2)
{
	int		j;
	t_sort	*temp_env_2;

	j = 0;
	temp_env_2 = malloc(sizeof(t_sort));
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
		j++;
	ft_set_temp(tokens, &temp_env->data, &temp_env_2->data, j);
	ft_set_temp(tokens, &temp_env->name, &temp_env_2->name, j);
	ft_set_temp(tokens, &temp_env->info, &temp_env_2->info, j);
	temp_env->data = ft_strdup(tokens->next->token);
	ft_set_list_2(temp_env);
	if (tokens->next->token[j] == '+')
		temp_env->data = ft_strjoin(temp_env_2->data, temp_env->info);
	ft_fill_data(tokens, temp_exp);
	if (tokens->next->token[j] == '+')
	{
		temp_exp_2->data[ft_strlen(temp_exp_2->data) - 1] = '\0';
		temp_exp->data = ft_strjoin(temp_exp_2->data, temp_env->info);
		temp_exp->data = ft_strjoin(temp_exp->data, "\"");
		ft_set_list_2(temp_env);
	}
}

void	ft_update_var_2(t_list *tokens, t_sort **t_env, t_sort *temp_env, t_sort *temp_exp)
{
	int		j;
	t_sort	*temp_exp_2;

	j = 0;
	temp_exp_2 = malloc(sizeof(t_sort));
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
		j++;
	if (!(temp_env && temp_env->name && ft_strcmp(temp_env->name, temp_exp->name) == 0))
	{
		ft_new_var_env(tokens, t_env, &temp_exp, j);
		return ;
	}
	if (temp_exp->data)
	{
		if (tokens->next->token[j] == '+')
			temp_exp_2->data = ft_strdup(temp_exp->data);
		free(temp_exp->data);
	}
	temp_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (temp_env && temp_env->name && ft_strcmp(temp_env->name, temp_exp->name) == 0)
		ft_update_var_3(tokens, temp_env, temp_exp, temp_exp_2);
}

void	ft_update_var(t_list *tokens, t_sort **t_env, t_sort **t_exp, t_sort *temp_env, t_sort *temp_exp)
{
	int		j;

	j = 0;
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
		j++;
	if (temp_exp && ft_strncmp(temp_exp->data, temp_exp->name, j) == 0)
	{
		if (tokens->next->token[j] != '+' && tokens->next->token[j] != '=')
			return ;
		ft_update_var_2(tokens, t_env, temp_env, temp_exp);
	}
	else
		ft_new_var(tokens, t_env, t_exp, j);
}

void	ft_browse_env(t_list *tokens, t_sort **t_env, t_sort **t_exp, char *tmp)
{
	int		j;
	t_sort	*temp_env;
	t_sort	*temp_exp;

	j = 0;
	temp_env = *t_env;
	temp_exp = *t_exp;
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
		j++;
	while (temp_env && ft_strcmp(temp_env->name, tmp) != 0)
		temp_env = temp_env->next;
	while (temp_exp && ft_strncmp(temp_exp->data, tmp, j) != 0)
		temp_exp = temp_exp->next;
	if (temp_exp && temp_exp->name)
		free(temp_exp->name);
	if (temp_exp)
		temp_exp->name = ft_strdup(tmp);
	ft_update_var(tokens, t_env, t_exp, temp_env, temp_exp);
}