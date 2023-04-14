/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:49:18 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:02:42 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_count_norm(char *new, size_t *i, size_t *j)
{
	if (new[*i] == '\"')
	{
		ft_plus(i, j);
		while (new[*i] && new[*i] != '\"')
			ft_plus(i, j);
		ft_plus(i, j);
	}
	if (new[*i] == '\'')
	{
		ft_plus(i, j);
		while (new[*i] && new[*i] != '\'')
			ft_plus(i, j);
		ft_plus(i, j);
	}
	if (new[*i] == '<' && new[*i + 1] != '<')
		ft_plus3(i, j);
	else if (new[*i] == '>' && new[*i + 1] != '>')
		ft_plus3(i, j);
	else if (new[*i] == '|')
		ft_plus3(i, j);
	else
		ft_plus(i, j);
}

size_t	new_count(char *new, size_t k)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (new[i] && i < k)
		new_count_norm(new, &i, &j);
	return (j);
}

void	ft_plus3(size_t *i, size_t *j)
{
	*i = *i + 1;
	*j = *j + 3;
}

size_t	ft_strlen33(const char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t' || s[i] == 12
			|| s[i] == '\n'))
		i++;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != 12)
	{
		i++;
		j++;
	}
	return (j);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		if (str[i] != NULL)
			free(str[i++]);
	}
	if (str != NULL)
		free(str);
}
