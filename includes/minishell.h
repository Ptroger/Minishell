#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"
# include "../libft/libft.h"

typedef struct      s_sort
{
	char			*name;
    char            *data;
    struct s_sort   *next;
}                   t_sort;

typedef	struct		s_pipe
{
	int				size;
	char			*token;
	char			**cmd;
	char			**cell;
	struct s_pipe	*next;
}					t_pipe;

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int		shell;
	int		state;
  	int token_i;
	int    parse_i;
	int				name_i;
	int		token_size;
	int		finish_line;
	t_pipe	*store;
	t_list	*tokens;
	t_sort	*t_env;
	t_sort	*t_exp;
}				t_vars;

void	add_token(t_vars *vars, int i);
void	ft_add_elem(t_sort **sort, char *env);
void	ft_add_elem_exp(t_sort **sort, char *env);
void	ft_add_elem_exp_2(t_sort **sort, t_sort *new_elem, char *env);
void	ft_add_elem_pipe(t_pipe **store);
void    ft_cd(char *path);
void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd);
void    ft_echo(char *str);
void    ft_echo_n(char *str);
void    ft_env(t_sort **env);
void    ft_export(t_list *tokens, t_sort **t_env, t_sort  **t_exp);
void    ft_find_cmd(char *token, char **cmd, char **tab);
void	ft_get_env_name(t_sort  **t_env, char **env);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(char *));
void	ft_lstclear(t_list **alst, void (*del)(void *));
void	parse(char *line, t_vars *vars);
int		handle_dollar(t_vars *vars, char *token, char *line);
char	*add_char_to_token(char c, t_vars *vars, int i, char *token);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putendl(char *s);
void	ft_reverse_rotate(t_sort **pile);
void	ft_set_env(t_sort  **t_env, char **env);
void	ft_set_exp(t_sort  **t_exp, t_sort  **t_env);
void	ft_strcpy(char *old, char *ne, int i);
void	ft_swap(t_sort **pile);
void    ft_pwd();
void    ft_unset(t_list *tokens, t_sort **t_env, t_sort  **t_exp);
int		call_command(t_vars **vars);
int		ft_error(char *str);
void	add_token(t_vars *vars, int i);
int		ft_pile_in_order(t_sort **pile_a);
int  	ft_pipe(t_list *tokens, t_pipe *pipe, char **tab);
int     ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char    *find_path(char *token, char *tab);
char	*ft_return_max(t_sort **pile_a);
char	*ft_strcpy_ari(char *dest, char *src);
char	*ft_strdup(const char *s1);
char  	**ft_command_size(int size);
char	**ft_split(const char *str, char c);
t_list	*ft_lstnew(void *content, int i);

#endif
