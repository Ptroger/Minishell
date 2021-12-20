#include "includes/minishell.h"

int main(){
printf("open %d\n",open("minishell", O_WRONLY));
}
