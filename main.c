/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/09 21:14:13 by zbentale         ###   ########.fr       */
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

void	ft_plus(size_t *i, size_t *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

void	ft_plusi(int *i, int *j)
{
	*i = *i + 1;
	*j = *j + 1;
}

void	ft_plus2(int *i, int *j)
{
	*i = *i + 2;
	*j = *j + 2;
}

void	ft_plus3(size_t *i, size_t *j)
{
	*i = *i + 1;
	*j = *j + 3;
}

void	new_count_norm(char *new, size_t *i, size_t *j)
{
	if (new[*i] == '\"')
	{
		ft_plus(i, j);
		while (new[*i] && new[*i] != '\"')
			ft_plus(i, j);
		ft_plus(i, j);
	}
	if (new[*i] == '\'')
	{
		ft_plus(i, j);
		while (new[*i] && new[*i] != '\'')
			ft_plus(i, j);
		ft_plus(i, j);
	}
	if (new[*i] == '<' && new[*i + 1] != '<')
		ft_plus3(i, j);
	else if (new[*i] == '>' && new[*i + 1] != '>')
		ft_plus3(i, j);
	else if (new[*i] == '|')
		ft_plus3(i, j);
	else
		ft_plus(i, j);
}

size_t	new_count(char *new, size_t k)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (new[i] && i < k)
		new_count_norm(new, &i, &j);
	return (j);
}

