/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:23:53 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/12 21:23:54 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*ptr;

	ptr = getcwd(NULL, 1);
	if (ptr == NULL)
		ptr = ft_getenv(g_globale.env1, "PWD");
	printf("%s\n", ptr);
	free(ptr);
}
