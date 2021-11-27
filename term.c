#include "includes/minishell.h"

int main()
{
	char *ls = "ls";
	printf("ret == %d\n", execve(ls, &ls, 0));
}