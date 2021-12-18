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
	if (tokens->next->token[j] == '=')
	{
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
	}
	else
		new_exp->data[i] = '\0';
	new_exp->next = NULL;
}

void	ft_set_list_2(t_list *tokens, t_sort *new_env, t_sort *new_exp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)new_exp;
//	new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
//	if (!new_exp->data)
//		return ;
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
	int		j;
	t_sort	*new_exp;
	t_sort	*new_env;

	j = 0;
	new_exp = ft_add_elem(NULL);
	add_back(t_exp, new_exp);
	if (!new_exp)
		return ;
	while (tokens->next->token[j] && tokens->next->token[j] != '=')
		j++;
	if (tokens->next->token[j] == '=' && tokens->next->token[j - 1] != ' ')
	{
		new_env = ft_add_elem(tokens->next->token);
		if (!new_env)
			return ;
		add_back(t_env, new_env);
		ft_set_list_2(tokens, new_env, new_exp);
	}
	else
		new_env = NULL;
	new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (!new_exp->data)
		return ;
	ft_fill_data(tokens, new_exp);
}

void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	t_list	*temp;

	temp = tokens;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0 && is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0 && is_special(temp->next) == FALSE)
		{
			ft_set_list(temp, t_env, t_exp);
			temp = temp->next;
		}
//		while (tokens->next->token[j] && tokens->next->token[j] != '=')
//			j++;
//		if (tokens->next->token[j] == '=' && tokens->next->token[j - 1] != ' ')
//			ft_set_list(tokens, t_env, t_exp);
	}
	else
		ft_display_exp(t_exp);
}