char	*char_plus_2cote(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	while (str[*i] && str[*i] != '\"')
	{
		new[*j] = str[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*char_plus_1cote(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	while (str[*i] && str[*i] != '\'')
	{
		new[*j] = str[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*char_plus_outfile(char *str, char *new, int *i, int *j)
{
	new[*j] = 12;
	*j = *j + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = 12;
	*j = *j + 1;
	return (new);
}

char	*char_plus_heredoc(char *str, char *new, int *i, int *j)
{
	new[*j] = 12;
	*j = *j + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	new[*j] = 12;
	*j = *j + 1;
	return (new);
}

char	*char_plus(char *str, char *new, int *i, int *j)
{
	new[*j] = str[*i];
	*j = *j + 1;
	*i = *i + 1;
	return (new);
}

char	*new_all(char *new, char *new_new, int *i, int *j)
{
	if (new[*i] == '\"')
		new_new = char_plus_2cote(new, new_new, i, j);
	if (new[*i] == '\'')
		new_new = char_plus_1cote(new, new_new, i, j);
	if (new[*i] == '<' && new[*i + 1] != '<')
		new_new = char_plus_outfile(new, new_new, i, j);
	else if (new[*i] == '>' && new[*i + 1] != '>')
		new_new = char_plus_outfile(new, new_new, i, j);
	else if (new[*i] == '<' && new[*i + 1] == '<')
		new_new = char_plus_heredoc(new, new_new, i, j);
	else if (new[*i] == '>' && new[*i + 1] == '>')
		new_new = char_plus_heredoc(new, new_new, i, j);
	else if (new[*i] == '|')
		new_new = char_plus_outfile(new, new_new, i, j);
	else
		new_new = char_plus(new, new_new, i, j);
	return (new_new);
}

char	*new_new(char *new, int k)
{
	int		i;
	int		j;
	char	*new_new;

	if (k == -1)
		k = 2147483647;
	new_new = malloc(sizeof(char) * (new_count(new, k) + 1));
	i = 0;
	j = 0;
	while (new[i] && i <= k)
		new_new = new_all(new, new_new, &i, &j);
	new_new[j] = '\0';
	free(new);
	return (new_new);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
    if (str == NULL)
        return ;
	while (str[i])
	{
		if (str[i] != NULL)
			free(str[i++]);
	}
	if (str != NULL)
		free(str);
}

t_Command_Table2	ft_init(void)
{
	t_Command_Table2	w;

	w.i = 0;
	w.j = 0;
	w.k = 0;
	w.l = 0;
	w.m = 0;
	w.n = 0;
	return (w);
}

void	sigint_handler(int sig)
{
	int	i;

	i = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	while (i < g_globale.command_count)
	{
		if (g_globale.pid[i] != 0)
			kill(g_globale.pid[i], SIGINT);
		i++;
	}
	if (g_globale.idheredok != 0)
	{
		g_globale.exit_child = 1;
		kill(g_globale.idheredok, SIGINT);
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	return ;
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

int	count(t_Command_Table3 *table)
{
	int	i;

	i = 0;
	while (table)
	{
		i++;
		table = table->next;
	}
	return (i);
}

int	char_is_ad(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
		return (0);
	else
		return (1);
}

int	ft_is_ad(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97
				&& c <= 122) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
			|| (c == '_'))
			i++;
		else
			return (i);
	}
	return (i);
}

int	ft_strcmpedit2(char *s1, char *s2, size_t j)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '=' || s2[i] != '=') && (s1[i] != '\0' || s2[i] != '\0')
		&& (s1[i] != '=' || s2[i] != '\0') && (s1[i] != '\0' || s2[i] != '=')
		&& i < j)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '=')
		return (0);
	return (-1);
}

t_int	ft_initint(void)
{
	t_int	w;

	w.i = 0;
	w.j = 0;
	w.k = 0;
	w.z = 0;
	w.new2 = NULL;
	return (w);
}

void	ft_env_cote(char *arg, int *i, int *j)
{
	ft_plusi(i, j);
	while (arg[*i] && arg[*i] != '\'')
		ft_plusi(i, j);
	ft_plusi(i, j);
}

void	ft_env_norm(char *arg, char *new, t_int *w)
{
	w->z = ft_is_ad(arg + w->i + 1);
	new = ft_itoa(g_globale.exit_child);
	w->j = w->j + ft_strlen3(new);
	free(new);
	w->i = w->i + 2;
	w->k = 0;
}

void	ft_env_norm2(envp *tmp, char *arg, char *new, t_int *w)
{
	while (tmp)
	{
		if (arg[w->i + 1] == '?')
		{
			ft_env_norm(arg, new, w);
			break ;
		}
		if (ft_strcmpedit2(arg + w->i + 1, tmp->str, ft_is_ad(arg + w->i
					+ 1)) == 0)
		{
			w->z = ft_is_ad(arg + w->i + 1);
			new = ft_strplusequal(tmp->str, 0);
			w->j = w->j + ft_strlen3(new);
			free(new);
			w->i++;
			w->k = 0;
			while (arg[w->i] && w->k < w->z)
				ft_plusi(&w->k, &w->i);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_env_norm3(char *arg, t_int *w)
{
	w->i++;
	while (arg[w->i] && arg[w->i] != ' ' && arg[w->i] != '\t'
		&& arg[w->i] != '\n' && arg[w->i] != '$' && char_is_ad(arg[w->i]) == 0)
		w->i++;
}

void	ft_env_norm4(char *arg, t_int *w)
{
	while (arg[w->i] && arg[w->i] != ' ' && arg[w->i] != '\t'
		&& arg[w->i] != '\n' && arg[w->i] != '$')
		w->i++;
}

void	ft_env_norm5(char *arg, char *new, envp *tmp, t_int *w)
{
	w->k = 0;
	w->z = 0;
	ft_env_norm2(tmp, arg, new, w);
	if (arg[w->i] == '$' && arg[w->i + 1] == '\0')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] == '$' && arg[w->i + 1] == '$')
		w->i = w->i + 2;
	else if ((arg[w->i] == '$' && arg[w->i + 1] == '+') || (arg[w->i] == '$'
				&& arg[w->i + 1] == '.') || (arg[w->i] == '$' && arg[w->i
				+ 1] == ','))
		ft_plus2(&w->i, &w->j);
	else if (w->z == 0 && arg[w->i] != '$' && arg[w->i + 1] != '\0' && arg[w->i
			+ 1] != ' ' && arg[w->i + 1] != '\t' && arg[w->i + 1] != '\n'
			&& arg[w->i + 1] != '$')
		ft_env_norm4(arg, w);
	else if (w->z == 0 && arg[w->i] == '$' && char_is_ad(arg[w->i + 1]) == 0)
		ft_env_norm3(arg, w);
	else if (w->z == 0 && arg[w->i] == '$')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '$')
		ft_plusi(&w->i, &w->j);
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '\0')
		ft_plusi(&w->i, &w->j);
	else if (w->z == 0 && arg[w->i] == '$')
		ft_plusi(&w->i, &w->j);
}

