#include "minishell.h"

void	ft_strcpy_2(char *old, char *new, int i)
{
	int n;

	n = 0;
	if (!old || !new)
		return ;
	while (old[n] && n < i)
	{
		new[n] = old[n];
		n++;
	}
	new[n] = '\0';
}