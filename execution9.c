/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:43:18 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 05:56:40 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_Command_Table3 *table)
{
	if (ft_strserarch(table->args[0], '/') == 1)
		ft_error1("minishell: No such file or directory: ", table->args[0]);
	else
		ft_error1("minishell: command not found: ", table->args[0]);
}

void	closing_pipes(int **pixa, int *mm)
{
	(close(pixa[*mm][0]), close(pixa[*mm][1]));
	(*mm)++;
}

void	closing_more_pipes(int aka, int **pixa)
{
	int	xx;

	xx = 0;
	while (xx < aka)
	{
		(close(pixa[xx][0]), close(pixa[xx][1]));
		xx++;
	}
}

void	waiting_for_child(int num_pipes, int **pipes)
{
	int	status;
	int	j;

	waitpid(g_globale.pid[num_pipes], &status, 0);
	j = 0;
	while (j < num_pipes)
	{
		(close(pipes[j][0]), close(pipes[j][1]));
		j++;
	}
	j = 0;
	while (j < num_pipes)
		waitpid(g_globale.pid[j++], NULL, 0);
	if (WIFSIGNALED(status))
		g_globale.exit_child = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		g_globale.exit_child = WEXITSTATUS(status);
}

void	c_more_pipes(t_Command_Table3 *table, int num_pipes, int **pipes, int i)
{
	if (i == 0)
		close(pipes[i][1]);
	else if (i == num_pipes)
		(close(pipes[i - 1][0]), close(pipes[i - 1][1]));
	else
		(close(pipes[i][1]), close(pipes[i - 1][0]), close(pipes[i - 1][1]));
	(close(table->outfile), close(table->infile));
}
