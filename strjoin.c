/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:59:43 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 05:55:06 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen3(s1);
	s2_len = ft_strlen3(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		p[i++] = s2[j++];
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1_len = ft_strlen3(s1);
	s2_len = ft_strlen3(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		p[i++] = s2[j++];
	return (p[i] = '\0', free(s1), p);
}

char	*ft_strplusequal(char *str, int k)
{
	int		i;
	int		j;
	int		size;
	char	*str2;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] != '=')
		i++;
	size = ft_strlen3(str) - i;
	if (k == 1)
		i--;
	else
		size--;
	str2 = malloc(sizeof(char) * size + 1);
	i++;
	while (str[i] != '\0')
	{
		str2[j] = str[i];
		i++;
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen3(s1);
	s2_len = ft_strlen3(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*ft_strjoin(char *s1, char *s2, int count)
{
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	p = malloc(ft_strlen3(s2) + ft_strlen3(s1) + 1);
	if (!p)
		return (NULL);
	while (i < ft_strlen3(s1))
	{
		p[i] = s1[i];
		i++;
	}
	while (j < ft_strlen3(s2))
		p[i++] = s2[j++];
	p[i] = '\0';
	if (count > 0)
		free(s1);
	return (free(s2), count++, p);
}
