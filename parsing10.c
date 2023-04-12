/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:50:00 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:09:18 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlencote(const char *c, size_t i, size_t j)
{
	while (c[i] != '\0')
	{
		if (c[i] == '\"')
		{
			i++;
			while (c[i] && c[i] != '\"')
				ft_plus(&i, &j);
			if (c[i])
				i++;
			continue ;
		}
		if (c[i] == '\'')
		{
			i++;
			while (c[i] && c[i] != '\'')
				ft_plus(&i, &j);
			if (c[i])
				i++;
			continue ;
		}
		ft_plus(&i, &j);
	}
	return (j);
}

char	*ft_cote2_norm(char *dest, char *src, int *i, int *l)
{
	while (src[*i])
	{
		if (src[*i] == '\"' && src[*i + 1])
		{
			(*i)++;
			while (src[*i] && src[*i] != '\"')
				dest[(*l)++] = src[(*i)++];
			if (src[*i] == '\0')
				break ;
			(*i)++;
		}
		else if (src[*i] == '\'' && src[*i + 1])
		{
			(*i)++;
			while (src[*i] && src[*i] != '\'')
				dest[(*l)++] = src[(*i)++];
			if (src[*i] == '\0')
				break ;
			(*i)++;
		}
		else
			dest[(*l)++] = src[(*i)++];
	}
	return (dest);
}

char	*ft_cote2(const char *src, int i, int l)
{
	char	*dest;

	if (src == NULL)
		return (NULL);
	dest = (char *)malloc(ft_strlencote((char *)src, 0, 0) * sizeof(const char)
			+ 1);
	dest = ft_cote2_norm(dest, (char *)src, &i, &l);
	dest[l] = '\0';
	return (dest);
}

t_Command_Table	*ft_cote(t_Command_Table *table)
{
	char			*new;
	t_Command_Table	*tmp;

	tmp = table;
	while (tmp)
	{
		new = ft_cote2(tmp->arg, 0, 0);
		free(tmp->arg);
		tmp->arg = new;
		tmp = tmp->next;
	}
	return (table);
}

int	ft_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
