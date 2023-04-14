/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:45:51 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:02:37 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_all(char *new, char *new_new, int *i, int *j)
{
	if (new[*i] == '\"')
		new_new = char_plus_2cote(new, new_new, i, j);
	if (new[*i] == '\'')
		new_new = char_plus_1cote(new, new_new, i, j);
	if (new[*i] == '<' && new[*i + 1] != '<')
		new_new = char_plus_outfile(new, new_new, i, j);
	else if (new[*i] == '>' && new[*i + 1] != '>')
		new_new = char_plus_outfile(new, new_new, i, j);
	else if (new[*i] == '<' && new[*i + 1] == '<')
		new_new = char_plus_heredoc(new, new_new, i, j);
	else if (new[*i] == '>' && new[*i + 1] == '>')
		new_new = char_plus_heredoc(new, new_new, i, j);
	else if (new[*i] == '|')
		new_new = char_plus_outfile(new, new_new, i, j);
	else
		new_new = char_plus(new, new_new, i, j);
	return (new_new);
}

char	*char_plus_2cote(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	while (str[*i] && str[*i] != '\"')
	{
		new[*j] = str[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*char_plus_1cote(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	while (str[*i] && str[*i] != '\'')
	{
		new[*j] = str[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*char_plus_outfile(char *str, char *new, int *i, int *j)
{
	new[*j] = 12;
	*j = *j + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = 12;
	*j = *j + 1;
	return (new);
}

char	*char_plus_heredoc(char *str, char *new, int *i, int *j)
{
	new[*j] = 12;
	*j = *j + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = 12;
	*j = *j + 1;
	return (new);
}
