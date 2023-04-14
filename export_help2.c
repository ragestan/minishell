/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:17:22 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:39:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_putstredit(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		if (s[i] == '=' && j == 0)
		{
			write(1, "\"", 1);
			j = 1;
		}
		i++;
	}
	write(1, "\"", 1);
}

void	printnode_export(t_envp *stp)
{
	t_envp	*st;

	st = stp;
	while (st)
	{
		if (st->prinlast == 1)
		{
			ft_putstr_fd("declare -x ", 1);
			if (st->option == 1)
				ft_putstredit(st->str);
			else
				ft_putstr_fd(st->str, 1);
			printf("\n");
		}
		st = st->next;
	}
}

void	ft_writeme1(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_globale.exit_child = 1;
}

void	ft_writeme2(t_envp **env1)
{
	printnodealpha(*env1);
	g_globale.exit_child = 0;
}
