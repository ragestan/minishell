/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing15.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:04:14 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 06:08:49 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Command_Table	*ft_all_nor(t_Command_Table *table, envp *env)
{
	table = ft_var(table, env);
	table = ft_cote(table);
	return (table);
}

void	ft_all_nor2_nor(void)
{
	g_globale.exit_child = 258;
	write(2, "minishell: syntax error near unexpected token `redirection'\n",
		61);
}

char	**ft_all_nor2_nor2(char **split, char *new)
{
	new = new_new(new, check_all(new));
	split = ft_split(new, 12);
	free(new);
	return (split);
}

void	ft_all_nor2(char **split, char *new, int g_fork, int i)
{
	char	*new2;

	ft_all_nor2_nor();
	split = ft_all_nor2_nor2(split, new);
	while (split[i++])
	{
		if (split[i - 1][0] == '<' && split[i - 1][1] == '<' && split[i
			- 1][2] == '\0')
		{
			if (split[i])
			{
				new = ft_strdup3(split[i]);
				g_fork = fork();
				if (g_fork == 0)
				{
					signal(SIGINT, SIG_DFL);
					new2 = heredocstring(new);
					(free(new), free(new2), exit(258));
				}
				else
					waitpid(g_fork, NULL, 0);
				free(new);
			}
		}
	}
	ft_free(split);
}
