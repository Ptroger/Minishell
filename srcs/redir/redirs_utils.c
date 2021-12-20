/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:04:14 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:04:16 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_err(t_vars *vars, t_list *tokens)
{
	ft_putstr_fd(tokens->next->token, STDERR_FILENO);
	write(2, ": ", 2);
	throw_error(NULL, errno);
	clean_exit(vars, 1);
}

void	redir_temp(t_vars *vars, t_list *tokens, char *name, int *file)
{
	*file = open(name, O_RDONLY);
	if (*file == -1)
		open_err(vars, tokens);
	dup2(*file, STDIN_FILENO);
	while (tokens)
	{
		if (tokens->type == R_IN)
			redirect_input(vars, tokens);
		if (tokens->type == R_OUT)
			redirect_output(vars, tokens, tokens->token);
		tokens = tokens->next;
	}
}

void	redirect_input(t_vars *vars, t_list *tokens)
{
	while (tokens)
	{
		if (tokens->type == R_OUT)
			redirect_output(vars, tokens, tokens->token);
		if (tokens->type == R_IN)
		{
			if (!tokens->next)
			{
				throw_error("syntax error near unexpected token 'newline'", 1);
				clean_exit(vars, 1);
			}
			if (vars->stdin > -1)
				close(vars->stdout);
			vars->stdin = open(tokens->next->token, O_RDONLY);
			if (vars->stdout == -1)
				open_err(vars, tokens);
		}
		tokens = tokens->next;
	}
	dup2(vars->stdin, STDIN_FILENO);
}

void	handle_token(t_vars *vars, t_list *tokens, char *token)
{
	if (!tokens->next)
	{
		throw_error("syntax error near unexpected token 'newline'", 1);
		clean_exit(vars, 1);
	}
	if (ft_strcmp(token, ">>") == 0)
	{
		if (vars->stdout > -1)
			close(vars->stdout);
		vars->stdout = open(tokens->next->token,
				O_WRONLY | O_CREAT | O_APPEND);
	}
	else
	{
		if (vars->stdout > -1)
			close(vars->stdout);
		vars->stdout = open(tokens->next->token,
				O_WRONLY);
	}
	if (vars->stdout == -1)
		open_err(vars, tokens);
}

void	redirect_output(t_vars *vars, t_list *tokens, char *token)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == R_IN)
			redirect_input(vars, tokens);
		if (tokens->type == R_OUT)
			handle_token(vars, tokens, token);
		tokens = tokens->next;
	}
	dup2(vars->stdout, STDOUT_FILENO);
	printf("errno %d\n", errno);
}
