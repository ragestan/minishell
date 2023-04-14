/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:52:42 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 23:56:16 by zbentale         ###   ########.fr       */
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
	g_globale.exit_child = 1;
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

t_w	*ft_init_w(void)
{
	t_w	*w;

	w = malloc(sizeof(t_w));
	w->k = 0;
	w->i = 0;
	w->split = NULL;
	w->table = NULL;
	return (w);
}
