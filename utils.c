/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:52:26 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/26 22:40:27 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *c, int k)
{
	size_t	i;
	size_t	j;

	i = k;
	j = 0;
	while (c[i] && (c[i] == ' ' || c[i] == '\t' || c[i] == 12))
		i++;
	while (c[i] != '\0' && c[i] != ' ' && c[i] != '\t' && c[i] != 12)
	{
		if (c[i] == '\"')
		{
			i++;
			while (c[i] && c[i] != '\"')
			{
				i++;
				j++;
			}
			i++;
			continue;
		}
		if (c[i] == '\'')
		{
			i++;
			while (c[i] && c[i] != '\'')
			{
				i++;
				j++;
			}
			i++;
			continue;
		}
		j++;
		i++;
	}
	return (j);
}

char	*ft_strdup(const char *src, int *k)
{
	int		i;
	int		l;
	char	*dest;
	char	*j;

	i = *k;
    if (src == NULL)
        return (NULL);
	l = 0;
	j = ((dest = (char *)malloc(ft_strlen((char *)src, *k) * sizeof(const char)
					+ 1)));
	if (!j)
		return (0);
	while (src[i] && (src[i] == ' ' || src[i] == '\t' || src[i] == 12))
		i++;
	while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != 12)
	{
		if (src[i] == '\"')
		{
			i++;
			while (src[i] && src[i] != '\"')
			{
				dest[l] = src[i];
				i++;
				l++;
			}
			i++;
			continue;
		}
		if (src[i] == '\'')
		{
			i++;
			while (src[i] && src[i] != '\'')
			{
				dest[l] = src[i];
				i++;
				l++;
			}
			i++;
			continue;
		}
		dest[l] = src[i];
		i++;
		l++;
	}
	dest[l] = '\0';
	*k = i;
	return (dest);
}

t_Command_Table	*ft_lst(char **new, int *i, t_Command_Table2 *w)
{
	t_Command_Table	*l;

	l = malloc(sizeof(t_Command_Table));
	if (!l)
		return (0);
	else
	{
		while (new[*i] && new[*i][w->j] && (new[*i][w->j] == ' '
				|| new[*i][w->j] == '\t' || new[*i][w->j] == 12))
		{
			if (new[*i][w->j + 1] == '\0')
			{
				*i = *i + 1;
				w->j = 0;
				continue ;
			}
			w->j++;
		}
		if (new[*i] == NULL)
        {
            free(l );
			return (NULL);
        }
		if (new[*i][w->j] == '<' && new[*i][w->j + 1] != '<')
		{
			l->index = 0;
			*i = *i + 1;
			w->j = 0;
		}
		else if (new[*i][w->j] == '>' && new[*i][w->j + 1] != '>')
		{
			l->index = 1;
			*i = *i + 1;
			w->j = 0;
		}
		else if (new[*i][w->j] == '>' && new[*i][w->j + 1] == '>')
		{
			l->index = 4;
			*i = *i + 1;
			w->j = 0;
		}
		else if (new[*i][w->j] == '<' && new[*i][w->j + 1] == '<')
		{
			l->index = 3;
			*i = *i + 1;
			w->j = 0;
		}
		else if (new[*i][w->j] == '|')
		{
			l->index = 5;
			*i = *i + 1;
			w->j = 0;
		}
		else
		{
			l->index = 2;
		}
		if (l->index == 5)
			l->arg = NULL;
		else
			l->arg = ft_strdup(new[*i], &w->j);
		if (new[*i] && new[*i][w->j] == '\0')
		{
			*i = *i + 1;
			w->j = 0;
		}
		l->next = NULL;
		return (l);
	}
}

t_Command_Table	*ft_lstlast(t_Command_Table *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back1(t_Command_Table **lst, t_Command_Table *new)
{
	t_Command_Table	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

int	ft_make(t_Command_Table **a, char **new, t_Command_Table2 *w)
{
	t_Command_Table	*next;

	next = ft_lst(new, &w->i, w);
	if (next == NULL)
    {
		return (w->i);
    }
	if (w->k != 0)
		ft_lstadd_back1(a, next);
	else
	{
		*a = next;
		w->k++;
	}
    // system("leaks minishell");
	return (w->i);
}

int	ft_lstsize(t_Command_Table *lst, int k)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->index == 5)
			break ;
		if (lst->index == k)
			i++;
		lst = lst->next;
	}
	return (i);
}

