/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:22:41 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 05:55:49 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

size_t	ft_strlen3(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strserarch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

envp	*sort_list(envp *lst, int (*cmp)(char *, char *))
{
	char	*swap;
	int		swapint;
	envp	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->str, lst->next->str)) >= 0)
		{
			swap = lst->str;
			swapint = lst->option;
			lst->str = lst->next->str;
			lst->option = lst->next->option;
			lst->next->str = swap;
			lst->next->option = swapint;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	export(envp **env1, char *str)
{
	static int	x;
	char		*stredit;

	x = 0;
	stredit = NULL;
	if (str == NULL)
		ft_writeme2(env1);
	else
	{
		x = valideinput(str);
		if (x == 1)
			ft_writeme1(str);
		ft_export_help(str, env1, x, stredit);
	}
}
