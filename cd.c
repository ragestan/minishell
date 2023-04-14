/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:27:59 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:40:04 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_envp *env, char *str)
{
	char	*ptr;

	ptr = NULL;
	while (env)
	{
		if (ft_strncmp(env->str, str, ft_strlen3(str)) == 0)
		{
			if (ft_strserarch(env->str, '=') == 1)
			{
				ptr = ft_strplusequal(env->str, 0);
				return (ptr);
			}
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_cd_help1(t_envp **env, t_cdd *cdd)
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
		updatepwd(env, cdd->pwd);
		updateoldpwd(env, cdd->oldpwd);
		free(cdd->oldpwd);
		free(cdd->ptr1);
		free(cdd->pwd);
		g_globale.exit_child = 0;
	}
}

void	ft_cd_help2(t_envp **env, t_cdd *cdd)
{
	cdd->ptr = ft_getenv(*env, "OLDPWD");
	if (cdd->ptr == NULL)
	{
		printf("cd :OLDPWD not set\n");
		free(cdd->oldpwd);
		g_globale.exit_child = 1;
		return ;
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
		updatepwd(env, cdd->pwd);
		updateoldpwd(env, cdd->oldpwd);
		printf("%s\n", cdd->ptr);
		(free(cdd->oldpwd), free(cdd->ptr), free(cdd->pwd));
		g_globale.exit_child = 0;
	}
}

void	ft_cd_help3(t_envp **env, t_cdd *cdd, char *str)
{
	cdd->ptr = ft_strdup_z(str);
	cdd->value = chdir(cdd->ptr);
	if (cdd->value < 0)
	{
		printf("cd: %s: no such file or directory \n", cdd->ptr);
		g_globale.exit_child = 1;
		free(cdd->oldpwd);
		free(cdd->ptr);
	}
	else if (cdd->value == 0)
	{
		cdd->pwd = getcwd(NULL, 1);
		updatepwd(env, cdd->pwd);
		updateoldpwd(env, cdd->oldpwd);
		free(cdd->oldpwd);
		free(cdd->ptr);
		free(cdd->pwd);
		g_globale.exit_child = 0;
	}
}

void	ft_cd(t_envp **env, char *str)
{
	t_cdd	cdd;

	cdd.ptr = NULL;
	cdd.ptr1 = NULL;
	cdd.pwd = NULL;
	cdd.oldpwd = getcwd(NULL, 1);
	if (cdd.oldpwd == NULL)
		cdd.oldpwd = ft_getenv(*env, "PWD");
	if (str == NULL || ft_strcmp(str, "~") == 0)
		ft_cd_help1(env, &cdd);
	else if (ft_strcmp(str, "-") == 0)
		ft_cd_help2(env, &cdd);
	else
		ft_cd_help3(env, &cdd, str);
}
