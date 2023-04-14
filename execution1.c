/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:12:37 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:33:02 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_last2(t_z *z)
{
	closing_more_pipes(z->aka, z->pixa);
	if (z->r)
		waiting_for_child(z->num_pipes, z->pipes);
	free(g_globale.pid);
}

t_z	*fork_update_r_value(t_z *z)
{
	z->r = 1;
	g_globale.pid[z->i] = fork();
	return (z);
}

t_z	*norm_close_pipes(t_z *z, t_Command_Table3 *table)
{
	if (table->heredoc[0] != NULL)
		closing_pipes(z->pixa, &z->mm);
	c_more_pipes(table, z->num_pipes, z->pipes, z->i);
	z->i++;
	return (z);
}

t_Command_Table3	*norm_last_realy(t_z *z, t_Command_Table3 *tmp,
		t_envp **envp1, t_pipex *pipex)
{
	t_Command_Table3	*table;

	table = tmp;
	z = fork_update_r_value(z);
	if (g_globale.pid[z->i] < 0)
		(perror("fork error"), free_z(z), exit(-1));
	else if (g_globale.pid[z->i] == 0)
		(norm_work_exec(z, table), norm_builtin(envp1, table),
			norm_wrok_exec2(table, pipex, z->env));
	else
	{
		z = norm_close_pipes(z, table);
		table = table->next;
	}
	return (table);
}

void	shell_with_pipes(t_Command_Table3 *table, char **env, t_pipex *pipex,
		t_envp **envp1)
{
	t_z	*z;

	z = ft_init_zz(table, env);
	pipex->paths = NULL;
	if (norm_last(z, table, pipex, envp1) == 1)
		return (free_z(z));
	if (z->num_pipes == 0)
		ft_onecmd(table, pipex, envp1, env);
	else
	{
		if (z->aka != 0)
			(open_pipe_nounocmd(z, z->aka, z->pixa), ft_idk(table, z->aka,
					z->pixa, &z->b));
		while (!z->b && z->i < z->k)
			table = norm_last_realy(z, table, envp1, pipex);
		norm_last2(z);
	}
	free_z(z);
}
