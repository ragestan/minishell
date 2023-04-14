/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:04:31 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 15:39:05 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printnodeenv(t_envp *str)
{
	t_envp	*st;

	st = str;
	while (st)
	{
		if (st->option == 1)
			printf("%s\n", st->str);
		st = st->next;
	}
}

int	valideinput(char *str)
{
	int	i;

	i = 0;
	if ((ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0) && str[i] != '_')
		return (1);
	i++;
	while (str[i] != '=' && str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '=' || str[i] == '_')
			i++;
		else if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				i++;
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_strnstredit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_strdupedit(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen3(s1) - 1;
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[j] != '\0')
	{
		if (s1[i] == '+' && s1[i + 1] == '=')
			j++;
		p[i] = s1[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	printnodealpha(t_envp *str)
{
	t_envp	*st;
	int		i;

	st = str;
	i = 32;
	while (i++ <= 126)
	{
		while (st)
		{
			if (st->str[0] == i && st->prinlast == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				if (st->option == 1)
					ft_putstredit(st->str);
				else
					ft_putstr_fd(st->str, 1);
				printf("\n");
				st = st->next;
			}
			else
				st = st->next;
		}
		st = str;
	}
	printnode_export(str);
}
