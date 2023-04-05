#include "minishell.h"

void ft_pwd()
{
    char *ptr;
   ptr =  getcwd(NULL,1);
   if(ptr == NULL)
   {
        ptr = ft_getenv(g_globale.env1, "PWD");
   }
    printf("%s\n",ptr);
    free(ptr);
}
