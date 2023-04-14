/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkd_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:09:38 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 07:05:13 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

envp	*ft_lstnew(char *content, int option)
{
	envp	*new;

	new = (envp *)malloc(sizeof(envp));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup_z(content);
	new->option = option;
	new->free = 1;
	new->prinlast = 1;
	new->next = NULL;
	return (new);
}

envp	*ft_lstlast_z(envp *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(envp **lst, envp *new)
{
	envp	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_z(*lst);
		last->next = new;
	}
}

void	make_node(envp **st, char *str)
{
	envp	*head;

	head = malloc(sizeof(envp));
	if (!head)
		return ;
	head->str = str;
	head->option = 1;
	head->prinlast = 0;
	head->next = *st;
	*st = head;
}

int	updateenv(envp *env, char *str, int b)
{
	envp	*st;
	char	*ptr;

	st = env;
	ptr = NULL;
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