int	ft_env_count(char *arg, envp *env, int g)
{
	t_int	w;
	char	*new;
	envp	*tmp;

	new = NULL;
	w = ft_initint();
	while (arg[w.i])
	{
		tmp = env;
		if (arg[w.i] == '\'' && ft_checkcote(arg, w.i, 0, 0) == 1 && g == 1)
			ft_env_cote(arg, &w.i, &w.j);
		else if (arg[w.i] == '$')
			ft_env_norm5(arg, new, tmp, &w);
		else if (arg[w.i] && arg[w.i] != '$')
			ft_plusi(&w.i, &w.j);
		else
			break ;
	}
	return (w.j);
}

int	ft_checkcote(char *str, int j, int i, int k)
{
	while (str[i] && i < j)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'' && i < j)
				i++;
			if (str[i] && i < j)
				i++;
		}
		else if (str[i] == '"')
		{
			ft_plusi(&k, &i);
			while (str[i] && str[i] != '"' && i < j)
				i++;
			if (str[i] && i < j)
				ft_plusi(&k, &i);
		}
		else
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

char	*ft_en_cote(char *arg, char *new, t_int *w)
{
	new[w->j++] = arg[w->i++];
	while (arg[w->i] && arg[w->i] != '\'')
		new[w->j++] = arg[w->i++];
	new[w->j++] = arg[w->i++];
	return (new);
}

char	*ft_en_norm(char *arg, char *new, char *new2, t_int *w)
{
    w->k = 0;
	w->z = ft_is_ad(arg + w->i + 1);
	new2 = ft_itoa(g_globale.exit_child);
	while (new2[w->k])
		new[w->j++] = new2[w->k++];
	free(new2);
	w->i = w->i + 2;
	w->k = 0;
	return (new);
}

char	*ft_en_norm2(envp *tmp, char *arg, char *new, t_int *w)
{
	while (tmp)
	{
		if (ft_strcmpedit2(arg + w->i + 1, tmp->str, ft_is_ad(arg + w->i
					+ 1)) == 0)
		{
			w->z = ft_is_ad(arg + w->i + 1);
			w->new2 = ft_strplusequal(tmp->str, 0);
			while (w->new2[w->k])
				new[w->j++] = w->new2[w->k++];
			free(w->new2);
			w->i++;
			w->k = 0;
			while (arg[w->i] && w->k < w->z)
				ft_plusi(&w->i, &w->k);
			break ;
		}
		tmp = tmp->next;
	}
	return (new);
}

char	*ft_en_norm3(char *arg, char *new, t_int *w)
{
	new[w->j++] = arg[w->i++];
	new[w->j++] = arg[w->i++];
	return (new);
}

char	*ft_en_norm4(char *arg, char *new, envp *tmp, t_int *w)
{
	new = ft_en_norm2(tmp, arg, new, w);
    if(arg[w->i] == '$' && arg[w->i + 1] == '?')
        new = ft_en_norm(arg, new, w->new2, w);
	else if (arg[w->i] == '$' && arg[w->i + 1] == '\0')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] == '$' && arg[w->i + 1] == '$')
		w->i = w->i + 2;
	else if ((arg[w->i] == '$' && arg[w->i + 1] == '+') || (arg[w->i] == '$'
				&& arg[w->i + 1] == '.') || (arg[w->i] == '$' && arg[w->i
				+ 1] == ','))
		new = ft_en_norm3(arg, new, w);
	else if (w->z == 0 && arg[w->i] != '$' && arg[w->i + 1] != '\0' && arg[w->i
			+ 1] != ' ' && arg[w->i + 1] != '\t' && arg[w->i + 1] != '\n'
			&& arg[w->i + 1] != '$')
		ft_env_norm4(arg, w);
	else if (w->z == 0 && arg[w->i] == '$' && char_is_ad(arg[w->i + 1]) == 0)
		ft_env_norm3(arg, w);
	else if (w->z == 0 && arg[w->i] == '$')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '$')
		new[w->j++] = arg[w->i++];
	else if (arg[w->i] && arg[w->i] == '$' && arg[w->i + 1] == '\0')
		new[w->j++] = arg[w->i++];
	else if (w->z == 0 && arg[w->i] == '$')
		new[w->j++] = arg[w->i++];
	return (new);
}

