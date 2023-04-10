/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:22:41 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/09 16:51:16 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
int	ft_updateenv_helper(char *str, envp *st)
{
	if (ft_strserarch(str, '=') == 1)
	{
		if (st->free == 1)
			free(st->str);
		st->str = ft_strdupZ(str);
		st->free = 1;
		if (ft_strserarch(str, '=') == 1)
			st->option = 1;
		return (1);
	}
	else
		return (3);
}
int	ft_updateenv_helper1(char *str, envp *st)
{
	char	*ptr;

	ptr = NULL;
	if (ft_strserarch(st->str, '=') == 0)
	{
		ptr = ft_strplusequal(str, 1);
		if (ft_strserarch(ptr, '=') == 1)
			st->option = 1;
	}
	else
		ptr = ft_strplusequal(str, 0);
	st->str = ft_strjoin(st->str, ptr, st->free);
	st->free = 1;
	return (1);
}

size_t	ft_strlen3(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strserarch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

envp	*sort_list(envp *lst, int (*cmp)(char *, char *))
{
	char	*swap;
	int		swapint;
	envp	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->str, lst->next->str)) >= 0)
		{
			swap = lst->str;
			swapint = lst->option;
			lst->str = lst->next->str;
			lst->option = lst->next->option;
			lst->next->str = swap;
			lst->next->option = swapint;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	//printnode(lst);
	return (lst);
}

int	ft_strcmpedit(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	//printf("s1 : %s s2: %s \n ",s1,s2);
	while ((s1[i] != '=' || s2[i] != '=') && (s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] != '=' || s2[i] != '\0') && (s1[i] != '\0' || s2[i] != '='))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strplusequal(char *str, int k)
{
	int		i;
	int		j;
	int		size;
	char	*str2;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] != '=')
		i++;
	size = ft_strlen3(str) - i;
	if (k == 1)
		i--;
	else
		size--;
	str2 = malloc(sizeof(char) * size + 1);
	i++;
	while (str[i] != '\0')
	{
		str2[j] = str[i];
		i++;
		j++;
	}
	str2[j] = '\0';
	return (str2);
}

int	updateenv(envp *env, char *str, int b)
{
	envp	*st;
	char	*ptr;

	st = env;
	ptr = NULL;
	while (st)
	{
		if (ft_strcmpedit(str, st->str) == 0 && b == 0)
			return (ft_updateenv_helper(str, st));
		else if (ft_strcmpedit(str, st->str) == 0 && b == 1)
			return (ft_updateenv_helper1(str, st));
		st = st->next;
	}
	return (0);
}

envp	*ft_lstnew(char *content, int option)
{
	envp	*new;

	new = (envp *)malloc(sizeof(envp));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdupZ(content);
	new->option = option;
	new->free = 1;
	new->prinlast = 1;
	new->next = NULL;
	return (new);
}

envp	*ft_lstlastZ(envp *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(envp **lst, envp *new)
{
	envp	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlastZ(*lst);
		last->next = new;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_putstredit(char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		if (s[i] == '=' && j == 0)
		{
			write(1, "\"", 1);
			j = 1;
		}
		i++;
	}
	write(1, "\"", 1);
}

void	printnodeExport(envp *stp)
{
	envp	*st;

	st = stp;
	while (st)
	{
		if (st->prinlast == 1)
		{
			ft_putstr_fd("declare -x ", 1);
			if (st->option == 1)
				ft_putstredit(st->str);
			else
				ft_putstr_fd(st->str, 1);
			printf("\n");
		}
		st = st->next;
	}
}

void	printnodealpha(envp *str)
{
	envp	*st;
	int		i;

	st = str;
	i = 32;
	while (i++ <= 126)
	{
		while (st)
		{
			if (st->str[0] == i && st->prinlast == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				if (st->option == 1)
					ft_putstredit(st->str);
				else
					ft_putstr_fd(st->str, 1);
				printf("\n");
				st = st->next;
			}
			else
				st = st->next;
		}
		st = str;
	}
	printnodeExport(str);
}

void	printnodeenv(envp *str)
{
	envp	*st;

	st = str;
	while (st)
	{
		if (st->option == 1)
			printf("%s\n", st->str);
		st = st->next;
	}
}

void	make_node(envp **st, char *str)
{
	envp	*head;

	head = malloc(sizeof(envp));
	if (!head)
		return ;
	head->str = str;
	head->option = 1;
	head->prinlast = 0;
	head->next = *st;
	*st = head;
}

int	valideinput(char *str)
{
	int	i;

	i = 0;
	if ((ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0 ) && str[i] != '_')
		return (1);
	i++;
	while (str[i] != '=' && str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '=' || str[i] == '_')
			i++;
		else if (str[i] == '+')
		{
			if (str[i + 1] == '=')
				i++;
			else
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int	ft_strnstredit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_strdupedit(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen3(s1) - 1;
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[j] != '\0')
	{
		if (s1[i] == '+' && s1[i + 1] == '=')
			j++;
		p[i] = s1[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	export(envp **env1, char *str)
{
	static int	x;
	char		*stredit;
	int			b;

	x = 0;
	stredit = NULL;
	b = 0;
	if (str == NULL)
	{
		//printnodeExport(*env1);
		printnodealpha(*env1);
		g_globale.exit_child = 0;
	}
	else
	{
		x = valideinput(str);
		if (x == 1)
		{
			printf("export: `%s': not a valid identifier\n", str);
			g_globale.exit_child = 1;
		}
		if ((ft_strserarch(str, '=') == 1) && (ft_strnstredit(str) == 0)
			&& x == 0)
		{
			if (updateenv(*env1, str, 0) == 1)
				;
			else
				ft_lstadd_back(env1, ft_lstnew(str, 1));
		}
		else if ((ft_strserarch(str, '=') == 1) && (ft_strnstredit(str) == 1)
				&& x == 0)
		{
			stredit = ft_strdupedit(str);
			if (updateenv(*env1, stredit, 1) == 1)
				free(stredit);
			else
			{
				ft_lstadd_back(env1, ft_lstnew(stredit, 1));
				free(stredit);
			}
		}
		else if ((ft_strserarch(str, '=') == 0) && x == 0)
		{
			b = updateenv(*env1, str, 0);
			if (b == 1)
				;
			else if (b == 0)
				ft_lstadd_back(env1, ft_lstnew(str, 0));
			else if (b == 3)
				;
		}
	}
}
