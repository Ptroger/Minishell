#include "minishell.h"

void	redir_temp(t_vars *vars, t_list *tokens, char *name, int *file)
{
	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		throw_error(NULL, errno);
		exit(errno);
	}
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
				exit(1);
			}
			close(vars->stdin);
			vars->stdin = open(tokens->next->token, O_RDONLY, 0777);
			if (vars->stdin == -1)
			{
				throw_error(NULL, errno);
				exit(errno);
			}
		}
		tokens = tokens->next;
	}
	dup2(vars->stdin, STDIN_FILENO);
}

void	redirect_output(t_vars *vars, t_list *tokens, char *token)
{
	while (tokens)
	{
		if (tokens->type == R_IN)
			redirect_input(vars, tokens);
		if (tokens->type == R_OUT)
		{
			if (!tokens->next)
			{
				throw_error("syntax error near unexpected token 'newline'", 1);
				exit(1);
			}
			if (ft_strcmp(token, ">>") == 0)
			{
				close(vars->stdout);
				vars->stdout = open(tokens->next->token, O_WRONLY | O_CREAT | O_APPEND, 0777);
			}
			else
			{
				close(vars->stdout);
				vars->stdout = open(tokens->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			}
			if (vars->stdout == -1)
			{
				throw_error(NULL, errno);
				return ;
			}
		}
		tokens = tokens->next;
	}
	dup2(vars->stdout, STDOUT_FILENO);
}