char	*ft_en(char *arg, envp *env, int g)
{
	t_int	w;
	envp	*tmp;
	char	*new;

	new = malloc(sizeof(char) * ft_env_count(arg, env, g) + 1);
	w = ft_initint();
	while (arg[w.i])
	{
		tmp = env;
		if (arg[w.i] == '\'' && ft_checkcote(arg, w.i, 0, 0) == 1 && g == 1)
			new = ft_en_cote(arg, new, &w);
		else if (arg[w.i] == '$')
		{
			w.k = 0;
			w.z = 0;
			new = ft_en_norm4(arg, new, tmp, &w);
		}
		else if (arg[w.i] && arg[w.i] != '$')
			new[w.j++] = arg[w.i++];
		else
			break ;
	}
	new[w.j] = '\0';
	free(arg);
	return (new);
}

t_Command_Table	*ft_var(t_Command_Table *table, envp *env)
{
	t_Command_Table	*tmp;

	tmp = table;
	while (tmp)
	{
		if (tmp->arg == NULL)
			tmp->arg = NULL;
		else
		{
			if (tmp->index != 3)
				tmp->arg = ft_en(tmp->arg, env, 1);
		}
		tmp = tmp->next;
	}
	return (table);
}

size_t	ft_strlencote(const char *c, size_t i, size_t j)
{
	while (c[i] != '\0' && c[i] != ' ' && c[i] != '\t' && c[i] != 12)
	{
		if (c[i] == '\"')
		{
			i++;
			while (c[i] && c[i] != '\"')
				ft_plus(&i, &j);
			if (c[i])
				i++;
			continue ;
		}
		if (c[i] == '\'')
		{
			i++;
			while (c[i] && c[i] != '\'')
				ft_plus(&i, &j);
			if (c[i])
				i++;
			continue ;
		}
		ft_plus(&i, &j);
	}
	return (j);
}

char	*ft_cote2_norm(char *dest, char *src, int *i, int *l)
{
	while (src[*i] && src[*i] != ' ' && src[*i] != '\t' && src[*i] != 12)
	{
		if (src[*i] == '\"' && src[*i + 1])
		{
			(*i)++;
			while (src[*i] && src[*i] != '\"')
				dest[(*l)++] = src[(*i)++];
			if (src[*i] == '\0')
				break ;
			(*i)++;
		}
		else if (src[*i] == '\'' && src[*i + 1])
		{
			(*i)++;
			while (src[*i] && src[*i] != '\'')
				dest[(*l)++] = src[(*i)++];
			if (src[*i] == '\0')
				break ;
			(*i)++;
		}
		else
			dest[(*l)++] = src[(*i)++];
	}
	return (dest);
}

char	*ft_cote2(const char *src, int i, int l)
{
	char	*dest;

	if (src == NULL)
		return (NULL);
	dest = (char *)malloc(ft_strlencote((char *)src, 0, 0) * sizeof(const char)
			+ 1);
	dest = ft_cote2_norm(dest, (char *)src, &i, &l);
	dest[l] = '\0';
	return (dest);
}

t_Command_Table	*ft_cote(t_Command_Table *table)
{
	char			*new;
	t_Command_Table	*tmp;

	tmp = table;
	while (tmp)
	{
		new = ft_cote2(tmp->arg, 0, 0);
		free(tmp->arg);
		tmp->arg = new;
		tmp = tmp->next;
	}
	return (table);
}

