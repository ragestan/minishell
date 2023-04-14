/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing9.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:42:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:03:55 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_en_cote(char *arg, char *new, t_int *w)
{
	new[w->j++] = arg[w->i++];
	while (arg[w->i] && arg[w->i] != '\'')
		new[w->j++] = arg[w->i++];
	new[w->j++] = arg[w->i++];
	return (new);
}

char	*ft_en_norm4(char *arg, char *new, envp *tmp, t_int *w)
{
	new = ft_en_norm2(tmp, arg, new, w);
	if (arg[w->i] == '$' && arg[w->i + 1] == '?')
		new = ft_en_norm(arg, new, w->new2, w);
	else if (arg[w->i] == '$' && arg[w->i + 1] == '\0')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] == '$' && arg[w->i + 1] == '$')
		w->i = w->i + 2;
	else if ((arg[w->i] == '$' && arg[w->i + 1] == '+') || (arg[w->i] == '$'
				&& arg[w->i + 1] == '.') || (arg[w->i] == '$' && arg[w->i
				+ 1] == ','))
		new = ft_en_norm3(arg, new, w);
	else if (w->z == 0 && arg[w->i] != '$' && arg[w->i + 1] != '\0' && arg[w->i
			+ 1] != ' ' && arg[w->i + 1] != '\n' && arg[w->i + 1] != '$')
		ft_env_norm4(arg, w);
	else if (w->z == 0 && arg[w->i] == '$' && char_is_ad(arg[w->i + 1]) == 0)
		ft_env_norm3(arg, w);
	else if (w->z == 0 && arg[w->i] == '$')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '$')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '\0')
		new[w->j++] = arg[w->i++];
	else if (w->z == 0 && arg[w->i] == '$')
		new[w->j++] = arg[w->i++];
	return (new);
}

char	*ft_en_norm2(envp *tmp, char *arg, char *new, t_int *w)
{
	while (tmp)
	{
		if (ft_strcmpedit2(arg + w->i + 1, tmp->str, ft_is_ad(arg + w->i
					+ 1)) == 0)
		{
			w->z = ft_is_ad(arg + w->i + 1);
			w->new2 = ft_strplusequal(tmp->str, 0);
			while (w->new2[w->k])
				new[w->j++] = w->new2[w->k++];
			free(w->new2);
			w->i++;
			w->k = 0;
			while (arg[w->i] && w->k < w->z)
				ft_plusi(&w->i, &w->k);
			break ;
		}
		tmp = tmp->next;
	}
	return (new);
}

char	*ft_en_norm(char *arg, char *new, char *new2, t_int *w)
{
	w->k = 0;
	w->z = ft_is_ad(arg + w->i + 1);
	new2 = ft_itoa(g_globale.exit_child);
	while (new2[w->k])
		new[w->j++] = new2[w->k++];
	free(new2);
	w->i = w->i + 2;
	w->k = 0;
	return (new);
}

char	*ft_en_norm3(char *arg, char *new, t_int *w)
{
	new[w->j++] = arg[w->i++];
	new[w->j++] = arg[w->i++];
	return (new);
}
