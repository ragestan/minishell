/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:42:50 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 20:42:24 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_onecmd(t_Command_Table3 *table, t_pipex *pipex, t_envp **envp1,
		char **env)
{
	t_x	*x;

	x = ft_init_xx(table);
	if (table->heredoc[0] != NULL)
	{
		if (pipe(x->pipa) < 0)
			return (perror("pipe error"), (g_globale.exit_child = 255),
				ft_free_xx(x));
		ft_here_null_with_pipe(x->str, x->pipa, table->heredoc, &x->b);
	}
	if (builtin_check(table, envp1, &x->b, x->dir) == 1)
		return (ft_free_xx(x));
	g_globale.pid[x->i] = fork();
	if (g_globale.pid[x->i] < 0)
		(perror("fork error"), ft_free_xx(x), exit(-1));
	else if (g_globale.pid[x->i] == 0)
		child_unocmd(table, env, pipex, x->pipa);
	else
		ft_wait_unocmd(x, table);
	ft_free_xx(x);
}

int	count_pi_herdo(t_Command_Table3 *table3)
{
	int	aka;

	aka = 0;
	while (table3)
	{
		if (table3->heredoc[0] != NULL)
			aka++;
		table3 = table3->next;
	}
	return (aka);
}

void	open_pipe_nounocmd(t_z *z, int aka, int **pixa)
{
	int	tl;

	tl = 0;
	while (tl < aka)
	{
		if (pipe(pixa[tl]) == -1)
			return (perror("pipe error"), free_z(z),
				(void)(g_globale.exit_child = 255));
		tl++;
	}
}

t_y	*ft_init_yy(void)
{
	t_y	*y;

	y = malloc(sizeof(t_y));
	y->mm = 0;
	y->lb = 0;
	y->lj = 0;
	y->str = NULL;
	return (y);
}

void	ft_here_open(t_Command_Table3 *table, int aka, int **pixa, t_y *y)
{
	(signal(SIGQUIT, herquite), signal(SIGINT, SIG_DFL));
	while (table)
	{
		if (table->heredoc[0] != NULL)
		{
			y->str = heredocwhile(table->heredoc);
			write(pixa[y->mm][1], y->str, ft_strlen3(y->str));
			y->mm++;
		}
		table = table->next;
	}
	while (y->lb < aka)
	{
		close(pixa[y->lb][0]);
		close(pixa[y->lb][1]);
		y->lb++;
	}
	free(y->str);
	free(y);
	exit(0);
}
