#include "minishell.h"

int	handle_special(t_vars *vars, char *token, char *line)
{
	if (vars->token_i == 0)
	{
		while (line[vars->parse_i]
			&& ft_strchr(REDIRS_CHARS, line[vars->parse_i]) != NULL)
		{
			token = add_c_tok(line[vars->parse_i], vars, vars->token_i, token);
			vars->parse_i++;
		}
	}
	token = add_c_tok('\0', vars, vars->token_i, token);
	vars->parse_i--;
	return (FINISHED);
}
