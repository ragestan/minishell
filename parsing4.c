/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:20:00 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:08:08 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_norm0(int *i, t_Command_Table2 *w, t_Command_Table *l)
{
	l->index = 0;
	*i = *i + 1;
	w->j = 0;
}

void	ft_lst_norm1(int *i, t_Command_Table2 *w, t_Command_Table *l)
{
	l->index = 1;
	*i = *i + 1;
	w->j = 0;
}

void	ft_lst_norm4(int *i, t_Command_Table2 *w, t_Command_Table *l)
{
	l->index = 4;
	*i = *i + 1;
	w->j = 0;
}

void	ft_lst_norm3(int *i, t_Command_Table2 *w, t_Command_Table *l)
{
	l->index = 3;
	*i = *i + 1;
	w->j = 0;
}

void	ft_lst_norm5(int *i, t_Command_Table2 *w, t_Command_Table *l)
{
	l->index = 5;
	*i = *i + 1;
	w->j = 0;
}
