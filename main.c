/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 21:12:24 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	int	i;

	i = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	while (i < g_globale.command_count)
	{
		if (g_globale.pid[i] != 0)
			kill(g_globale.pid[i], SIGINT);
		i++;
	}
	if (g_globale.idheredok != 0)
	{
		g_globale.exit_child = 1;
		kill(g_globale.idheredok, SIGINT);
	}
}

void	herquite(int sig)
{
	(void)sig;
	rl_on_new_line();
	//rl_redisplay();
	return ;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_globale.idheredok != 0)
	{
		kill(g_globale.idheredok, SIGQUIT);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

int	count(t_Command_Table3 *table)
{
	int	i;

	i = 0;
	while (table)
	{
		i++;
		table = table->next;
	}
	return (i);
}

t_Command_Table3	*ft_all(envp *env)
{
	char				*new;
	char				**split;
	int					i;
	int					k;
	t_Command_Table		*table;
	t_Command_Table2	w;
	t_Command_Table3	*last_table;
	t_Command_Table3	*tmp;
	struct termios		term;
	struct termios		oldterm;

	k = 0;
	i = 0;
	split = NULL;
	tcgetattr(0, &term);
	oldterm = term;
	term.c_lflag &= ~ECHOCTL;
	table = NULL;
	tcsetattr(0, TCSANOW, &term);
	new = readline("minishell$ ");
	tcsetattr(0, TCSANOW, &oldterm);
	if (!new)
		(write(1, "exit\n", 5), exit(g_globale.exit_child));
	add_history(new);
	if (check_all(new) != -1)
		return (ft_all_nor2(split,new,0,i), NULL);
	new = new_new(new, -1);
	split = ft_split(new, 12);
	w = ft_init();
	while (split[i])
		i = ft_make(&table, split, &w);
	if (table == NULL)
		return (free(new), ft_free(split), NULL);
	table = ft_all_nor(table, env);
	while (table)
		last_table = ft_make_last(&table, last_table, &k);
	tmp = last_table;
	while (tmp)
	{
		last_table->args = arg(last_table->args, 0, 2);
		tmp = tmp->next;
	}
	return (free(new),ft_free(split),freestack(&table),last_table);
}

int	main(int argc, char **argv, char **env)
{
	t_Command_Table3	*last_table;
	envp				*env1;
	t_pipex				pipex;
	int					r;

	// char *new;
	// char **split;
	// int i;
	// int k;
	// t_Command_Table *table;
	// t_Command_Table2 w;
	//expand in echo
	//exit in builtin
	g_globale.exit_child = 0;
	env1 = NULL;
	(void)argc;
	(void)argv;
	printf("/-----------------------------\n");
	//add OLDPWD
	r = 0;
	//int j = 1;
	//int error = 0;
	while (env[r] != NULL)
		r++;
	r -= 2;
	while (r >= 0)
	{
		make_node(&env1, env[r]);
		r--;
	}
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, sigquit_handler));
	g_globale.env1 = env1;
	while (1)
	{
		last_table = ft_all(env1);
       
		//system("leaks minishell");
		if (last_table == NULL)
			continue ;
		//printlinkdlist(last_table);
		if (last_table->infile != -1 && last_table->outfile != -1)
		{
			shell_with_pipes(last_table, env, &pipex, &env1);
			ft_free(pipex.paths);
		}
		close(last_table->outfile);
		close(last_table->infile);
		// execve("/usr/bin/make", last_table->args, NULL);
		freestack_3(&last_table);
	}
}
