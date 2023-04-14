/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:42:57 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 07:01:55 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_idk(t_Command_Table3 *table, int aka, int **pixa, int *b)
{
	t_y	*y;

	y = ft_init_yy();
	g_globale.idheredok = fork();
	if (g_globale.idheredok < 0)
		(perror("fork error"), free(y), exit(-1));
	else if (g_globale.idheredok == 0)
		ft_here_open(table, aka, pixa, y);
	else
	{
		waitpid(g_globale.idheredok, b, 0);
		while (y->lj < aka)
		{
			close(pixa[y->lj][1]);
			y->lj++;
		}
		if (WIFSIGNALED(*b))
			(*b) = 1;
		free(y);
	}
}

void	ft_close_pipe(int num_pipes, int **pipes, int i)
{
	int	l;

	l = 0;
	dup2(pipes[i][1], 1);
	while (l < num_pipes)
	{
		close(pipes[l][0]);
		close(pipes[l][1]);
		l++;
	}
}

void	ft_close_pipe2(int num_pipes, int **pipes, int i)
{
	int	j;

	dup2(pipes[i - 1][0], 0);
	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	ft_close_pipe3(int num_pipes, int **pipes, int i)
{
	int	j;

	dup2(pipes[i - 1][0], STDIN_FILENO);
	dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	the_point_case_in_multi_pipe(void)
{
	write(2, "minishell: .: filename argument required\n", 41);
	write(2, ".: usage: . filename [arguments]\n", 33);
	g_globale.exit_child = 2;
	exit(g_globale.exit_child);
}
