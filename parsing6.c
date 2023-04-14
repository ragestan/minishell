/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:26:59 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 20:28:14 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_count(char *arg, t_envp *env, int g)
{
	t_int	w;
	char	*new;
	t_envp	*tmp;

	new = NULL;
	w = ft_initint();
	while (arg[w.i])
	{
		tmp = env;
		if (arg[w.i] == '\'' && ft_checkcote(arg, w.i, 0, 0) == 1 && g == 1)
			ft_env_cote(arg, &w.i, &w.j);
		else if (arg[w.i] == '$')
			ft_env_norm5(arg, new, tmp, &w);
		else if (arg[w.i] && arg[w.i] != '$')
			ft_plusi(&w.i, &w.j);
		else
			break ;
	}
	return (w.j);
}

int	ft_checkcote(char *str, int j, int i, int k)
{
	while (str[i] && i < j)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'' && i < j)
				i++;
			if (str[i] && i < j)
				i++;
		}
		else if (str[i] == '"')
		{
			ft_plusi(&k, &i);
			while (str[i] && str[i] != '"' && i < j)
				i++;
			if (str[i] && i < j)
				ft_plusi(&k, &i);
		}
		else
			i++;
	}
	if (k % 2 == 0)
		return (1);
	return (0);
}

void	ft_env_cote(char *arg, int *i, int *j)
{
	ft_plusi(i, j);
	while (arg[*i] && arg[*i] != '\'')
		ft_plusi(i, j);
	ft_plusi(i, j);
}

void	ft_plusi(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

void	ft_env_norm5(char *arg, char *new, t_envp *tmp, t_int *w)
{
	ft_env_norm2(tmp, arg, new, w);
	if (arg[w->i] == '$' && arg[w->i + 1] == '?')
		ft_env_norm(arg, new, w);
	if (arg[w->i] == '$' && arg[w->i + 1] == '\0')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] == '$' && arg[w->i + 1] == '$')
		w->i = w->i + 2;
	else if ((arg[w->i] == '$' && arg[w->i + 1] == '+') || (arg[w->i] == '$'
			&& arg[w->i + 1] == '.') || (arg[w->i] == '$' && arg[w->i
				+ 1] == ','))
		ft_plus2(&w->i, &w->j);
	else if (w->z == 0 && arg[w->i] != '$' && arg[w->i + 1] != '\0' && arg[w->i
			+ 1] != ' ' && arg[w->i + 1] != '\t' && arg[w->i + 1] != '\n'
		&& arg[w->i + 1] != '$')
		ft_env_norm4(arg, w);
	else if (w->z == 0 && arg[w->i] == '$' && char_is_ad(arg[w->i + 1]) == 0)
		ft_env_norm3(arg, w);
	else if (w->z == 0 && arg[w->i] == '$')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '$')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '\0')
		ft_plusi(&w->i, &w->j);
	else if (w->z == 0 && arg[w->i] == '$')
		ft_plusi(&w->i, &w->j);
}
