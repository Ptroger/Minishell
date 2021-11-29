#include "../../includes/minishell.h"

int	handlers(t_vars *vars, char *token, char *line)
{
	if (line[vars->parse_i] == '$')
	{
		if (handle_dollar(vars, token, line) == 1)
			return (1);
	}
	else if (line[vars->parse_i] == '\'' || line[vars->parse_i] == '"')
	{
		if (handle_quotes(vars, token, line) == 1)
			return (1);
	}
	else if (line[vars->parse_i] == ' ')
	{
		if (handle_space(vars, token, line) == 1)
			return (1);
	}
	else if (line[vars->parse_i] != ' ' || vars->state == D_QUOTE
		|| vars->state == S_QUOTE)
		token = add_c_tok(line[vars->parse_i], vars, vars->token_i, token);
	return (0);
}

char	*get_next_token(char *line, t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size + 1);
	token[vars->token_size] = '\0';
	while (line[vars->parse_i])
	{
		if (handlers(vars, token, line) == 1)
		{
			vars->parse_i += 1;
			return (token);
		}
		vars->parse_i += 1;
	}
	vars->finish_line = TRUE;
	token = add_c_tok('\0', vars, vars->token_i, token);
	return (token);
}

void	parse(char *line, t_vars *vars)
{
	char	*token;
	int		i;

	i = 0;
	while (vars->finish_line == FALSE)
	{
		vars->token_i = 0;
		token = get_next_token(line, vars);
		finish_token(vars, token, i);
		i++;
	}
	vars->finish_line = FALSE;
}
