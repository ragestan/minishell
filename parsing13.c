/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing13.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:04:23 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:04:35 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_or_here(t_Command_Table *table)
{
	int	i;

	i = 0;
	while (table)
	{
		if (table->index == 0)
			i = 1;
		if (table->index == 3)
			i = 2;
		if (table->index == 5)
			break ;
		table = table->next;
	}
	return (i);
}

size_t	ft_strlen2(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup2(const char *src)
{
	int		i;
	char	*dest;
	char	*j;

	i = 0;
	j = ((dest = (char *)malloc(ft_strlen2((char *)src) * sizeof(const char)
					+ 1)));
	if (!j)
	{
		return (0);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_lstsize(t_Command_Table *lst, int k)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->index == 5)
			break ;
		if (lst->index == k)
			i++;
		lst = lst->next;
	}
	return (i);
}

t_Command_Table3	*make_last_norm(t_Command_Table3 *last_table, int i, int j)
{
	last_table->args[i] = NULL;
	last_table->heredoc[j] = NULL;
	last_table->next = NULL;
	return (last_table);
}
