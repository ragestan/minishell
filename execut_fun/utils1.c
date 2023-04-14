/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:26:19 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 06:00:21 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup_z(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen3(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result > LLONG_MAX && sign == -1)
			return (0);
		else if (result > LLONG_MAX && sign == 1)
			return (-1);
		i++;
	}
	return (result * sign);
}

void	ft_error1(char *str, char *st)
{
	write(2, str, ft_strlen3(str));
	if (st)
		write(2, st, ft_strlen3(st));
	write(2, "\n", 1);
	g_globale.exit_child = 127;
	exit(127);
}
