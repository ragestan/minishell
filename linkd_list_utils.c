/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkd_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:09:38 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 20:29:52 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_lstnew(char *content, int option)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup_z(content);
	new->option = option;
	new->free = 1;
	new->prinlast = 1;
	new->next = NULL;
	return (new);
}

t_envp	*ft_lstlast_z(t_envp *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_z(*lst);
		last->next = new;
	}
}

void	make_node(t_envp **st, char *str)
{
	t_envp	*head;

	head = malloc(sizeof(t_envp));
	if (!head)
		return ;
	head->str = str;
	head->option = 1;
	head->prinlast = 0;
	head->next = *st;
	*st = head;
}

int	updateenv(t_envp *env, char *str, int b)
{
	t_envp	*st;

	st = env;
	while (st)
	{
		if (ft_strcmpedit(str, st->str) == 0 && b == 0)
			return (ft_updateenv_helper(str, st));
		else if (ft_strcmpedit(str, st->str) == 0 && b == 1)
			return (ft_updateenv_helper1(str, st));
		st = st->next;
	}
	return (0);
}
