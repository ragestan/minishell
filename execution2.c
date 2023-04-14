/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:39:52 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 06:54:06 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_creat_pipe(int num_pipes, int **pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
			i--;
			perror("pipe 2error");
			while (i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				i--;
			}
			return ((void)(g_globale.exit_child = 255), 1);
		}
		i++;
	}
	return (0);
}

void	ft_here_null_with_pipe(char *str, int *pipa, char **heredoc, int *b)
{
	int	status;

	g_globale.idheredok = 0;
	g_globale.idheredok = fork();
	if (g_globale.idheredok == 0)
	{
		signal(SIGINT, SIG_DFL);
		str = heredocwhile(heredoc);
		if (str)
			write(pipa[1], str, ft_strlen3(str));
		close(pipa[1]);
		close(pipa[0]);
		free(str);
		exit(0);
	}
	else
	{
		waitpid(g_globale.idheredok, &status, 0);
		if (WIFSIGNALED(status))
		{
			g_globale.exit_child = 1;
			*b = 1;
		}
		close(pipa[1]);
	}
}

void	the_point_case_yay(void)
{
	printf("minishell: .: filename argument required\n");
	printf(" .: usage: . filename [arguments]\n");
	g_globale.exit_child = 2;
	free(g_globale.pid);
}

void	the_dir_case(DIR *dir, char *arg)
{
	closedir(dir);
	printf("mini: %s: is a directory\n", arg);
	g_globale.exit_child = 126;
	free(g_globale.pid);
}

void	ft_unset_norm(char **args, envp **envp1, int i, int j)
{
	while (args[i])
	{
		j = unset(envp1, args[i]);
		if (j == 1)
			g_globale.exit_child = 1;
		i++;
	}
	if (i == 1)
		g_globale.exit_child = 0;
	free(g_globale.pid);
}
