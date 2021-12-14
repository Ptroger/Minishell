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
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

void	set_files(t_vars *vars)
{
	t_list	*tokens;

	tokens = vars->tokens;
	while (tokens)
	{
		if (tokens->type == R_IN)
			tokens->next->type = F_OPEN;
		else if (tokens->type == H_DOC)
			tokens->next->type = LIMITOR;
		else if (tokens->type == R_OUT)
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
				 || ft_strcmp(tokens->token, ">>") == 0 )
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
		if (tokens->type == PIPE)
			tokens->next->type = CMD;
		else if (tokens->type == NONE)
			tokens->type = ARG;
		tokens = tokens->next;
	}
}

void	set_type(t_vars *vars)
{
	set_redir(vars);
	set_files(vars);
	set_cmd(vars);
}

void	read_loop(t_vars *vars)
{
	char	*line;

	while (vars->shell == RUNNING)
	{
		vars->parse_i = 0;
		signal(SIGQUIT, SIG_IGN);
		line = readline(PROMPT);
//		ft_putnbr_fd(g_g.pid, 1);
		if (!line)
		{
			destroy_vars(vars);
			exit(0);
		}
		if (check_str(line) != 0)
			throw_error("parse error", 1);
		else if (*line)
		{
			parse(line, vars);
			set_type(vars);
			add_history(line);
			free(line);
			call_command(&vars, FALSE);
			ft_lstclear(&vars->tokens, free);
			unlink("./temp");
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
