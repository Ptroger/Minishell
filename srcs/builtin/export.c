/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:04:59 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 11:48:42 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_exp(t_sort **t_exp)
{
	t_sort	*temp_exp;

	temp_exp = *t_exp;
	while (temp_exp->next)
	{
		printf("%s", "declare -x ");
		if (temp_exp->data[0] == '_' && temp_exp->data[1] == '='
			&& temp_exp->data[2] == '/')
			temp_exp = temp_exp->next;
		printf("%s\n", temp_exp->data);
		temp_exp = temp_exp->next;
	}
	printf("%s", "declare -x ");
	printf("%s\n", temp_exp->data);
}

void	ft_fill_data(t_list *tokens, t_sort *new_exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tokens->next->token[j] && tokens->next->token[j] != '=')
	{
		new_exp->data[i] = tokens->next->token[j];
		i++;
		j++;
	}
	new_exp->data[i] = tokens->next->token[j];
	i++;
	j++;
	new_exp->data[i] = '"';
	i++;
	while (tokens->next->token[j])
	{
		new_exp->data[i] = tokens->next->token[j];
		i++;
		j++;
	}
	new_exp->data[i] = '"';
	new_exp->data[i + 1] = '\0';
	printf("token : %s\n", new_exp->data);
	new_exp->next = NULL;
}

void	ft_set_list_2(t_list *tokens, t_sort *new_env, t_sort *new_exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (!new_exp->data)
		return ;
	new_env->data = ft_strdup(tokens->next->token);
	new_env->name = malloc(sizeof(char) * ft_strlen(new_env->data));
	new_env->info = malloc(sizeof(char) * ft_strlen(new_env->data));
	if (!new_env->name)
		return ;
	while (new_env->data[i] != '=')
	{
		new_env->name[i] = new_env->data[i];
		i++;
	}
	new_env->name[i] = '\0';
	i++;
	while (new_env->data[i])
	{
		new_env->info[j] = new_env->data[i];
		i++;
		j++;
	}
	new_env->info[j] = '\0';
	new_env->next = NULL;
}

void	ft_set_list(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	t_sort	*new_exp;
	t_sort	*new_env;
	t_sort	*temp_exp;
	t_sort	*temp_env;

	temp_exp = *t_exp;
	temp_env = *t_env;
	new_exp = malloc(sizeof(t_sort));
	if (!new_exp)
		return ;
	new_env = malloc(sizeof(t_sort));
	if (!new_env)
		return ;
	while (temp_exp->next)
		temp_exp = temp_exp->next;
	while (temp_env->next)
		temp_env = temp_env->next;
	temp_exp->next = new_exp;
	temp_env->next = new_env;
	ft_set_list_2(tokens, new_env, new_exp);
	ft_fill_data(tokens, new_exp);
}

void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	int		j;

	j = 0;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0)
	{
		while (tokens->next->token[j] && tokens->next->token[j] != '=')
			j++;
		if (tokens->next->token[j] == '=' && tokens->next->token[j - 1] != ' ')
			ft_set_list(tokens, t_env, t_exp);
	}
	else
		ft_display_exp(t_exp);
}