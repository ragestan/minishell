/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:10:37 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/14 00:05:03 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp1(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '=' && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	i = 0;
	while (s1[i] != '\0' && s1[i] != '=')
		i++;
	if (i == ft_strlen3(s2))
		return (0);
	else
		return (1);
}

void	deleteNode(envp **head, char *str)
{
	envp	*temp;
	envp	*current;

	if (*head == NULL)
		return ;
	if (ft_strncmp1((*head)->str, str) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
		return ;
	}
	current = *head;
	while (current->next != NULL && ft_strncmp1(current->next->str, str) != 0)
	{
		current = current->next;
	}
	if (current->next == NULL)
		return ;
	if (current->next->prinlast == 1)
		free(current->next->str);
	temp = current->next;
	current->next = current->next->next;
	free(temp);
}

int	validarg(char *str)
{
	int	i;

	i = 0;
	if ((ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}

int	unset(envp **env1, char *str)
{
	if (validarg(str) == 1)
	{
		printf("unset: `%s': not a valid identifier\n", str);
		return (1);
	}
	deleteNode(env1, str);
	return (0);
}
