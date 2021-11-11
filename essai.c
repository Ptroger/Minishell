#include "includes/minishell.h"

int	main()
{
	char *toto = "|";

	if (ft_mul_strcmp(REDIRS_STRINGS, toto) == TRUE)
		printf("TRUE\n");
	else
		printf("FALSE");
	return (0);
}