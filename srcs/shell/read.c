/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:15:26 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:15:28 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_str(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
			{
				throw_error("syntax error near token: ", 1);
				ft_putchar_fd(str[i], 2);
				return (1);
			}
			dif = 0;
		}
		i++;
	}
	return (0);
}

int	check_syntax(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	while (tokens)
	{
		if (tokens->type == SYNTAX_ERROR)
		{
			ft_putstr_fd("syntax error near token ", STDERR_FILENO);
			throw_error(tokens->token, 258);
			return (FALSE);
		}
		tokens = tokens->next;
	}
	return (TRUE);
}

char	*reset_loop(t_vars *vars)
{
	char	*line;

	vars->parse_i = 0;
	vars->exit_status = g_g.ret;
	signal(SIGQUIT, SIG_IGN);
	line = readline(PROMPT);
	while (line && (check_quote(line) == FALSE
		|| check_pipe(line) == FALSE))
	{
		free(line);
		line = readline(PROMPT);
	}
	return (line);
}

void	read_loop(t_vars *vars)
{
	char	*line;

	while (1)
	{
		line = reset_loop(vars);
		if (!line)
			ctrl_d(vars);
		else if (*line)
		{
			parse(line, vars);
			add_history(line);
			if (vars->tokens)
				set_type(vars);
			if (check_syntax(vars) == TRUE && vars->tokens)
			{
				free(line);
				call_command(&vars, FALSE);
			}
			ft_lstclear(&vars->tokens, free);
			if (access(H_DOC_PATH, R_OK) == 0)
				unlink(H_DOC_PATH);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars				*vars;

	(void)ac;
	(void)av;
	vars = ft_init_vars();
	ft_set_env(&vars->t_env, env);
	ft_get_env_name(&vars->t_env, env);
	ft_set_exp(&vars->t_exp, &vars->t_env);
	signal(SIGINT, sig_handler);
	read_loop(vars);
	destroy_vars(vars);
}
