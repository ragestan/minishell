/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:10:53 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:02:56 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdupnor(char *dest, const char *src, int *i, int *l)
{
	dest[(*l)++] = src[(*i)++];
	while (src[*i] && src[*i] != '\"')
		dest[(*l)++] = src[(*i)++];
	if (src[*i])
		dest[(*l)++] = src[(*i)++];
	return (dest);
}

char	*ft_strdupnor2(char *dest, const char *src, int *i, int *l)
{
	dest[(*l)++] = src[(*i)++];
	while (src[*i] && src[*i] != '\'')
		dest[(*l)++] = src[(*i)++];
	if (src[*i])
		dest[(*l)++] = src[(*i)++];
	return (dest);
}

size_t	ft_strlen(const char *c, int k)
{
	size_t	i;
	size_t	j;

	i = k;
	j = 0;
	while (c[i] && (c[i] == ' ' || c[i] == '\t' || c[i] == 12))
		i++;
	while (c[i] != '\0' && c[i] != ' ' && c[i] != '\t' && c[i] != 12)
	{
		if (c[i] == '\"')
			ft_strlen_nor(c, &i, &j);
		else if (c[i] == '\'')
		{
			ft_plus(&i, &j);
			while (c[i] && c[i] != '\'')
				ft_plus(&i, &j);
			if (c[i])
				ft_plus(&i, &j);
		}
		else
			ft_plus(&i, &j);
	}
	return (j);
}

void	ft_strlen_nor(const char *c, size_t *i, size_t *j)
{
	ft_plus(i, j);
	while (c[*i] && c[*i] != '\"')
		ft_plus(i, j);
	if (c[*i])
		ft_plus(i, j);
}

void	ft_plus(size_t *i, size_t *j)
{
	*i = *i + 1;
	*j = *j + 1;
}
