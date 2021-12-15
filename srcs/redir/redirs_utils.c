#include "minishell.h"

void	redir_temp(char *name, int *file)
{
	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		throw_error(NULL, errno);
		exit(errno);
	}
	dup2(*file, STDIN_FILENO);
}

void	redirect_input(t_list *tokens, int *file)
{
	while (tokens)
	{
		if (tokens->type == R_IN)
		{
			if (!tokens->next)
			{
				throw_error("syntax error near unexpected token 'newline'", 1);
				exit(1);
			}
			close(*file);
			*file = open(tokens->next->token, O_RDONLY, 0777);
			if (*file == -1)
			{
				throw_error(NULL, errno);
				exit(errno);
			}
		}
		tokens = tokens->next;
	}
	dup2(*file, STDIN_FILENO);
}

void	redirect_output(t_list *tokens, char *token, int *file)
{
	while (tokens)
	{
		if (tokens->type == R_OUT)
		{
			if (!tokens->next)
			{
				throw_error("syntax error near unexpected token 'newline'", 1);
				exit(1);
			}
			if (ft_strcmp(token, ">>") == 0)
			{
				close(*file);
				*file = open(tokens->next->token, O_WRONLY | O_CREAT | O_APPEND, 0777);
			}
			else
			{
				close(*file);
				*file = open(tokens->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			}
			if (*file == -1)
			{
				throw_error(NULL, errno);
				return ;
			}
		}
		tokens = tokens->next;
	}
	dup2(*file, STDOUT_FILENO);
}
