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

typedef struct		s_glob
{
	pid_t	pid;
	int		ret;
}					t_glob;

typedef struct		s_sort
{
	char			*name;
    char			*data;
	char			*info;
    struct s_sort	*next;
}					t_sort;

typedef struct		s_pipe
{
	int				size;
	char			*token;
	char			**cmd;
	char			**cell;
	struct s_pipe	*next;
}					t_pipe;

typedef struct	s_vars
{
	int		state;
  	int		token_i;
	int		parse_i;
	int		name_i;
	int		token_size;
	int		finish_line;
	int		special_i;
	int		size;
	int		tab_size;
	int		exit_status;
	int		stdout;
	int		stdin;
	char	**path;
	char	**real_envs;
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
void	cat_ret(char *token, t_vars *vars);
int		ft_mul_strcmp(const char **s1, const char *s2);
void	ft_strcpy_2(char *old, char *ne, int i);
char	*get_tok_index(t_list *lst, int i);
void	finish_token(t_vars *vars, char *token, int i);

// REDIRECTIONS
void	redirect_input(t_vars *vars, t_list *tokens);
void	redir_temp(t_vars *vars, t_list *tokens, char *name, int *file);
void	redirect_output(t_vars *vars, t_list *tokens, char *token);
int		handle_redirs(t_vars *vars, t_list *tokens, int *file);
int		is_redir(char *token);
int		is_special(t_list *tokens);
int		ft_pipe(t_vars **vars, t_pipe *pipe);
void	ft_add_elem_pipe(t_pipe **store);

// HEREDOCS
void	write_file(t_vars *vars, char *name);
char	*insert_env(char *line, char *env, int l, int i);
int	expand_helper(t_vars *vars, char *line, char *name, int i);

// EXECUTION
int		call_command(t_vars **vars, int is_child);
void	ft_find_cmd(t_vars *vars, char *token, char **cmd, char **tab);
int		shall_exec(t_vars *vars, t_list *token);

// ENVS
void	ft_get_env_name(t_sort **t_env, char **env);
void	ft_set_env(t_sort **t_env, char **env);
void	set_envs(t_vars *vars);
char	*my_get_env(t_vars *vars, char *name);
void	add_back(t_sort **sort, t_sort *new);

// BUILTINS
int		ft_cd(t_vars **vars, t_list *tokens, char *user);
void	ft_pwd(t_vars *vars, t_list *tokens);
void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd);
void	ft_call_echo(t_list *tokens);
void	ft_echo_n(t_list *tokens);
void	ft_call_env(t_vars **vars, t_list *tokens);
void	ft_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_call_builtin(t_vars **vars, t_list *tokens);
int		ft_is_builtin(char *token);

// BUILTINS_UTILS
void	ft_browse_tmp(t_list **temp);
void	ft_process_3(t_vars **vars, t_pipe *temp_p, t_list *temp_1);
int		ft_process_2(t_vars **vars, t_pipe *temp_p);

// MEMORY
void	clean_exit(t_vars *vars, int code);
char    *dupfree(char *s1, char *s2);
void	destroy_vars(t_vars *vars);
void	destroy_tab(char **tab);
t_vars	*ft_init_vars(void);

// OTHERS
void	sig_handler(int sig);
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
char	*find_path(char *token, char **tab);
char	*ft_return_max(t_sort **pile_a);
char	**ft_command_size(int size);

#endif
