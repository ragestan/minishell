/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:21:31 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 07:03:42 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_updateenv_helper(char *str, envp *st)
{
	if (ft_strserarch(str, '=') == 1)
	{
		if (st->free == 1)
			free(st->str);
		st->str = ft_strdup_z(str);
		st->free = 1;
		if (ft_strserarch(str, '=') == 1)
			st->option = 1;
		return (1);
	}
	else
		return (3);
}

int	ft_updateenv_helper1(char *str, envp *st)
{
	char	*ptr;

	ptr = NULL;
	if (ft_strserarch(st->str, '=') == 0)
	{
		ptr = ft_strplusequal(str, 1);
		if (ft_strserarch(ptr, '=') == 1)
			st->option = 1;
	}
	else
		ptr = ft_strplusequal(str, 0);
	st->str = ft_strjoin(st->str, ptr, st->free);
	st->free = 1;
	return (1);
}

int	ft_strcmpedit(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '=' || s2[i] != '=') && (s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] != '=' || s2[i] != '\0') && (s1[i] != '\0' || s2[i] != '='))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_export_help(char *str, envp **env1, int x, char *stredit)
{
	if ((ft_strserarch(str, '=') == 1) && (ft_strnstredit(str) == 0) && x == 0)
	{
		if (updateenv(*env1, str, 0) == 1)
			;
		else
			ft_lstadd_back(env1, ft_lstnew(str, 1));
	}
	else if ((ft_strserarch(str, '=') == 1) && (ft_strnstredit(str) == 1)
		&& x == 0)
	{
		stredit = ft_strdupedit(str);
		if (updateenv(*env1, stredit, 1) == 1)
			free(stredit);
		else
			(ft_lstadd_back(env1, ft_lstnew(stredit, 1)), free(stredit));
	}
	else if ((ft_strserarch(str, '=') == 0) && x == 0)
	{
		if (updateenv(*env1, str, 0) == 0)
			ft_lstadd_back(env1, ft_lstnew(str, 0));
	}
}
