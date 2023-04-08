/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:46:12 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/07 20:15:57 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_help(char *r)
{
	int	i;

	i = 0;
	while (r[i] && (r[i] == ' ' || r[i] == '\t' || r[i] == '\n' || r[i] == 12))
		i++;
	if (r[i] == '\0')
		return (1);
	return (0);
}

int	ft_check_syntax_1(char *new)
{
	int	i;

	i = 0;
	while (new[i])
	{
		if (new[i] == ' ' || new[i] == '\t')
		{
			i++;
			continue ;
		}
		if (new[i] == '|')
			return (i);
		else
			break ;
	}
	return (-1);
}

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

int	ft_check_syntax_2(char *new, int i, int j)
{
	while (new[i])
	{
		while (new[i] && (new[i] == ' ' || new[i] == '\t' || new[i] == '\n'))
			i++;
		j = i;
		if (new[i] == '<' && new[i + 1] == '<')
		{
			i = i + 2;
			while (new[i] && (new[i] == ' ' || new[i] == '\t'
					|| new[i] == '\n' || new[i] == 12))
				i++;
			if (new[i] == '>' || new[i] == '<' || new[i] == '|' || new[i] == '#'
				|| new[i] == '(' || new[i] == ')' || new[i] == '\0')
				return (j);
		}
		else
		{
			j = ft_check_syntax_2_cnt(new, i, j);
			if (j != -1)
				return (j);
		}
		i++;
	}
	return (-1);
}

int	ft_check_syntax_2_cnt(char *new, int i, int j)
{
	if (new[i] == '<' && new[i + 1] == '<' && syntax_help(new + i + 1) == 1)
		return (j);
	if (new[i] == '>' && new[i + 1] == '>' && syntax_help(new + i + 1) == 1)
		return (j);
	if (new[i] == '<' && syntax_help(new + i + 1) == 1)
		return (j);
	if (new[i] == '>' && syntax_help(new + i + 1) == 1)
		return (j);
	if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '<')
		return (j);
	if (new[i] == '<' && new[i + 1] == '>' && new[i + 2] == '<')
		return (j);
	if (new[i] == '>' && new[i + 1] == '<' && new[i + 2] == '>')
		return (j);
	if (new[i] == '<' && new[i + 1] == '>' && new[i + 2] == '>')
		return (j);
	if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '<')
		return (j);
	if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '>')
		return (j);
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

int	ft_check_syntax_5(char *new,int i)
{
	int j;

	while (new[i])
	{
		j = i;
		if (new[i] == '|')
		{	
		    i++;
			while (new[i] && (new[i] == ' ' || new[i] == '\t' || new[i] == '\n' || new[i] == 12))
				i++;
			if (new[i] == '\0' || new[i] == '|')
				return (j);
		}
		i++;
	}
	return (-1);
}

int	check_all(char *new)
{
	int	i;

	i = ft_check_syntax_1(new);
	if (i != -1)
	{
		return (i);
	}
	i = ft_check_syntax_2(new, 0, 0);
	if (i != -1)
	{
		return (i);
	}
	i = ft_check_syntax_3(new);
	if (i != -1)
	{
		return (i);
	}
	i = ft_check_syntax_4(new, 0);
	if (i != -1)
	{
		return (i);
	}
	i = ft_check_syntax_5(new, 0);
	if (i != -1)
	{
		return (i);
	}
	return (-1);
}
