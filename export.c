#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		return ;
	}
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
 
size_t	ft_strlen3(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_strserarch(char *str,char c)
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == c)
        return 1;
        i++;
    }
    return 0;
}
envp	*sort_list(envp *lst, int (*cmp)(char *, char *))
{
	char	*swap;
    int swapint;
	envp	*tmp;

	tmp = lst;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->str, lst->next->str)) >= 0)
		{
			swap = lst->str;
			swapint = lst->option;
			lst->str = lst->next->str;
			lst->option = lst->next->option;
			lst->next->str = swap;
			lst->next->option = swapint;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
    //printnode(lst);
	return (lst);
}
int	ft_strcmpedit( char *s1,  char *s2)
{
	size_t	i;

	i = 0;
    //printf("s1 : %s s2: %s \n ",s1,s2);
	while ((s1[i] != '='  || s2[i] != '=' )&& (s1[i] != '\0' || s2[i] != '\0')&&(s1[i] != '=' || s2[i] != '\0')&&(s1[i] != '\0' || s2[i] != '='))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	return  0;
}
char *ft_strplusequal(char *str,int k)
{
    int i =0;
    int j = 0;
    int size = 0;
    while(str[i] != '=')
        i++;
    size = ft_strlen3(str) - i;
    if(k == 1)
    i--;
    else
    size--;
    
    char *str2 = malloc(sizeof(char) * size);
    i++;
    while(str[i] != '\0')
    {
        str2[j] = str[i];
        i++;
        j++;
    }
    str2[j] = '\0';
    return str2;
}
int updateenv(envp *env,char *str,int b)
{
    envp *st;
    st = env;
    char *ptr = NULL;
    while(st)
    {
        // printf("tst : %s\n",st->str);
        if(ft_strcmpedit(str,st->str) == 0 && b == 0)
        {
           // printf("tst : %s |%s\n",st->str,str);
            //free(st->str);
            if(ft_strserarch(str,'=') == 1)
            {
                //free(st->str);
                st->str = str;
                //free(str);
              if(ft_strserarch(str,'=') == 1)
              st->option = 1;
              return 1;
            }
            else
            return 3;
            
            
        }
        else if(ft_strcmpedit(str,st->str) == 0 && b == 1)
        {
            //printf("-----------%s\n", st->str);
            if(ft_strserarch(st->str,'=') == 0)
            {
               // printf("----------------------meee>\n");
                ptr = ft_strplusequal(str,1);
                if(ft_strserarch(ptr,'=') == 1)
              st->option = 1;
            }
            else
                ptr = ft_strplusequal(str,0);
            printf("-----------%s\n", ptr);
            st->str = ft_strjoin(st->str,ptr,st->free);
            st->free = 1;
            return 1;
        }
            
        st = st->next;
    }
    return 0;
}
envp	*ft_lstnew(char *content,int option)
{
	envp	*new;

	new = (envp *)malloc(sizeof(envp));
	if (new == NULL)
		return (NULL);
	new->str = content;
    new->option = option;
    new->free = 0;
	new->next = NULL;
	return (new);
}
envp	*ft_lstlastZ(envp *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(envp **lst, envp *new)
{
	envp	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlastZ(*lst);
		last->next = new;
	}
}

