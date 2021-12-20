/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:04:59 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:32:21 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_var_env(t_list *tokens, t_sort **t_env, t_sort **t_exp, int j)
{
	t_sort	*new_env;

	new_env = NULL;
	if ((tokens->next->token[j] == '=' || (tokens->next->token[j] == '+'
				&& tokens->next->token[j + 1] == '='))
		&& tokens->next->token[j - 1] != ' ')
	{
		new_env = ft_add_elem(tokens->next->token);
		if (!new_env)
			return ;
		add_back(t_env, new_env);
		ft_set_list_2(new_env);
	}
	if ((*t_exp)->data)
		free((*t_exp)->data);
	(*t_exp)->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (!(*t_exp)->data)
		return ;
	ft_fill_data(tokens, *t_exp);
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
	if ((tokens->next->token[j] == '=' || (tokens->next->token[j] == '+'
				&& tokens->next->token[j + 1] == '='))
		&& tokens->next->token[j - 1] != ' ')
	{
		new_env = ft_add_elem(tokens->next->token);
		add_back(t_env, new_env);
		if (!new_env)
			return ;
		ft_set_list_2(new_env);
	}
	new_exp->data = malloc(sizeof(char) * ft_strlen(tokens->next->token) + 3);
	if (!new_exp->data)
		return ;
	ft_fill_data(tokens, new_exp);
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

void	ft_parse_exp(t_list *tokens, t_sort **t_env, t_sort **t_exp, char *tmp)
{
	int		i;

	i = 0;
	if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
	{
		while (tmp[i] != '=' && tmp[i])
		{
			if (((!ft_isalnum(tmp[i])) && tmp[i] != '_')
				&& (tmp[i] == '+' && tmp[i + 1] != '='))
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
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0
		&& is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0
			&& is_special(temp->next) == FALSE)
		{
			tmp = ft_strdup(temp->next->token);
			ft_parse_exp(temp, t_env, t_exp, tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
	else
		ft_display_exp(t_exp);
}