size_t	ft_strlen2(const char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (c[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

char	*ft_strdup2(const char *src)
{
	int		i;
	char	*dest;
	char	*j;

	i = 0;
	j = ((dest = (char *)malloc(ft_strlen2((char *)src) * sizeof(const char)
					+ 1)));
	if (!j)
	{
		return (0);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	last_infile(t_Command_Table *table)
{
	int	fd;

	fd = -2;
	while (table)
	{
		if (table->index == 5)
			break ;
		if (table->index == 0)
		{
			if (fd != -2)
				close(fd);
			fd = open(table->arg, O_RDONLY);
			if (fd == -1)
			{
				write(2, "minishell: ", 11);
				perror(table->arg);
				return (-1);
			}
		}
		table = table->next;
	}
	return (fd);
}

int	last_outfile(t_Command_Table *table)
{
	int	fd;
	int	i;

	fd = -2;
	i = -2;
	while (table)
	{
		if (table->index == 5)
			break ;
		if (table->index == 0)
		{
			// if (i != -2)
			// 	close(i);
			i = open(table->arg, O_RDONLY);
			if (i == -1)
				return (-1);
            close(i);
            
		}
		if (table->index == 4)
		{
			if (fd != -2)
				close(fd);
			fd = open(table->arg, O_RDWR| O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				write(2, "minishell: ", 11);
				perror(table->arg);
				return (-1);
			}
		}
		if (table->index == 1)
		{
			if (fd != -2)
				close(fd);
			fd = open(table->arg, O_WRONLY | O_RDONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				write(2, "minishell: ", 11);
				perror(table->arg);
				return (-1);
			}
		}
		table = table->next;
	}
	return (fd);
}

int	in_or_here(t_Command_Table *table)
{
	int	i;

	i = 0;
	while (table)
	{
		if (table->index == 0)
			i = 1;
		if (table->index == 3)
			i = 2;
		if (table->index == 5)
			break ;
		table = table->next;
	}
	return (i);
}

t_Command_Table3	*make_last(t_Command_Table *table)
{
	t_Command_Table3	*last_table;
	int					i;
	int					j;

	i = 0;
	j = 0;
	last_table = malloc(sizeof(t_Command_Table3));
	last_table->args = malloc(sizeof(char *) * (ft_lstsize(table, 2) + 1));
	last_table->heredoc = malloc(sizeof(char *) * (ft_lstsize(table, 3) + 1));
	last_table->infile = last_infile(table);
	last_table->outfile = last_outfile(table);
	if (in_or_here(table) == 1)
		last_table->in_or_here = ft_strdup2("infile");
	else if (in_or_here(table) == 2)
		last_table->in_or_here = ft_strdup2("heredoc");
	else
		last_table->in_or_here = ft_strdup2("none");
	while (table)
	{
		if (table->index == 3)
		{
			last_table->heredoc[j] = ft_strdup2(table->arg);
			j++;
		}
		if (table->index == 2)
		{
			last_table->args[i] = ft_strdup2(table->arg);
			i++;
		}
		if (table->index == 5)
			break ;
		table = table->next;
	}
	last_table->args[i] = NULL;
	last_table->heredoc[j] = NULL;
	last_table->next = NULL;
	return (last_table);
}

t_Command_Table3	*ft_lstlast_last(t_Command_Table3 *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_last(t_Command_Table3 **lst, t_Command_Table3 *new)
{
	t_Command_Table3	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast_last(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

void	freestack_last(t_Command_Table **stack)
{
	t_Command_Table	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while (*stack && (*stack)->next && (*stack)->index != 5)
	{
		(*stack) = (*stack)->next;
		free(temp->arg);
		free(temp);
		temp = *stack;
	}
	*stack = (*stack)->next;
	if (temp->arg)
		free(temp->arg);
	free(temp);
	// 	free(temp);
}

t_Command_Table3	*ft_make_last(t_Command_Table **a, t_Command_Table3 *table,int *k)
{
	t_Command_Table3	*next;

	next = make_last(*a);
	if (*k != 0)
	{
		ft_lstadd_back_last(&table, next);
	}
	else
	{
		table = next;
		(*k)++;
	}
	freestack_last(a);
	return (table);
}
