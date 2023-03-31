/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:55:55 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/31 23:09:55 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **arg(char **str)
{
	int i = 0;
	int j = 0;
	char **arg;

	if (str[0][0] == 'e' && str[0][1] == 'c'  && str[0][2] == 'h' && str[0][3] == 'o' &&  str[0][4] == '\0')
		i++;
	if (str[1][0] == '-' && str[1][1] == 'n' && str[1][2] == '\0')
		i++;
	while (str[i])
	{
		if(str[i - 1][0] == str[i][0] && str[i - 1][1] == str[i][1] && str[i - 1][2] == str[i][2])
			i++;
		else
			break;	
	}
	if (str[i] == NULL)
	{
		ft_free(str);
		arg = ft_split("echo -n", ' ');
	}
	else 
		return (str);
}



int syntax_help(char *r)
{
	int i;
	while (r[i] && (r[i] == ' ' || r[i] == '\t' || r[i] == '\n' || r[i] == 12))
		i++;
	if (r[i] == '\0')
		return (1);
	return (0);
}