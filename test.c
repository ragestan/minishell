/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:55:55 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/01 21:12:19 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_count(char *arg,envp *env)
{
	int i;
	int j;
	int k;
	int z;
	char *new;
	envp *tmp;

	i = 0;
	j = 0;
	while (arg[i])
	{
		tmp = env;
		if (arg[i + 1] == '?')
		{
			new = ft_itoa(g_globale.exit_child);
			j = j + ft_strlen3(new);
			free(new);
			i = i + 2;
			k = 0;
			break;
		}
		if (arg[i] == '\'' && ft_checkcote(arg,i) == 1)
		{
			z = ft_is_ad(arg + i + 1);
			i++;
			j++;
			while (arg[i] && arg[i] != '\'')
			{
				i++;
				j++;
			}
			i++;
			j++;
			continue;
		}
		if (arg[i] == '$')
		{
			while(tmp)
			{
				if(ft_strcmpedit2(arg + i + 1,tmp->str,ft_is_ad(arg + i +1)) == 0)
				{
					new = ft_strplusequal(tmp->str,0);
					j = j + ft_strlen3(new);
					free(new);
					i++;
					k = 0;
					while(arg[i] && k < z)
					{
						j++;
						i++;
					}
					break;
				}
				tmp= tmp->next;
			}
		}
			i++;
			j++;
	}
	return (j);
}

int ft_checkcote(char *str , int j)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] && i < j)
	{
		if (str[i] == '"')
			k++;
		i++;
	}
	if (k % 2 == 0)
		return (1);
	return (0);
}

static size_t	ft_count(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	j;

	j = n;
	i = ft_count(n);
	if (n < 0)
	{
		j = -j;
		i++;
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i--)
	{
		str[i] = j % 10 + '0';
		j /= 10;
	}
	if (n < 0)
	str[0] = '-';
	return (str);
}

char *ft_en(char *arg,envp *env)
{
	int i;
	int j;
	int k;
	int z;
	envp *tmp;
	char *new2;
	char *new;

	new = malloc(sizeof(char) * ft_env_count(arg,env) + 1);
	i = 0;
	j = 0;
	k = 0;
	while (arg[i])
	{
		tmp = env;
		if (arg[i] == '$')
		{
			k = 0;
			z = 0;
			while(tmp)
			{
				if (arg[i + 1] == '?')
				{
					z = ft_is_ad(arg + i + 1);
					new2 = ft_itoa(g_globale.exit_child);
					while (new2[k])
						new[j++] = new2[k++];
					free(new2);
					i = i + 2;
					k = 0;
					break;
				}
				else if(ft_strcmpedit2(arg + i + 1,tmp->str,ft_is_ad(arg + i +1)) == 0)
				{
					z = ft_is_ad(arg + i +1);
					new2 = ft_strplusequal(tmp->str,0);
					while (new2[k])
					{
						new[j++] = new2[k++];
					}
					free(new2);
					i++;
					k = 0;
					while(arg[i] && k < z)
					{
						k++;
						i++;
					}
					break;
				}
				tmp= tmp->next;
			}
			if (arg[i] == '$' && arg[i + 1] == '\0')
				new[j++] = arg[i++];
			else if (arg[i] == '$' && arg[i + 1] == '$')
			{
				i = i + 2;
				continue;
			}
			else if ((arg[i] == '$' && arg[i + 1] == '+' ) || (arg[i] == '$' && arg[i + 1] == '.') || (arg[i] == '$' && arg[i + 1] == ','))
			{
				new[j++] = arg[i++];
				new[j++] = arg[i++];
			}
			else if (z == 0 && arg[i] != '$' && arg[i + 1] != '\0' && arg[i + 1] != ' ' && arg[i + 1] != '\t' && arg[i + 1] != '\n' && arg[i + 1] != '$')
			{
					while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n' && arg[i] != '$')
						i++;
			}
			else if(z == 0 && arg[i] == '$')
			{
				i++;
				while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n' && arg[i] != '$')
					i++;
			}
		}
		
		if (arg[i] && arg[i] != '$')
		{
			new[j++] = arg[i++];
		}
		else if (arg[i] && arg[i] == '$' && arg[i + 1] == '$')
			new[j++] = arg[i++];
		else if (arg[i] && arg[i] == '$' && arg[i + 1] == '\0')
			new[j++] = arg[i++];
		else if(arg[i] && arg[i] == '$' && arg[i + 1] != '\0' )
			continue;
		else
			break;
	}
	new[j] = '\0';
	free(arg);
	return (new);
}