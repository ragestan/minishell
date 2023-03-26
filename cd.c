/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:27:59 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/26 15:35:45 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//should fix CD only;
void	ft_pwd(void)
{
	char	*ptr;

	ptr = getcwd(NULL, 1);
	printf("%s\n", ptr);
	free(ptr);
}
char	*ft_getenv(envp *env, char *str)
{
	char	*ptr;
    
	ptr = NULL;
	while (env)
	{
		if (ft_strncmp(env->str, str, ft_strlen3(str)) == 0)
		{
            if(ft_strserarch(env->str,'=') == 1)
            {
                ptr = ft_strplusequal(env->str, 0);
			    return (ptr);
            }
		}
		env = env->next;
	}
	return (NULL);
}
char	*ft_strjoin1(char *s1, char *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

    
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen3(s1);
	s2_len = ft_strlen3(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}
void updatepwd(envp **env,char *str)
{
      envp *st;
      st = *env;
      while (st)
      {
            if(ft_strncmp(st->str,"PWD",3) == 0)
            {
                if(st->free == 1)
                free(st->str);
                st->free = 1;
                st->str = ft_strjoin1("PWD=",str);
                
                return;
            }
            
        st = st->next;
      }
      
}
void updateoldpwd(envp **env,char *str)
{
      envp *st;
      st = *env;
      while (st)
      {
            if(ft_strncmp(st->str,"OLDPWD",6) == 0)
            {
                if(st->free == 1)
                free(st->str);
                st->free = 1;
                st->str = ft_strjoin1("OLDPWD=",str);
                st->option = 1;
                return;
            }
            
        st = st->next;
      }
      
}
void	ft_cd(envp **env, char *str)
{
	char	*ptr = NULL;
    char    *ptr1;
    char    *oldpwd;
    char    *pwd = NULL;
    int value;
	
	
	oldpwd = getcwd(NULL, 1);
	if (str == NULL || ft_strcmp(str,"~") == 0)
	{
		ptr1 = ft_getenv(*env, "HOME");
        value = chdir(ptr1);
		if (value < 0)
		{
			perror("cd");
			//free(ptr);
            //free(ptr1);
			//exit(1);
		}
        else if (value == 0)
        {
            pwd = getcwd(NULL, 1);
            updatepwd(env,pwd);
            updateoldpwd(env,oldpwd);
            free(oldpwd);
            free(ptr1);
            free(pwd);
        }
	}
	else if(ft_strcmp(str,"-") == 0)
	{
	    ptr = ft_getenv(*env,"OLDPWD");
        if(ptr == NULL)
        {
            printf("OLDPWD not set\n");
            //free(ptr);
            free(oldpwd);
            return;
        }
        value = chdir(ptr);
        if (value < 0)
        {
            perror("cd");
            //free(ptr);
            //free(ptr1);
            exit(1);
        }
        else if (value == 0)
        {
            pwd = getcwd(NULL, 1);
            updatepwd(env,pwd);
            updateoldpwd(env,oldpwd);
            printf("%s\n",ptr);
            free(oldpwd);
            free(ptr);
            free(pwd);
            
        }
	}
    else
    {
        ptr = ft_strdupZ(str);
        value = chdir(ptr);
        if (value < 0)
	    {
		perror("cd");
		//free(ptr);
        //free(ptr1);
		//exit(1);
	    }
        else if (value == 0)
        {
            pwd = getcwd(NULL, 1);
            updatepwd(env,pwd);
            updateoldpwd(env,oldpwd);
            free(oldpwd);
            free(ptr);
            free(pwd);
        }
        
    }
	
	// if (k > 0)
	// 	free(ptr);
}

// int main(int argc,char **argv)
// {
//     ft_cd(argv[1]);
//     ft_pwd();
// }