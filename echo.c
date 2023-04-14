/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:33:21 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 00:01:57 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	echo_option_check(char *option)
{
	int	i;

	i = 0;
	if (option[0] != '-')
		return (0);
	i++;
	while (option[i] != '\0')
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char *option, char *str)
{
	if (option == NULL)
	{
		printf("%s\n", str);
		if (str)
			free(str);
		return ;
	}
	else if (echo_option_check(option) == 0)
	{
		printf("%s %s\n", option, str);
		if (str)
			free(str);
		return ;
	}
	else
	{
		printf("%s", str);
		if (str)
			free(str);
	}
}
