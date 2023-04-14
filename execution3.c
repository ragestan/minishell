/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:40:19 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:33:19 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_norm(char **args, t_envp **envp1, int i)
{
	g_globale.exit_child = 0;
	if (args[1] == NULL)
	{
		export(envp1, NULL);
		free(g_globale.pid);
		return ;
	}
	else
	{
		while (args[i])
		{
			export(envp1, args[i]);
			i++;
		}
	}
	free(g_globale.pid);
}

void	ft_export(char **args)
{
	if (ft_test(args) == 1)
		echo(args[1], ft_collect(args, 2));
	else
		echo(NULL, ft_collect(args, 1));
	free(g_globale.pid);
	g_globale.exit_child = 0;
}

void	ft_exiit(char **args)
{
	free(g_globale.pid);
	printf("exit\n");
	if (args[1] != NULL)
	{
		if (ft_isdigit1(args[1]) == 0)
			g_globale.exit_child = ft_atoi(args[1]);
		else if (ft_isdigit1(args[1]) == 1)
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_globale.exit_child = 255;
			exit(g_globale.exit_child);
		}
		if (args[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			g_globale.exit_child = 1;
			return ;
		}
	}
	exit(g_globale.exit_child);
}

int	ft_execut_now(t_pipex *pipex, t_Command_Table3 *table, char **env)
{
	pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], "/");
	pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],
			table->args[0]);
	if (access(pipex->paths[pipex->i], F_OK) == 0)
	{
		if (table->args[0][0] == '\0')
			return (0);
		if (execve(pipex->paths[pipex->i], table->args, env) == -1)
			(perror("execve error"), exit(126));
	}
	pipex->i++;
	free(pipex->paths[pipex->i - 1]);
	return (1);
}

void	ft_norm(char *arg)
{
	if (ft_strserarch(arg, '/') == 1)
		ft_error1("minishell: No such file or directory: ", arg);
	else
		ft_error1("minishell: command not found: ", arg);
}
