/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:26:19 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/21 12:00:45 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2,int count)
{
	char	*p;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

    
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen3(s1);
	s2_len = ft_strlen3(s2);
	p = malloc(s2_len + s1_len + 1);
	if (!p)
		return (NULL);
	while (i < s1_len)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	p[i++] = s2[j++];
	p[i] = '\0';
    if(count > 0)
    free(s1);
    free(s2);
    count++;
	return (p);
}