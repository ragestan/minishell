/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:05:38 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:08:05 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Command_Table	*ft_lst(char **new, int *i, t_Command_Table2 *w)
{
	t_Command_Table	*l;

	l = malloc(sizeof(t_Command_Table));
	if (!l)
		return (0);
	else
	{
		while (new[*i] && new[*i][w->j] && (new[*i][w->j] == ' '
				|| new[*i][w->j] == '\t' || new[*i][w->j] == 12))
			ft_lst_normw(new, i, w);
		if (new[*i] == NULL)
			return (free(l), NULL);
		ft_lst_normlast(new, l, i, w);
		if (l->index == 5)
			l->arg = NULL;
		else
			l->arg = ft_strdup(new[*i], &w->j);
		if (new[*i] && new[*i][w->j] == '\0')
			ft_lst_norm(i, w);
		l->next = NULL;
		return (l);
	}
}

void	ft_lst_normw(char **new, int *i, t_Command_Table2 *w)
{
	if (new[*i][w->j + 1] == '\0')
		ft_lst_norm(i, w);
	else
		w->j++;
}

void	ft_lst_norm(int *i, t_Command_Table2 *w)
{
	*i = *i + 1;
	w->j = 0;
}

char	*ft_strdup(const char *src, int *k)
{
	int		i;
	int		l;
	char	*dest;

	i = *k;
	if (src == NULL)
		return (NULL);
	l = 0;
	dest = (char *)malloc(ft_strlen((char *)src, *k) * sizeof(const char) + 1);
	while (src[i] && (src[i] == ' ' || src[i] == '\t' || src[i] == 12))
		i++;
	while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != 12)
	{
		if (src[i] == '\"')
			dest = ft_strdupnor(dest, src, &i, &l);
		else if (src[i] == '\'')
			dest = ft_strdupnor2(dest, src, &i, &l);
		else
			dest[l++] = src[i++];
	}
	dest[l] = '\0';
	*k = i;
	return (dest);
}

void	ft_lst_normlast(char **new, t_Command_Table *l, int *i,
		t_Command_Table2 *w)
{
	if (new[*i][w->j] == '<' && new[*i][w->j + 1] != '<')
		ft_lst_norm0(i, w, l);
	else if (new[*i][w->j] == '>' && new[*i][w->j + 1] != '>')
		ft_lst_norm1(i, w, l);
	else if (new[*i][w->j] == '>' && new[*i][w->j + 1] == '>')
		ft_lst_norm4(i, w, l);
	else if (new[*i][w->j] == '<' && new[*i][w->j + 1] == '<')
		ft_lst_norm3(i, w, l);
	else if (new[*i][w->j] == '|')
		ft_lst_norm5(i, w, l);
	else
		l->index = 2;
}
