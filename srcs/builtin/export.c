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
	while (tokens->next->token[j] && tokens->next->token[j] != '+' && tokens->next->token[j] != '=')
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

void	ft_set_list_3(t_sort *new_env, int i, int j, int tmp)
{
	while (new_env->data[i])
	{
		new_env->info[j] = new_env->data[i];
		i++;
		j++;
	}
	new_env->info[j] = '\0';
	new_env->next = NULL;
	if (tmp == 1)
	{
		free(new_env->data);
		new_env->data = ft_strjoin(new_env->name, "=");
		new_env->data = ft_strjoin(new_env->data, new_env->info);
	}
}

void	ft_set_list_2(t_sort *new_env)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	j = 0;
	tmp = 0;
	new_env->name = malloc(sizeof(char) * ft_strlen(new_env->data));
	new_env->info = malloc(sizeof(char) * ft_strlen(new_env->data));
	if (!new_env->name)
		return ;
	while (new_env->data[i] != '+' && new_env->data[i] != '=')
	{
		new_env->name[i] = new_env->data[i];
		i++;
	}
	new_env->name[i] = '\0';
	if (new_env->data[i] == '+' && new_env->data[i + 1] == '=')
	{
		tmp++;
		i++;
	}
	i++;
	ft_set_list_3(new_env, i, j, tmp);
}

void	ft_new_var(t_list *tokens, t_sort **t_env, t_sort **t_exp, int j)
{
	t_sort	*new_exp;
	t_sort	*new_env;

	new_env = NULL;
	new_exp = ft_add_elem(NULL);
	add_back(t_exp, new_exp);
	if (!new_exp)
		return ;
	if ((tokens->next->token[j] == '=' || (tokens->next->token[j] == '+' && tokens->next->token[j + 1] == '=')) && tokens->next->token[j - 1] != ' ')
	{
		new_env = ft_add_elem(tokens->next->token);
		if (!new_env)
			return ;
		add_back(t_env, new_env);
		ft_set_list_2(new_env);
	}
	new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (!new_exp->data)
		return ;
	ft_fill_data(tokens, new_exp);
}

void	ft_update_var_2(t_list *tokens, t_sort *temp_env, t_sort *temp_exp, t_sort *temp_env_2)
{
	int		j;
	t_sort	*temp_exp_2;
	
	j = 0;
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
		j++;
	temp_exp_2 = malloc(sizeof(t_sort));
	temp_env->data = ft_strdup(tokens->next->token);
	if (temp_exp && ft_strncmp(temp_exp->data, temp_exp->info, j) == 0)
	{
		if (temp_exp->data)
		{
			if (tokens->next->token[j] == '+')
				temp_exp_2->data = ft_strdup(temp_exp->data);
			free(temp_exp->data);
		}
		temp_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	}
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
//		ft_fill_data(tokens, temp_exp);
//		ft_set_list_2(tokens, &temp_env_2, temp_exp);
}

void	ft_set_temp(t_list *tokens, char **env, char **tmp, int j)
{
	if (*env)
	{
		if (tokens->next->token[j] == '+')
			*tmp = ft_strdup(*env);
		free(*env);
	}
}

void	ft_udpate_var(t_list *tokens, t_sort *temp_env, t_sort *temp_exp, char *tmp)
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
	temp_exp->info = ft_strdup(tmp);
	ft_update_var_2(tokens, temp_env, temp_exp, temp_env_2);
}

void	ft_set_list(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	int		i;
	int		j;
	char	*tmp;
	t_sort	*temp_env;
	t_sort	*temp_exp;
	
	i = 0;
	j = 0;
	temp_env = *t_env;
	temp_exp = *t_exp;
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
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
		ft_udpate_var(tokens, temp_env, temp_exp, tmp);
	else
		ft_new_var(tokens, t_env, t_exp, j);
	free(tmp);
}

void	ft_parse_export(t_list *tokens, t_sort **t_env, t_sort **t_exp, char *tmp)
{
	int		i;

	i = 0;
	if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
	{
		while (tmp[i] != '=' && tmp[i])
		{
			if (((!ft_isalnum(tmp[i])) && tmp[i] != '_') && (tmp[i] == '+' && tmp[i + 1] != '='))
			{
				printf("minishell: export: `%s': not a valid identifier\n", tmp);
				return ;
			}
			i++;
		}
		ft_set_list(tokens, t_env, t_exp);
	}
	else
		printf("minishell: export: `%s': not a valid identifier\n", tmp);
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
			ft_parse_export(temp, t_env, t_exp, tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
	else
		ft_display_exp(t_exp);
}
