/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:13:47 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:13:49 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d(t_vars *vars)
{
	printf("exit\n");
	if (vars->real_envs)
		destroy_tab(vars->real_envs);
	clean_exit(vars, 0);
}

void	sig_c(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_g.ret = 1;
}

void	handle_parent(int sig)
{
	if (kill(g_g.pid, sig) == 0)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			g_g.ret = 130;
		}
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3 Core dumped\n", STDERR_FILENO);
			g_g.ret = 131;
		}
	}
	else if (sig == SIGINT)
		sig_c();
}

void	sig_handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_g.pid != 0)
		handle_parent(sig);
	else if (sig == SIGQUIT)
		exit(131);
	else
		sig_c();
}
