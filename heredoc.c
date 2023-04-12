/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:24:40 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/12 21:38:15 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredocstring(char *delimiter)
{
	char	*string;
	char	*line;

	string = NULL;
	line = NULL;
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = ft_en(line, g_globale.env1, 0);
		string = ft_strjoin3(string, line);
		string = ft_strjoin3(string, "\n");
		free(line);
		line = readline("> ");
	}
	return (string);
}

char	*heredocwhile(char **heredoc)
{
	int		i;
	char	*string;

	i = 0;
	string = NULL;
	while (heredoc[i])
	{
		if (string)
			free(string);
		string = heredocstring(heredoc[i]);
		i++;
	}
	return (string);
}
