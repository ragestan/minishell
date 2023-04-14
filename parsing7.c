/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:32:43 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 15:42:33 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_norm2(t_envp *tmp, char *arg, char *new, t_int *w)
{
	w->k = 0;
	w->z = 0;
	while (tmp)
	{
		if (ft_strcmpedit2(arg + w->i + 1, tmp->str, ft_is_ad(arg + w->i
					+ 1)) == 0)
		{
			w->z = ft_is_ad(arg + w->i + 1);
			new = ft_strplusequal(tmp->str, 0);
			w->j = w->j + ft_strlen3(new);
			free(new);
			w->i++;
			w->k = 0;
			while (arg[w->i] && w->k < w->z)
				ft_plusi(&w->k, &w->i);
			w->k = 0;
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_strcmpedit2(char *s1, char *s2, size_t j)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '=' || s2[i] != '=') && (s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] != '=' || s2[i] != '\0') && (s1[i] != '\0' || s2[i] != '=')
		&& i < j)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '=')
		return (0);
	return (-1);
}

int	ft_is_ad(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97
				&& c <= 122) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
			|| (c == '_'))
			i++;
		else
			return (i);
	}
	return (i);
}

void	ft_env_norm(char *arg, char *new, t_int *w)
{
	w->z = ft_is_ad(arg + w->i + 1);
	new = ft_itoa(g_globale.exit_child);
	w->j = w->j + ft_strlen3(new);
	free(new);
	w->i = w->i + 2;
	w->k = 0;
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	j;

	j = n;
	i = ft_count(n);
	if (n < 0)
	{
		j = -j;
		i++;
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i--)
	{
		str[i] = j % 10 + '0';
		j /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
