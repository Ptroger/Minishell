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
	(void)tokens;
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
	int		i;
	int		j;
	char	*tmp;
	t_sort	*new_exp;
	t_sort	*new_env;
	t_sort	*temp_env;
	t_sort	*temp_exp;

	i = 0;
	j = 0;
	new_exp = NULL;
	temp_env = *t_env;
	temp_exp = *t_exp;
	while (tokens->next->token[j] && tokens->next->token[j] != '=')
		j++;
	tmp = (char *)malloc(sizeof(char) * j + 1);
	if (!tmp)
		return ;
	while (i < j)
	{
		tmp[i] = tokens->next->token[i];
		i++;
	}
	tmp[i] = '\0';
	while (temp_env && ft_strcmp(temp_env->name, tmp) != 0)
		temp_env = temp_env->next;
	while (temp_exp && ft_strncmp(temp_exp->data, tmp, j) != 0)
		temp_exp = temp_exp->next;
	if (temp_env && temp_env->name && ft_strcmp(temp_env->name, tmp) == 0)
	{
		if (temp_env->data)
			free(temp_env->data);
		if (temp_env->name)
			free(temp_env->name);
		if (temp_env->info)
			free(temp_env->info);
		temp_env->data = ft_strdup(tokens->next->token);
		if (temp_exp && temp_exp->name && ft_strcmp(temp_exp->name, tmp) == 0)
		{
			if (temp_exp->data)
				free(temp_exp->data);
			temp_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
		}
		ft_set_list_2(tokens, temp_env, temp_exp);
		ft_fill_data(tokens, temp_exp);
	}
	else
	{
		new_exp = ft_add_elem(NULL);
		add_back(t_exp, new_exp);
		if (!new_exp)
			return ;
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
	free(tmp);
}

void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	char	*tmp;
	t_list	*temp;

	tmp = NULL;
	temp = tokens;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0 && is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0 && is_special(temp->next) == FALSE)
		{
			tmp = ft_strdup(temp->next->token);
			if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
				ft_set_list(temp, t_env, t_exp);
			else
				printf("minishell: export: `%s': not a valid identifier\n", tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
	else
		ft_display_exp(t_exp);
}
