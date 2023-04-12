/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:38:10 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:08:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_plus2(int *i, int *j)
{
	*i = *i + 2;
	*j = *j + 2;
}

void	ft_env_norm3(char *arg, t_int *w)
{
	w->i++;
	while (arg[w->i] && arg[w->i] != ' ' && arg[w->i] != '\t'
		&& arg[w->i] != '\n' && arg[w->i] != '$' && char_is_ad(arg[w->i]) == 0)
		w->i++;
}

void	ft_env_norm4(char *arg, t_int *w)
{
	while (arg[w->i] && arg[w->i] != ' ' && arg[w->i] != '\t'
		&& arg[w->i] != '\n' && arg[w->i] != '$')
		w->i++;
}

int	char_is_ad(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
		return (0);
	else
		return (1);
}
