#include "minishell.h"

void	set_files(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	while (tokens)
	{
		if (tokens->type == R_IN && tokens->next && tokens->next->type == NONE)
			tokens->next->type = F_OPEN;
		else if (tokens->type == H_DOC && tokens->next
			&& tokens->next->type == NONE)
			tokens->next->type = LIMITOR;
		else if (tokens->type == R_OUT && tokens->next
			&& tokens->next->type == NONE)
			tokens->next->type = F_EXIT;
		tokens = tokens->next;
	}
}

void	set_redir(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	while (tokens)
	{
		if (ft_strcmp(tokens->token, "<") == 0)
			tokens->type = R_IN;
		else if (ft_strcmp(tokens->token, "<<") == 0)
			tokens->type = H_DOC;
		else if (ft_strcmp(tokens->token, ">") == 0
			|| ft_strcmp(tokens->token, ">>") == 0)
			tokens->type = R_OUT;
		else if (ft_strcmp(tokens->token, "|") == 0)
			tokens->type = PIPE;
		else
			tokens->type = NONE;
		tokens = tokens->next;
	}
}

void	set_cmd(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	tokens->type = CMD;
	while (tokens)
	{
		if (tokens->type == PIPE && tokens->next)
			tokens->next->type = CMD;
		else if (tokens->type == NONE)
			tokens->type = ARG;
		tokens = tokens->next;
	}
}

void	flag_mix(t_vars *vars)
{
	t_list	*tokens;
	int		i;

	tokens = vars->tokens;
	while (tokens)
	{
		i = 0;
		if (ft_strchr(tokens->token, '<') != NULL)
			i += 1;
		if (ft_strchr(tokens->token, '>') != NULL)
			i += 1;
		if (ft_strchr(tokens->token, '|') != NULL)
			i += 1;
		if (i > 0 && tokens->type == NONE)
			tokens->type = SYNTAX_ERROR;
		tokens = tokens->next;
	}
}

void	flag_syntax(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	while (tokens)
	{
		if (tokens->type >= R_IN && tokens->type < H_DOC)
		{
			if (tokens->next && (tokens->next->type <= 5
				|| tokens->next->type >= 7))
				{
					tokens->next->type = SYNTAX_ERROR;
					// printf("ici\n");
				}
			else if (!tokens->next)
				tokens->type = SYNTAX_ERROR;
		}
		tokens = tokens->next;
	}
}

void	set_type(t_vars *vars)
{
	set_redir(vars);
	flag_mix(vars);
	set_files(vars);
	flag_syntax(vars);
	set_cmd(vars);
}
