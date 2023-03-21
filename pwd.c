#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void ft_pwd()
{
    char *ptr;
   ptr =  getcwd(NULL,1);
    printf("%s\n",ptr);
    free(ptr);
}
