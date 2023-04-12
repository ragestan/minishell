/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing14.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:51:32 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/12 13:53:56 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strdoublelen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**arg(char **str, int i, int j)
{
	char	**arg;

	if (str[0] && ft_strcmp(str[0], "echo") == 0)
		i++;
	else
		return (str);
	while (str[i])
	{
		if (ft_strcmp(str[i], "-n") == 0)
			i++;
		else
			break ;
	}
	if (i != 1 && i != 2)
	{
		arg = malloc(sizeof(char *) * (strdoublelen(str) - i + 2 + 1));
		arg[0] = ft_strdupZ("echo");
		arg[1] = ft_strdupZ("-n");
	}
	else
		return (str);
	while (str[i])
		arg[j++] = ft_strdupZ(str[i++]);
	arg[j] = NULL;
	return (ft_free(str), arg);
}

void	freestack(t_Command_Table **stack)
{
	t_Command_Table	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while ((*stack)->next)
	{
		(*stack) = (*stack)->next;
		free(temp->arg);
		free(temp);
		temp = *stack;
	}
	free(temp->arg);
	free(temp);
}

void	freestack_3(t_Command_Table3 **stack)
{
	t_Command_Table3	*tmp;

	if (!*stack)
		return ;
	tmp = *stack;
	while (*stack && (*stack)->next)
	{
		(*stack) = (*stack)->next;
		ft_free(tmp->args);
		ft_free(tmp->heredoc);
		free(tmp->in_or_here);
		free(tmp);
		tmp = *stack;
	}
	if (tmp->args != NULL)
		ft_free(tmp->args);
	if (tmp->heredoc != NULL)
		ft_free(tmp->heredoc);
	if (tmp->in_or_here != NULL)
		free(tmp->in_or_here);
	if (tmp != NULL)
		free(tmp);
}