size_t	ft_strlen33(const char *s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t' || s[i] == 12
			|| s[i] == '\n'))
		i++;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != 12)
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_strdup3(const char *s1)
{
	char	*p;
	size_t	j;
	size_t	i;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen33(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0' && (s1[i] == ' ' || s1[i] == '\t' || s1[i] == 12
			|| s1[i] == '\n'))
		i++;
	while (s1[i] != '\0' && s1[i] != ' ' && s1[i] != '\t' && s1[i] != 12
		&& s1[i] != '\n')
		p[j++] = s1[i++];
	p[j] = '\0';
	return (p);
}

t_Command_Table3	*ft_all(envp *env)
{
    int g_fork = 0;
	char				*new;
	char				*new2;
	char				**split;
	int					i;
	int					k;
	t_Command_Table		*table;
	t_Command_Table2	w;
	t_Command_Table3	*last_table;
	t_Command_Table3	*tmp;
	struct termios		term;
	struct termios		oldterm;

	k = 0;
	i = 0;
	tcgetattr(0, &term);
	oldterm = term;
	term.c_lflag &= ~ECHOCTL;
	table = NULL;
	tcsetattr(0, TCSANOW, &term);
	new = readline("minishell$ ");
	tcsetattr(0, TCSANOW, &oldterm);
	if (!new)
		(write(1, "exit\n", 5), exit(g_globale.exit_child));
	add_history(new);
	if (check_all(new) != -1)
	{
		g_globale.exit_child = 258;
		write(2,
				"minishell: syntax error near unexpected token `redirection'\n",
				61);
		new = new_new(new, check_all(new));
		split = ft_split(new, 12);
		free(new);
		while (split[i])
		{
			if (split[i][0] == '<' && split[i][1] == '<' && split[i][2] == '\0')
			{
				if (split[i + 1])
				{
					new = ft_strdup3(split[i + 1]);
                    g_fork = fork();
                    if (g_fork == 0)
                    {
                        signal(SIGINT, SIG_DFL);
                        new2 = heredocstring(new);
                        free(new);
                        free(new2);
                        exit(258);
                    }
                    else
                        waitpid(g_fork, NULL, 0);
					// new2 = heredocstring(new);
					 free(new);
					// free(new2);
				}
			}
			i++;
		}
		ft_free(split);
		return (NULL);
	}
	new = new_new(new, -1);
	split = ft_split(new, 12);
	w = ft_init();
	// mor hna l3iba;
	while (split[i])
		i = ft_make(&table, split, &w);
	if (table == NULL)
	{
		free(new);
		ft_free(split);
		return (NULL);
	}
	table = ft_var(table, env);
	table = ft_cote(table);
	while (table)
		last_table = ft_make_last(&table, last_table, &k);
	tmp = last_table;
	while (tmp)
	{
		last_table->args = arg(last_table->args, 0, 2);
		tmp = tmp->next;
	}
	free(new);
	ft_free(split);
	freestack(&table);
	return (last_table);
}

int	main(int argc, char **argv, char **env)
{
	t_Command_Table3	*last_table;
	envp				*env1;
	t_pipex				pipex;
	int					r;

	// char *new;
	// char **split;
	// int i;
	// int k;
	// t_Command_Table *table;
	// t_Command_Table2 w;
	//expand in echo
	//exit in builtin
	g_globale.exit_child = 0;
	env1 = NULL;
	(void)argc;
	(void)argv;
	printf("/-----------------------------\n");
	//add OLDPWD
	r = 0;
	//int j = 1;
	//int error = 0;
	while (env[r] != NULL)
		r++;
	r -= 2;
	while (r >= 0)
	{
		make_node(&env1, env[r]);
		r--;
	}
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, sigquit_handler));
	g_globale.env1 = env1;
	while (1)
	{
		last_table = ft_all(env1);
		//system("leaks minishell");
		if (last_table == NULL)
			continue ;
		//printlinkdlist(last_table);
		if (last_table->infile != -1 && last_table->outfile != -1)
		{
			shell_with_pipes(last_table, env, &pipex, &env1);
			ft_free(pipex.paths);
		}
		close(last_table->outfile);
		close(last_table->infile);
		// execve("/usr/bin/make", last_table->args, NULL);
		freestack_3(&last_table);
	}
}
