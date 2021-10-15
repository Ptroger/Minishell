#include "minishell.h"

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
			finish_quote;
		else if (vars->state == S_QUOTE && c == '\'')
			finish_quote;
		else
			vars->tokens->token[vars->tokens->i] = c;
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