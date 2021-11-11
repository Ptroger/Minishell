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

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int             shell;
	int             token_i;
	int             parse_i;
	int				name_i;
	int             state;
	int             token_size;
	int             finish_line;
	t_list  *tokens;
}                               t_vars;


typedef struct      s_sort
{
    char            *str;
    struct s_sort   *next;
}                   t_sort;

void    ft_pwd();
void    call_command(t_list *tokens, t_sort  **t_env, t_sort  **t_exp);
void	ft_add_elem(t_sort **sort, char *env);
void	ft_add_elem_exp(t_sort **sort, char *env);
void    ft_cd(char *path);
void    ft_echo(char *str);
void    ft_echo_n(char *str);
void    ft_env(t_sort **env);
void    ft_export(t_list *tokens, t_sort  **t_exp);
void	parse(char *line, t_vars *vars);
int		handle_dollar(t_vars *vars, char *token, char *line);
char	*add_char_to_token(char c, t_vars *vars, int i, char *token);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putendl(char *s);
void	ft_reverse_rotate(t_sort **pile);
void	ft_strcpy(char *old, char *ne, int i);
void	ft_swap(t_sort **pile);
void	add_token(t_vars *vars, int i);
int		ft_pile_in_order(t_sort **pile_a);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_return_max(t_sort **pile_a);
char	*ft_strcpy_ari(char *dest, char *src);
int		ft_strlen(const char *str);
char	**ft_split(const char *str, char c);

#endif
