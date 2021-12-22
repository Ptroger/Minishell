/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:08:33 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/21 19:11:59 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <errno.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "constants.h"
# include "../libft/libft.h"

typedef struct s_glob
{
	pid_t	pid;
	int		ret;
}					t_glob;

typedef struct s_sort
{
	char			*name;
	char			*data;
	char			*info;
	struct s_sort	*next;
}					t_sort;

typedef struct s_pipe
{
	int				index;
	int				redir;
	int				size;
	char			*token;
	char			**cmd;
	char			**cell;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_vars
{
	int		state;
	int		token_i;
	int		parse_i;
	int		name_i;
	int		token_size;
	int		finish_line;
	int		special_i;
	int		been_quoted;
	int		size;
	int		tab_size;
	int		exit_status;
	int		stdout;
	int		stdin;
	int		hrdc;
	char	**path;
	char	**real_envs;
	t_pipe	*original;
	t_pipe	*store;
	t_list	*tokens;
	t_sort	*t_env;
	t_sort	*t_exp;
}				t_vars;

extern t_glob	g_g;

// TOKENS FUNCTIONS
void	parse(char *line, t_vars *vars);
int		handle_dollar(t_vars *vars, char *token, char *line);
int		handle_quotes(t_vars *vars, char *token, char *line);
int		handle_space(t_vars *vars, char *token, char *line);
int		handle_special(t_vars *vars, char *token, char *line);
void	set_type(t_vars *vars);

// TOKEN UTILS
void	add_token(t_vars *vars, int i);
char	*add_c_tok(char c, t_vars *vars, int i, char *token);
char	*my_get_env(t_vars *vars, char *name);
int		is_valid(t_vars *vars, char *line);
int		check_pipe(char *str);
void	cat_ret(char *token, t_vars *vars);
int		ft_mul_strcmp(const char **s1, const char *s2);
void	ft_strcpy_2(char *old, char *ne, int i);
char	*get_tok_index(t_list *lst, int i);
void	flag_mix(t_vars *vars);
void	finish_token(t_vars *vars, char *token, int i);

// REDIRECTIONS
int		ft_check_redir(t_vars **vars);
void	redirect_input(t_vars *vars, t_list *tokens, int *file);
void	redir_temp(t_vars *vars, t_list *tokens, char *name, int *file);
void	redirect_output(t_vars *vars, t_list *tokens, char *token, int *file);
int		handle_redirs(t_vars *vars, t_list *tokens, int *file);
int		ft_is_redir(char *str);
int		is_special(t_list *tokens);
int		is_absolute(char *token);
int		is_dir(t_vars *vars, char *path, int is_exec);
int		ft_pipe(t_vars **vars);
t_pipe	*ft_add_elem_pipe(void);
void	pipe_add_back(t_pipe **sort, t_pipe *new);

// HEREDOCS
void	write_file(t_vars *vars, char *name);
char	*insert_env(char *line, char *env, int l, int i);
int		expand_helper(t_vars *vars, char *line, char *name, int i);

// EXECUTION
int		call_command(t_vars **vars, int is_child);
void	ft_single_command(t_vars **vars, t_list *tokens, char **cmd, int size);
void	ft_find_cmd(t_vars *vars, char *token, char ***cmd, char **tab);
int		shall_exec(t_vars *vars, t_list *token);
void	ctrl_d(t_vars *vars);

// ENVS
void	ft_get_env_name(t_sort **t_env, char **env);
void	ft_set_env(t_sort **t_env, char **env);
void	ft_display_exp(t_sort **t_exp);
void	set_envs(t_vars *vars);
char	*my_get_env(t_vars *vars, char *name);
int		check_quote(char *str);
void	cpy_env(t_sort *temp, char **env, int i, int *j);
void	add_back(t_sort **sort, t_sort *new);

// BUILTINS
void	ft_env(t_sort **t_env);
int		ft_cd(t_vars **vars, t_list *tokens, char *user);
void	ft_pwd(t_vars *vars, t_list *tokens);
void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd);
void	ft_exit(t_vars *vars, t_list *tokens);
void	ft_call_echo(t_list *tokens);
void	ft_echo_n(t_list *tokens);
void	ft_call_env(t_vars **vars, t_list *tokens);
void	ft_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_unset_env(t_sort **t_env, int i);
void	ft_unset_exp(t_sort **t_env, int i);
void	ft_parse_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp,
			char *tmp);
void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_fill_data(t_list *tokens, t_sort *new_exp);
void	ft_set_list_2(t_sort *new_env);
void	ft_set_list(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_set_temp(t_list *tokens, char **env, char **tmp, int j);
void	ft_new_var(t_list *tokens, t_sort **t_env, t_sort **t_exp, int j);
void	ft_new_var_env(t_list *tokens, t_sort **t_env, t_sort **t_exp, int j);
void	ft_browse_env(t_list *tokens, t_sort **t_env,
			t_sort **t_exp, char *tmp);
void	destroy_tmp_env(t_sort *envs, char *str);
void	ft_call_builtin(t_vars **vars, t_list *tokens);
int		ft_is_builtin(char *token);

// BUILTINS_UTILS
void	ft_browse_tmp(t_list **temp, t_pipe **temp_p, int *count);
void	ft_process_3(t_vars **vars, t_pipe *temp_p, t_list *temp_1);
int		ft_process_2(t_vars *vars);
int		check_path(t_vars *vars, char *path, int is_exec);

// MEMORY
void	destroy_store(t_pipe **store);
void	clean_exit(t_vars *vars, int code);
char	*dupfree(char *s1, char *s2);
void	destroy_vars(t_vars *vars);
void	destroy_tab(char **tab);
void	destroy_env(t_sort **envs);
t_vars	*ft_init_vars(void);

//PIPES
int		ft_child(t_vars **vars, t_pipe **store, int size);

// OTHERS
void	set_type(t_vars *vars);
int		find_path_2(char *token, char **tab);
void	sig_handler(int sig);
int		check_syntax(t_vars *vars);
int		throw_error(char *err, int errcode);
t_sort	*ft_add_elem(char *env);
void	ft_add_elem_exp(t_sort **sort, char *env);
void	ft_add_elem_exp_2(t_sort **sort, t_sort *new_elem, char *env);
void	ft_reverse_rotate(t_sort **pile);
void	ft_set_exp(t_sort **t_exp, t_sort **t_env);
void	ft_swap(t_sort **pile);
int		ft_is_key(char *str);
int		ft_new_readline(t_vars **vars);
int		ft_pile_in_order(t_sort **pile_a);
char	*find_path(t_vars *vars, char *token, char **tab);
char	*ft_return_max(t_sort **pile_a);
char	**ft_command_size(int size);

#endif