int	ft_strcmp( char *s1,  char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_putstredit(char *s)
{
	int	i;
    int j = 0;
	i = 0;
	
	while (s[i] != '\0')
	{
        
		write(1, &s[i], 1);
        if(s[i] == '=' && j == 0)
        {
            write(1, "\"", 1);
            j = 1;
        }
		i++;
	}
    write(1, "\"", 1);
}
void printnodeExport(envp *str)
{
    envp *st;
    st = str;
    while(st)
    {
        ft_putstr_fd("declare -x ",1);
        if(st->option == 1)
         ft_putstredit(st->str);
         else
         {
                ft_putstr_fd(st->str,1);
         }
         
         ft_putstr_fd("  | ",1);
        ft_putnbr_fd(st->option,1);
        printf("\n");
        st = st->next;
    }  
}
// void printnodeenv(envp *str)
// {
//     envp *st;
//     st = str;
//     while(st)
//     {
//         if(st->option == 1)
//         printf("%s\n",st->str);
//         st = st->next;
//     }  
//     //print the last lint in the original env
// }

void	make_node(envp **st, char *str)
{
	envp	*head;

	head = malloc(sizeof(envp));
	if (!head)
		return ;
	head->str = str;
    head->option = 1;
	head->next = *st;
	*st = head;
}
int valideinput(char *str)
{
    int i = 0;
    if(ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0)
    {
        return 1; 
    }
        
    i++;
    // if(ft_strchr(str,'=') == 0)
    // {
    //     return 1;
    // }
    
    while(str[i] != '=' && str[i])
    {
        if(ft_isalnum(str[i]) == 1 || str[i] == '=')
        {
            i++;
        }
        else if(str[i] == '+')
        {
            if(str[i+1] == '=')
             i++;
             else
             return 1;
        }
        else 
        {
            printf("%c\n",str[i]);
            return  1;
        }
        
    }
    return 0;
}
int	ft_strnstredit(const char *str)
{
	// size_t	i;
	// size_t	j;

	// i = 0;
	// if (str == NULL)
	// 	return (0);
	// if (to_find[i] == '\0')
	// 	return (0);
	// while (str[i] != '\0')
	// {
	// 	j = 0;
	// 	while (str[i + j] == to_find[j] && str[i + j] != '\0')
	// 	{
	// 		if (to_find[j + 1] == '\0')
	// 			return (1);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// return (0);
    int i = 0;
    while(str[i])
    {
        if(str[i] == '=')
        {
            if(str[i-1] == '+')
            return 1;
            else
            return 0;
        }
        i++;
    }
    return 0;
}
char	*ft_strdupedit(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
    j = 0;
	len = ft_strlen3(s1) - 1;
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[j] != '\0')
	{
        if(s1[i] == '+' && s1[i+1] == '=')
            j++;
            
		p[i] = s1[j];
        j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
void export(envp **env1 ,char *str)
{
   
    int error = 0;
    int x = 0;
    char *stredit;
    int b = 0;
    static int i = 0;
    if(i == 0)
    {
       sort_list(*env1,ft_strcmp);
        i++;
    }
    
    if(str == NULL)
        printnodeExport(*env1);
   
    else
    {
        x = valideinput(str);
        //updt  export data
        if(x == 1)//add all the error char
            {
                printf("export: `%s': not a valid identifier\n",str);
                error = 1;
            }

             if ((ft_strserarch(str,'=') == 1) &&  (ft_strnstredit(str) == 0) &&  x == 0)
            {
      
                    if(updateenv(*env1,str,0) == 1)
                     {
                         printf("update :%s\n",str);
                         //updt  export data
                     }
                         else
                            ft_lstadd_back(env1,ft_lstnew(str,1));
            }
            else if ((ft_strserarch(str,'=') == 1) && (ft_strnstredit(str) == 1) && x == 0)
            {
                
                stredit = ft_strdupedit(str);
                      if(updateenv(*env1,stredit,1) == 1)
                     {
                        free(stredit);
                         printf("update2 :%s\n",str);
                         //updt  export data
                     }
                         else
                         {
                                //free(stredit);
                            ft_lstadd_back(env1,ft_lstnew(stredit,1));
                         }
                         
            }
            
            else if ((ft_strserarch(str,'=') == 0) && x == 0)
            { 
                printf("str :%s\n",str);
                 b = updateenv(*env1,str,0);
                if(b == 1)
                     {
                         printf("update :%s\n",str);
                         //updt  export data
                    }
                else if (b == 0)
                {
                    printf("aaaaaa\n");
                    ft_lstadd_back(env1,ft_lstnew(str,0));
                }
                else if (b == 3)
                {
                    printf("jiji\n");
                }
            }

    }
}
// int main(int argc,char **argv ,char **env)
// {
//     (void)argc;
//     (void)argv;
//     t_pipex pipex;
//      printf("/-----------------------------\n");
//     //add OLDPWD
//     int i = 0;
//     //int j = 1;
//     //int error = 0;
// 	envp *env1 = NULL;
// 	while (env[i] != '\0')
// 		i++;
// 	i -= 2;
// 	while (i >= 0)
// 	{
// 		make_node(&env1, env[i]);
// 		i--;
// 	}
//    // export(&env1,"OLDPWD");
//     //sort_list(env1,ft_strcmp);
//     //envv(env1);
//     // export(&env1,"alom");
//     //export(&env1,"testb=zaka"); 
//     // export(&env1,"rrr");
//     //  printf("/-----------------------------\n");
//     // export(&env1,"test=mbarki");
//     //  printf("/-----------------------------\n");
    
    
//     // printf("%d\n",ft_strcmpedit("alom","alom=poink"));
//     // export(&env1,"gg=zak");
//     //  export(&env1,"alom=zaka");
//     //  export(&env1,"alom=zakba");
//     // export(&env1,"alom+=bb");
//     export(&env1,NULL);
//     //  export(&env1,"gg+=lmkj");
//     printf("/-----------------------------\n");
//     pathfinder(&pipex,env1);
//     printf("%s\n",pipex.paths[0]);
//     //  export(&env1,"gg+=www");
//     //  export(&env1,"gg+=bbb");
//     //   export(&env1,"alom+=zakbac");
//     //  export(&env1,"alom+=zakbag");
//     //  export(&env1,"alom+=zzz");
//     //  export(&env1,"alom+=zzz");
//     //  export(&env1,"alom+=zzz");
//     //ft_cd(&env1,"kr[ohk]");
//     //unset(&env1,"Apple_PubSub_Socket_Render");
//     //export(&env1,NULL,0);
//     //printf("/-----------------------------\n");
//     //export(&env1,NULL,0);
//     //ft_cd(&env1,NULL);
//     // ft_pwd();
//      //printf("/-----------------------------\n");
//     //export(&env1,NULL,0);
//      //ft_cd(&env1,"/bin");
//      //printf("/-----------------------------\n");
//     //export(&env1,NULL,0);
//      //printf("/-----------------------------\n");
//      //ft_cd(&env1,"/home");
//      //printf("/3\n");
//      //export(&env1,NULL,0);
//      //ft_cd(&env1,"-");
//     //ft_pwd();
//      //printf("/-----------------------------\n");
//     //echo("-nnnnnnnnnnnn","$HOME");
//      //export(&env1,NULL);
//     //system("leaks minishell");
//     // printnodeenv(env1);
// }
//update value of export and if its valid make the option 1
//if you want to update the value of a valide varibale dont update it;
//test+= is not easy to do you should join what in plus with the value of the variable