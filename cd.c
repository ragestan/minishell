/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:27:59 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/09 17:19:48 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//should fix CD only;
// void	ft_pwd(void)
// {
// 	char	*ptr;

// 	ptr = getcwd(NULL, 1);
// 	printf("%s\n", ptr);
// 	free(ptr);
// }
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
char *ft_strjoin3(char *s1, char *s2)
{
    char	*p;
    int		s1_len;
    int		s2_len;
    int		i;
    int		j;

    i = 0;
    j = 0;
    if(s2 == NULL)
    {
        s2_len = 0;
        s1_len = ft_strlen3(s1);
    }  
    else if(s1 == NULL)
    {
        s1_len = 0;
        s2_len = ft_strlen3(s2);
    }
    else
    {
        s1_len = ft_strlen3(s1);
        s2_len = ft_strlen3(s2);
    }
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
    free(s1);
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
void ft_cd_help1(envp **env, t_cdd *cdd)
{
    	cdd->ptr1 = ft_getenv(*env, "HOME");
        cdd->value = chdir(cdd->ptr1);
		if (cdd->value < 0)
		{
			write(2, "cd: HOME not set\n", 18);
             g_globale.exit_child = 1;
             free(cdd->oldpwd);
                free(cdd->ptr1);
		}
        else if (cdd->value == 0)
        {
            cdd->pwd = getcwd(NULL, 1);
            updatepwd(env,cdd->pwd);
            updateoldpwd(env,cdd->oldpwd);
            free(cdd->oldpwd);
            free(cdd->ptr1);
            free(cdd->pwd);
            g_globale.exit_child = 0;
        }
}
void ft_cd_help2(envp **env, t_cdd *cdd)
{
     cdd->ptr = ft_getenv(*env,"OLDPWD");
        if(cdd->ptr == NULL)
        {
            printf("cd :OLDPWD not set\n");
            free(cdd->oldpwd);
            g_globale.exit_child = 1;
            return;
        }
        cdd->value = chdir(cdd->ptr);
        if (cdd->value < 0)
        {
            perror("cd");
            g_globale.exit_child = 1;
            free(cdd->oldpwd);
            free(cdd->ptr);
        }
        else if (cdd->value == 0)
        {
            cdd->pwd = getcwd(NULL, 1);
            updatepwd(env,cdd->pwd);
            updateoldpwd(env,cdd->oldpwd);
            printf("%s\n",cdd->ptr);
            free(cdd->oldpwd);
            free(cdd->ptr);
            free(cdd->pwd);
            g_globale.exit_child = 0;
        }
}

void ft_cd_help3(envp **env , t_cdd *cdd ,char *str)
{
       cdd->ptr = ft_strdupZ(str);
        cdd->value = chdir(cdd->ptr);
        if (cdd->value < 0)
	    {
		write(2,"cd: HOME not set\n",18);
        g_globale.exit_child = 1;
        free(cdd->oldpwd);
        free(cdd->ptr);
        
        
	    }
        else if (cdd->value == 0)
        {
            
            cdd->pwd = getcwd(NULL, 1);
            updatepwd(env,cdd->pwd);
            updateoldpwd(env,cdd->oldpwd);
            free(cdd->oldpwd);
            free(cdd->ptr);
            free(cdd->pwd);
            g_globale.exit_child = 0;
        }
}

void	ft_cd(envp **env, char *str)
{
	// char	*ptr = NULL;
    // char    *ptr1;
    // char    *oldpwd;
    // char    *pwd = NULL;
    // int value;
    t_cdd cdd;
    cdd.ptr = NULL;
    cdd.ptr1 = NULL;
    cdd.pwd = NULL;
	
	
	cdd.oldpwd = getcwd(NULL, 1);
    if(cdd.oldpwd == NULL)
        cdd.oldpwd = ft_getenv(*env,"PWD");
	if (str == NULL || ft_strcmp(str,"~") == 0)
	{
		// cdd.ptr1 = ft_getenv(*env, "HOME");
        // cdd.value = chdir(cdd.ptr1);
		// if (cdd.value < 0)
		// {
		// 	perror("cd");
        //      g_globale.exit_child = 1;
		// }
        // else if (cdd.value == 0)
        // {
        //     cdd.pwd = getcwd(NULL, 1);
        //     updatepwd(env,cdd.pwd);
        //     updateoldpwd(env,cdd.oldpwd);
        //     free(cdd.oldpwd);
        //     free(cdd.ptr1);
        //     free(cdd.pwd);
        //     g_globale.exit_child = 0;
        // }
        ft_cd_help1(env,&cdd);
	}
	else if(ft_strcmp(str,"-") == 0)
	{
	//    cdd.ptr = ft_getenv(*env,"OLDPWD");
    //     if(cdd.ptr == NULL)
    //     {
    //         printf("OLDPWD not set\n");
    //         free(cdd.oldpwd);
    //         g_globale.exit_child = 1;
    //         return;
    //     }
    //     cdd.value = chdir(cdd.ptr);
    //     if (cdd.value < 0)
    //     {
    //         perror("cd");
    //         g_globale.exit_child = 1;
    //     }
    //     else if (cdd.value == 0)
    //     {
    //         cdd.pwd = getcwd(NULL, 1);
    //         updatepwd(env,cdd.pwd);
    //         updateoldpwd(env,cdd.oldpwd);
    //         printf("%s\n",cdd.ptr);
    //         free(cdd.oldpwd);
    //         free(cdd.ptr);
    //         free(cdd.pwd);
    //         g_globale.exit_child = 0;
    //     }
        ft_cd_help2(env,&cdd);
	}
    else
    {
        // cdd.ptr = ft_strdupZ(str);
        // cdd.value = chdir(cdd.ptr);
        // if (cdd.value < 0)
	    // {
		// perror("cd");
        // g_globale.exit_child = 1;
	    // }
        // else if (cdd.value == 0)
        // {
            
        //     cdd.pwd = getcwd(NULL, 1);
        //     updatepwd(env,cdd.pwd);
        //     updateoldpwd(env,cdd.oldpwd);
        //     free(cdd.oldpwd);
        //     free(cdd.ptr);
        //     free(cdd.pwd);
        //     g_globale.exit_child = 0;
        // }
        ft_cd_help3(env,&cdd,str);
    }
}

// int main(int argc,char **argv)
// {
//     ft_cd(argv[1]);
//     ft_pwd();
// }