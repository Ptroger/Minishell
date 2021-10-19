#include "minishell.h"

/// IL FAUT GERER LES ETATS DES TOKENS ET ECRIRE UNE FONCTION POUR RENTRER LES TOKENS DANS LA LISTE
/// DETERMINER COMMENT JE VAIS GERER L'AJOUT DES TOKENS

void	add_char_to_token(char c, t_vars *vars)
{
	char	*new_token;
	char	*ptr;

	if (vars->tokens->i < vars->token_size)
		vars->tokens->token[vars->tokens->i] = c;
	else
	{
		ptr = vars->tokens->token;
		vars->token_size *= 2;
		new_token = malloc(sizeof(char) * vars->token_size);
		ft_strcpy(vars->tokens->token, new_token, vars->tokens->i);
		vars->tokens->token = new_token;
		free(ptr);
	}
	vars->tokens->i++;
}

static void	finish_quote(char c, t_vars *vars)
{
	vars->state = BASIC;
	add_char_to_token(c, vars);
	add_char_to_token('\0', vars);
}

static void	set_state(char c, t_vars *vars)
{
	if (vars->state == BASIC)
	{
		if (c == '"')
			vars->state = D_QUOTE;
		else if (c == '\'')
			vars->state = S_QUOTE;
	}
	else
	{
		if (vars->state == D_QUOTE && c == '"')
			finish_quote(c, vars);
		else if (vars->state == S_QUOTE && c == '\'')
			finish_quote(c, vars); 
		else
			add_char_to_token(c, vars);
	}
}

void	tokenize_line(char *line, t_vars *vars)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			set_state(line[i], vars);
		i++;
	}
}

void	parse(char *line, t_vars *vars)
{
	tokenize_line(line, vars);
}