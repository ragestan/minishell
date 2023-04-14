/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:42:43 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 23:24:02 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_unocmd(t_x **x, t_Command_Table3 *table)
{
	int	status;

	waitpid(g_globale.pid[(*x)->i], &status, 0);
	close(table->outfile);
	close(table->infile);
	if (table->heredoc[0] != NULL)
	{
		close((*x)->pipa[0]);
	}
	if (WIFSIGNALED(status))
		g_globale.exit_child = 128 + WTERMSIG(status);
	if (WIFEXITED(status))
		g_globale.exit_child = WEXITSTATUS(status);
	free(g_globale.pid);
}

int	builtin_check(t_Command_Table3 *table, t_envp **envp1, t_x *x, DIR *dir)
{
	int	i;

	i = 1;
	if (x->b != 0 || table->args[0] == NULL)
		return (close1(x, table), free(g_globale.pid), 1);
	if (ft_strncmp(table->args[0], ".", 2) == 0)
		return (the_point_case_yay(), 1);
	dir = opendir(table->args[0]);
	if (dir != NULL)
		return (the_dir_case(dir, table->args[0]), 1);
	if (ft_strncmp(table->args[0], "cd", 3) == 0)
		return (ft_cd(envp1, table->args[1]), free(g_globale.pid), 1);
	else if (ft_strncmp(table->args[0], "env", 4) == 0)
		return (envv(*envp1), free(g_globale.pid), 1);
	else if (ft_strncmp(table->args[0], "unset", 6) == 0)
		return (ft_unset_norm(table->args, envp1, i, 0), 1);
	else if (ft_strncmp(table->args[0], "export", 7) == 0)
		return (ft_export_norm(table->args, envp1, i), 1);
	else if (ft_strncmp(table->args[0], "echo", 5) == 0)
		return (ft_export(table->args), 1);
	else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
		return (g_globale.exit_child = 0, free(g_globale.pid), ft_pwd(), 1);
	else if (ft_strncmp(table->args[0], "exit", 5) == 0)
		ft_exiit(table->args);
	return (0);
}

void	child_unocmd(t_Command_Table3 *table, char **env, t_pipex *pipex,
		int *pipa)
{
	if (table->outfile != -2 && table->outfile != -1)
		(dup2(table->outfile, STDOUT_FILENO), close(table->outfile));
	if (table->infile != -2 && table->infile != -1)
		(dup2(table->infile, STDIN_FILENO), close(table->infile));
	if (table->heredoc[0] != NULL && ft_strcmp(table->in_or_here,
			"heredoc") == 0)
		(dup2(pipa[0], STDIN_FILENO), close(pipa[0]), close(pipa[1]));
	else if (table->heredoc[0] != NULL)
		(close(pipa[0]), close(pipa[1]));
	if ((table->args[0][0] == '.' || table->args[0][0] == '/')
		&& access(table->args[0], F_OK) == 0)
	{
		if (execve(table->args[0], table->args, env) == -1)
			(write(2, "minishell: ", 11), perror(table->args[0]), exit(126));
	}
	else if (table->args[0][0] == '.' || table->args[0][0] == '/')
		(write(2, "minishell: ", 11), perror(table->args[0]), exit(127));
	pipex->i = 0;
	while (pipex->paths && pipex->paths[pipex->i])
	{
		if (ft_execut_now(pipex, table, env) == 0)
			break ;
	}
	if (table->args)
		ft_norm(table->args[0]);
}

void	ft_free_xx(t_x *x)
{
	int	i;

	i = 0;
	while (i < x->num_pipes)
	{
		free(x->pipes[i]);
		i++;
	}
	free(x->pipa);
	free(x->pipes);
	free(x);
}

t_x	*ft_init_xx(t_Command_Table3 *table)
{
	t_x	*x;
	int	i;

	x = malloc(sizeof(t_x));
	i = 0;
	x->dir = NULL;
	x->i = 0;
	x->b = 0;
	x->num_pipes = count(table) - 1;
	x->str = NULL;
	x->pipa = malloc(sizeof(int) * 2);
	x->pipes = malloc(sizeof(int *) * x->num_pipes);
	while (i < x->num_pipes)
	{
		x->pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (x);
}
