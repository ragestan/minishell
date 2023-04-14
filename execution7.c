/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:43:05 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 05:56:49 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_dir_in_multi_pipe(DIR *dir, t_Command_Table3 *table)
{
	closedir(dir);
	write(2, "minishell: is a directory : ", 28);
	write(2, table->args[0], ft_strlen3(table->args[0]));
	write(2, "\n", 1);
	g_globale.exit_child = 126;
	exit(g_globale.exit_child);
}

void	reading_from_heredoc(int aka, int **pixa, int *mm)
{
	int	la;
	int	ss;

	la = 0;
	ss = *mm;
	if (dup2(pixa[ss][0], STDIN_FILENO) == -1)
		(perror("dup2 error "), exit(-1));
	while (la < aka)
	{
		close(pixa[la][0]);
		close(pixa[la][1]);
		la++;
	}
	(*mm)++;
}

void	not_reading_from_heredoc(int aka, int **pixa, int *mm)
{
	int	la;

	la = 0;
	while (la < aka)
	{
		close(pixa[la][0]);
		close(pixa[la][1]);
		la++;
	}
	(*mm)++;
}

void	unset_in_multi_pipe(t_Command_Table3 *table, envp **envp1)
{
	int	i;

	i = 1;
	g_globale.exit_child = 0;
	while (table->args[i])
	{
		unset(envp1, table->args[i]);
		i++;
	}
	exit(0);
}

void	export_in_multipipe(t_Command_Table3 *table, envp **envp1)
{
	int	i;

	g_globale.exit_child = 0;
	i = 1;
	if (table->args[1] == NULL)
		(export(envp1, NULL), exit(0));
	else
	{
		while (table->args[i])
		{
			export(envp1, table->args[i]);
			i++;
		}
	}
	exit(0);
}
