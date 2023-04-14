/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:43:23 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:58:43 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_z	*ft_init_zz(t_Command_Table3 *table, char **env)
{
	t_z	*z;

	z = malloc(sizeof(t_z));
	z->dir = NULL;
	z->i = 0;
	z->r = 0;
	z->k = count(table);
	z->b = 0;
	z->aka = count_pi_herdo(table);
	z->pixa = malloc(sizeof(int *) * z->aka);
	z->num_pipes = count(table) - 1;
	while (z->i < z->aka)
		z->pixa[z->i++] = malloc(sizeof(int) * 2);
	z->pipes = malloc(sizeof(int *) * z->num_pipes);
	z->i = 0;
	while (z->i < z->num_pipes)
		z->pipes[z->i++] = malloc(sizeof(int) * 2);
	z->i = 0;
	z->mm = 0;
	z->env = env;
	return (z);
}

void	norm_work_exec(t_z *z, t_Command_Table3 *table)
{
	signal(SIGINT, SIG_DFL);
	if (z->i == 0)
		ft_close_pipe(z->num_pipes, z->pipes, z->i);
	else if (z->i == z->num_pipes)
		ft_close_pipe2(z->num_pipes, z->pipes, z->i);
	else if (z->i != 0)
		ft_close_pipe3(z->num_pipes, z->pipes, z->i);
	if (table->args[0] != NULL && ft_strncmp(table->args[0], ".", 2) == 0)
		the_point_case_in_multi_pipe();
	z->dir = opendir(table->args[0]);
	if (z->dir != NULL)
		if_dir_in_multi_pipe(z->dir, table);
	if (table->outfile != -2 && table->outfile != -1)
		dup2(table->outfile, STDOUT_FILENO);
	if (table->infile != -2 && table->infile != -1)
		dup2(table->infile, STDIN_FILENO);
	if (table->heredoc[0] != NULL && ft_strcmp(table->in_or_here,
			"heredoc") == 0)
		reading_from_heredoc(z->aka, z->pixa, &z->mm);
	else if (table->heredoc[0] != NULL)
		not_reading_from_heredoc(z->aka, z->pixa, &z->mm);
}

void	norm_builtin(t_envp **envp1, t_Command_Table3 *table)
{
	if (ft_strncmp(table->args[0], "cd", 3) == 0)
		(ft_cd(envp1, table->args[1]), exit(g_globale.exit_child));
	else if (ft_strncmp(table->args[0], "env", 4) == 0)
		(envv(*envp1), exit(0));
	else if (ft_strncmp(table->args[0], "unset", 6) == 0)
		unset_in_multi_pipe(table, envp1);
	else if (ft_strncmp(table->args[0], "export", 7) == 0)
		export_in_multipipe(table, envp1);
	else if (ft_strncmp(table->args[0], "echo", 5) == 0)
		echo_in_multipipe(table);
	else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
		(ft_pwd(), exit(0));
	else if (ft_strncmp(table->args[0], "exit", 5) == 0)
		exit_in_multipipe(table);
}

void	norm_wrok_exec2(t_Command_Table3 *table, t_pipex *pipex, char **env)
{
	if ((table->args[0][0] == '.' || table->args[0][0] == '/')
		&& access(table->args[0], F_OK) == 0)
		dir_in_multipipe(table, env);
	else if (table->args[0][0] == '.' || table->args[0][0] == '/')
		dir_in_multipipe2(table);
	execute_in_multpipe(pipex, table, env);
	if (table->args)
		cmd_not_found(table);
}

int	norm_last(t_z *z, t_Command_Table3 *table, t_pipex *pipex, t_envp **envp1)
{
	pathfinder(pipex, *envp1);
	g_globale.pid = malloc(sizeof(int) * count(table));
	g_globale.command_count = count(table);
	if (ft_creat_pipe(z->num_pipes, z->pipes) == 1)
		return (free(g_globale.pid), 1);
	return (0);
}
