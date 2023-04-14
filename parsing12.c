/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing12.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:56:43 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 00:04:29 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_infile(t_Command_Table *table, int fd)
{
	while (table)
	{
		if (table->index == 5)
			break ;
		if (table->index == 0)
		{
			if (fd != -2)
				close(fd);
			if (table->arg[0] == '\0' || ft_space(table->arg) == 1)
			{
				g_globale.exit_child = 1;
				return (write(2, "minishell: ambiguous redirect\n", 30), -1);
			}
			fd = open(table->arg, O_RDONLY);
			if (fd == -1)
			{
				g_globale.exit_child = 1;
				return (write(2, "minishell: ", 11), perror(table->arg), -1);
			}
		}
		table = table->next;
	}
	return (fd);
}

int	last_outfile_norm(t_Command_Table *table, int fd)
{
	if (fd != -2)
		close(fd);
	if (table->arg[0] == '\0' || ft_space(table->arg) == 1)
	{
		g_globale.exit_child = 1;
		return (write(2, "minishell: ambiguous redirect\n", 30), -3);
	}
	fd = open(table->arg, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	last_outfile_norm2(t_Command_Table *table, int fd)
{
	if (fd != -2)
		close(fd);
	if (table->arg[0] == '\0' || ft_space(table->arg) == 1)
	{
		g_globale.exit_child = 1;
		return (write(2, "minishell: ambiguous redirect\n", 30), -3);
	}
	fd = open(table->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	last_outfile_norm3(t_Command_Table *table, int fd)
{
	if (table->index == 4)
		fd = last_outfile_norm2(table, fd);
	if (table->index == 1)
		fd = last_outfile_norm(table, fd);
	return (fd);
}

int	last_outfile(t_Command_Table *table, int fd, int i)
{
	while (table && table->index != 5)
	{
		if (table->index == 0)
		{
			i = open(table->arg, O_RDONLY);
			if (i == -1)
			{
				g_globale.exit_child = 1;
				return (-1);
			}
			close(i);
		}
		if (table->index == 4 || table->index == 1)
			fd = last_outfile_norm3(table, fd);
		if (fd == -1)
		{
			g_globale.exit_child = 1;
			return (write(2, "minishell: ", 11), perror(table->arg), -1);
		}
		if (fd == -3)
			return (-1);
		table = table->next;
	}
	return (fd);
}
