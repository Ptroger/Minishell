/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 20:12:31 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 09:36:45 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_oldpwd(t_vars **vars, char *wd)
{
	t_sort	*temp;
	
	temp = (*vars)->t_env;
	while (temp && ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	temp->info = ft_strdup(wd);
	temp->data = ft_strdup("OLDPWD");
	temp->data = ft_strjoin(temp->data, "=");
	temp->data = ft_strjoin(temp->data, temp->info);
}

void	ft_is_dash(t_vars **vars)
{
	t_sort	*temp;
	char	*old_pwd;

	temp = (*vars)->t_env;
	old_pwd = NULL;
	while (temp && ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	if (ft_strcmp(temp->name, "OLDPWD") == 0)
	{
		old_pwd = ft_strdup(temp->info);
		printf("%s\n", old_pwd);
		chdir(old_pwd);
	}
}

int	ft_cd(t_vars **vars, t_list *tokens, char *user)
{
	char	*buf;
	char	*wd;
	int		ret;

	buf = NULL;
	wd = ft_strdup(getcwd(buf, sizeof(buf)));
	if (!tokens->next || ft_strcmp(tokens->next->token, "~") == 0)
		chdir(user);
	else if (ft_strcmp(tokens->next->token, "-") == 0)
		ft_is_dash(vars);
	else if (chdir(tokens->next->token) != -1)
		ret = 1;
	else
		ret = 0;
	ft_set_oldpwd(vars, wd);
	return (0);
}
