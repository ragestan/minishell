/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:22:57 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 15:41:51 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Command_Table	*ft_lstlast(t_Command_Table *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back1(t_Command_Table **lst, t_Command_Table *new)
{
	t_Command_Table	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

t_Command_Table	*ft_var(t_Command_Table *table, t_envp *env)
{
	t_Command_Table	*tmp;

	tmp = table;
	while (tmp)
	{
		if (tmp->arg == NULL)
			tmp->arg = NULL;
		else
		{
			if (tmp->index != 3)
				tmp->arg = ft_en(tmp->arg, env, 1);
		}
		tmp = tmp->next;
	}
	return (table);
}

char	*ft_en(char *arg, t_envp *env, int g)
{
	t_int	w;
	t_envp	*tmp;
	char	*new;

	new = malloc(sizeof(char) * ft_env_count(arg, env, g) + 1);
	w = ft_initint();
	while (arg[w.i])
	{
		tmp = env;
		if (arg[w.i] == '\'' && ft_checkcote(arg, w.i, 0, 0) == 1 && g == 1)
			new = ft_en_cote(arg, new, &w);
		else if (arg[w.i] == '$')
		{
			w.k = 0;
			w.z = 0;
			new = ft_en_norm4(arg, new, tmp, &w);
		}
		else if (arg[w.i] && arg[w.i] != '$')
			new[w.j++] = arg[w.i++];
		else
			break ;
	}
	new[w.j] = '\0';
	free(arg);
	return (new);
}

t_int	ft_initint(void)
{
	t_int	w;

	w.i = 0;
	w.j = 0;
	w.k = 0;
	w.z = 0;
	w.new2 = NULL;
	return (w);
}
