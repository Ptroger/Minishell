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
	char	*tem;
	
	temp = (*vars)->t_env;
	while (temp && ft_strcmp(temp->name, "OLDPWD") != 0)
		temp = temp->next;
	if (temp->info)
		free(temp->info);
	temp->info = wd;
	if (temp->data)
		free(temp->data);
	temp->data = ft_strdup("OLDPWD");
	tem = temp->data;
	temp->data = ft_strjoin(temp->data, "=");
	free(tem);
	tem = temp->data;
	temp->data = ft_strjoin(temp->data, temp->info);
	free(tem);
}

int	ft_is_dash(t_vars **vars)
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
		return (chdir(old_pwd));
	}
	return (0);
}

int	ft_cd(t_vars **vars, t_list *tokens, char *user)
{
	char	*buf;
	char	*wd;
	int		ret;

	buf = NULL;
	wd = getcwd(buf, sizeof(buf));
	if (!tokens->next || ft_strcmp(tokens->next->token, "~") == 0)
	{
		ret = chdir(user);
	}
	else if (ft_strcmp(tokens->next->token, "-") == 0)
		ret = ft_is_dash(vars);
	else
		ret = chdir(tokens->next->token);
	ft_set_oldpwd(vars, wd);
	if (ret != 0)
		throw_error(NULL, errno);
	free(user);	
	return (0);
}
