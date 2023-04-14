/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing11.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:52:27 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:04:03 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Command_Table3	*ft_make_last(t_Command_Table **a, t_Command_Table3 *table,
		int *k)
{
	t_Command_Table3	*next;

	next = make_last(*a, 0, 0);
	if (*k != 0)
		ft_lstadd_back_last(&table, next);
	else
	{
		table = next;
		(*k)++;
	}
	freestack_last(a);
	return (table);
}

t_Command_Table3	*make_last(t_Command_Table *table, int i, int j)
{
	t_Command_Table3	*last_table;

	last_table = malloc(sizeof(t_Command_Table3));
	last_table->args = malloc(sizeof(char *) * (ft_lstsize(table, 2) + 1));
	last_table->heredoc = malloc(sizeof(char *) * (ft_lstsize(table, 3) + 1));
	last_table->infile = last_infile(table, -2);
	last_table->outfile = last_outfile(table, -2, -2);
	if (in_or_here(table) == 1)
		last_table->in_or_here = ft_strdup2("infile");
	else if (in_or_here(table) == 2)
		last_table->in_or_here = ft_strdup2("heredoc");
	else
		last_table->in_or_here = ft_strdup2("none");
	while (table)
	{
		if (table->index == 3)
			last_table->heredoc[j++] = ft_strdup2(table->arg);
		if (table->index == 2)
			last_table->args[i++] = ft_strdup2(table->arg);
		if (table->index == 5)
			break ;
		table = table->next;
	}
	last_table = make_last_norm(last_table, i, j);
	return (last_table);
}

void	ft_lstadd_back_last(t_Command_Table3 **lst, t_Command_Table3 *new)
{
	t_Command_Table3	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast_last(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	freestack_last(t_Command_Table **stack)
{
	t_Command_Table	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while (*stack && (*stack)->next && (*stack)->index != 5)
	{
		(*stack) = (*stack)->next;
		free(temp->arg);
		free(temp);
		temp = *stack;
	}
	*stack = (*stack)->next;
	if (temp->arg)
		free(temp->arg);
	free(temp);
}

t_Command_Table3	*ft_lstlast_last(t_Command_Table3 *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
