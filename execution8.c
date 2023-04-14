/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:43:10 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 07:02:24 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_in_multipipe(t_Command_Table3 *table)
{
	if (ft_test(table->args) == 1)
		echo(table->args[1], ft_collect(table->args, 2));
	else
		echo(NULL, ft_collect(table->args, 1));
	exit(0);
}

void	exit_in_multipipe(t_Command_Table3 *table)
{
	if (table->args[1] != NULL)
	{
		if (table->args[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			g_globale.exit_child = 1;
			exit(1);
		}
		if (ft_isdigit1(table->args[1]) == 0)
			g_globale.exit_child = ft_atoi(table->args[1]);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				table->args[1]);
			g_globale.exit_child = 255;
			exit(g_globale.exit_child);
		}
	}
	exit(g_globale.exit_child);
}

void	dir_in_multipipe(t_Command_Table3 *table, char **env)
{
	if (execve(table->args[0], table->args, env) == -1)
		(perror("execve error"), exit(126));
}

void	dir_in_multipipe2(t_Command_Table3 *table)
{
	write(2, "minishell: ", 11);
	perror(table->args[0]);
	g_globale.exit_child = 127;
	exit(g_globale.exit_child);
}

void	execute_in_multpipe(t_pipex *pipex, t_Command_Table3 *table, char **env)
{
	pipex->i = 0;
	while (pipex->paths && pipex->paths[pipex->i])
	{
		pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], "/");
		pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],
				table->args[0]);
		if (access(pipex->paths[pipex->i], F_OK) == 0)
		{
			if (table->args[0][0] == 0)
				break ;
			if (execve(pipex->paths[pipex->i], table->args, env) == -1)
				(perror("execve error"), exit(126));
		}
		pipex->i++;
	}
}
