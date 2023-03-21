/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:26:19 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/21 16:39:59 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + 48, fd);
	}
	if (n < 10)
	{
		ft_putchar_fd(n % 10 + 48, fd);
	}
}
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	return (0);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	return (0);
}
char	*ft_strdupZ(const char *s1)
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
	write (fd, &c, 1);
}