/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:33:17 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 00:01:57 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envv(envp *str)
{
	envp *st;
	st = str;
	while (st)
	{
		if (st->option == 1)
			printf("%s\n", st->str);
		st = st->next;
	}
	printf("_=/usr/bin/env\n");
}