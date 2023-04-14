/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 07:05:00 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_w	*ft_all_norm_last(t_w *w)
{
	tcgetattr(0, &w->term);
	w->oldterm = w->term;
	w->term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &w->term);
	w->new = readline("minishell$ ");
	tcsetattr(0, TCSANOW, &w->oldterm);
	if (!w->new)
		(write(1, "exit\n", 5), free(w->new), free(w),
			exit(g_globale.exit_child));
	add_history(w->new);
	return (w);
}

t_Command_Table3	*ft_all(envp *env)
{
	t_w	*w;

	w = ft_init_w();
	w = ft_all_norm_last(w);
	if (check_all(w->new) != -1)
		return (ft_all_nor2(w->split, w->new, 0, w->i), free(w), NULL);
	w->new = new_new(w->new, -1);
	w->split = ft_split(w->new, 12);
	w->z = ft_init();
	while (w->split[w->i])
		w->i = ft_make(&w->table, w->split, &w->z);
	if (w->table == NULL)
		return (free(w->new), ft_free(w->split), free(w), NULL);
	w->table = ft_all_nor(w->table, env);
	while (w->table)
		w->last_table = ft_make_last(&w->table, w->last_table, &w->k);
	w->tmp = w->last_table;
	while (w->tmp)
	{
		w->last_table->args = arg(w->last_table->args, 0, 2);
		w->tmp = w->tmp->next;
	}
	return (free(w->new), ft_free(w->split), freestack(&w->table), free(w),
		w->last_table);
}

void	ft_none_env(char **env, envp **env1)
{
	char	*ptr;

	ptr = NULL;
	if (env[0] == NULL)
	{
		ptr = getcwd(NULL, 0);
		ft_lstadd_back(env1, ft_lstnew(ptr, 1));
		ft_lstadd_back(env1, ft_lstnew("SHLVL=1", 1));
		free(ptr);
	}
}

void	norm_main(char **env, int argc, envp **env1)
{
	while (env[argc] != NULL)
		argc++;
	argc -= 2;
	while (argc >= 0)
		make_node(env1, env[argc--]);
	ft_none_env(env, env1);
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, sigquit_handler));
	g_globale.env1 = *env1;
}

int	main(int argc, char **argv, char **env)
{
	t_Command_Table3	*last_table;
	envp				*env1;
	t_pipex				pipex;

	g_globale.exit_child = 0;
	env1 = NULL;
	(void)argv;
	argc = 0;
	norm_main(env, argc, &env1);
	while (1)
	{
		last_table = ft_all(env1);
		if (last_table == NULL)
			continue ;
		if (last_table->infile != -1 && last_table->outfile != -1)
			(shell_with_pipes(last_table, env, &pipex, &env1),
				ft_free(pipex.paths));
		(close(last_table->outfile), close(last_table->infile),
			freestack_3(&last_table));
	}
}
