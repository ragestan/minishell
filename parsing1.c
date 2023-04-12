/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:00:43 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:48:13 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_new(char *new, int k)
{
	int		i;
	int		j;
	char	*new_new;

	if (k == -1)
		k = 2147483647;
	new_new = malloc(sizeof(char) * (new_count(new, k) + 1));
	i = 0;
	j = 0;
	while (new[i] && i <= k)
		new_new = new_all(new, new_new, &i, &j);
	new_new[j] = '\0';
	free(new);
	return (new_new);
}

char	*char_plus(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*ft_strdup3(const char *s1)
{
	char	*p;
	size_t	j;
	size_t	i;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen33(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0' && (s1[i] == ' ' || s1[i] == '\t' || s1[i] == 12
			|| s1[i] == '\n'))
		i++;
	while (s1[i] != '\0' && s1[i] != ' ' && s1[i] != '\t' && s1[i] != 12
		&& s1[i] != '\n')
		p[j++] = s1[i++];
	p[j] = '\0';
	return (p);
}

t_Command_Table2	ft_init(void)
{
	t_Command_Table2	w;

	w.i = 0;
	w.j = 0;
	w.k = 0;
	w.l = 0;
	w.m = 0;
	w.n = 0;
	return (w);
}

int	ft_make(t_Command_Table **a, char **new, t_Command_Table2 *w)
{
	t_Command_Table	*next;

	next = ft_lst(new, &w->i, w);
	if (next == NULL)
	{
		return (w->i);
	}
	if (w->k != 0)
		ft_lstadd_back1(a, next);
	else
	{
		*a = next;
		w->k++;
	}
	return (w->i);
}
