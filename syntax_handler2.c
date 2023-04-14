/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:55:28 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:04:59 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax_3(char *new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		if (new[i] == '|' && syntax_help(new + i + 1) == 1)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_check_syntax_4(char *new, int i)
{
	while (new[i])
	{
		if (new[i] == '\"')
		{
			i++;
			while (new[i] && new[i] != '\"')
				i++;
			if (new[i] == '\0')
				return (1);
			i++;
			continue ;
		}
		if (new[i] == '\'')
		{
			i++;
			while (new[i] && new[i] != '\'')
				i++;
			if (new[i] == '\0')
				return (1);
			i++;
			continue ;
		}
		i++;
	}
	return (-1);
}

int	ft_check_syntax_5(char *new, int i)
{
	int	j;

	while (new[i])
	{
		j = i;
		if (new[i] == '|')
		{
			i++;
			while (new[i] && (new[i] == ' ' || new[i] == '\t' || new[i] == '\n'
					|| new[i] == 12))
				i++;
			if (new[i] == '\0' || new[i] == '|')
				return (j);
		}
		i++;
	}
	return (-1);
}
