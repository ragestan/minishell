/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:23:53 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 06:02:32 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*ptr;

	ptr = getcwd(NULL, 1);
	if (ptr == NULL)
		ptr = ft_getenv(g_globale.env1, "PWD");
	printf("%s\n", ptr);
	free(ptr);
}

void	updatepwd(envp **env, char *str)
{
	envp	*st;

	st = *env;
	while (st)
	{
		if (ft_strncmp(st->str, "PWD", 3) == 0)
		{
			if (st->free == 1)
				free(st->str);
			st->free = 1;
			st->str = ft_strjoin1("PWD=", str);
			return ;
		}
		st = st->next;
	}
}

void	updateoldpwd(envp **env, char *str)
{
	envp	*st;

	st = *env;
	while (st)
	{
		if (ft_strncmp(st->str, "OLDPWD", 6) == 0)
		{
			if (st->free == 1)
				free(st->str);
			st->free = 1;
			st->str = ft_strjoin1("OLDPWD=", str);
			st->option = 1;
			return ;
		}
		st = st->next;
	}
}

void	pathfinder(t_pipex *pipex, envp *envp1)
{
	envp	*tmp;

	tmp = envp1;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PATH=", 5) == 0)
		{
			pipex->save = tmp->str + 5;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		pipex->paths = NULL;
		return ;
	}
	pipex->paths = ft_split(pipex->save, ':');
}
