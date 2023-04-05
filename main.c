/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/05 20:08:48 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int syntax_help(char *r)
{
	int i;

	i = 0;
	while (r[i] && (r[i] == ' ' || r[i] == '\t' || r[i] == '\n' || r[i] == 12))
		i++;
	if (r[i] == '\0')
		return (1);
	return (0);
}

char **arg(char **str)
{
	int i = 0;
	int j = 2;
	int k = 0;
	char **arg;

    
	if (str[0] && ft_strcmp(str[0], "echo") == 0)
		i++;
	else
		return (str);
	while (str[i])
	{
		if (ft_strcmp(str[i] ,"-n") == 0)
			i++;
		else
		 	break;
	}
	
	if (i != 1 && i != 2)
	{
		while (str[k])
			k++;
		arg = malloc(sizeof(char *) * (k - i + 2 + 1));
		arg[0] = ft_strdupZ("echo");
		arg[1] = ft_strdupZ("-n");
	}
	else
		return(str);
	while(str[i])
	{
		arg[j] = ft_strdupZ(str[i]);
		i++;
		j++;
	}
	arg[j] = NULL;
	ft_free(str);
	return (arg);
}

// t_Command_Table *table_init(void)
// {
// 	t_Command_Table *table;

// 	table = NULL;

// 	table->input = NULL;
// 	table->next = NULL;
// 	return(table);
// }

int	count_of_outfile(char **new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new[i])
	{
		if (new[i][0] == '>' && new[i][1] == '\0')
			j++;
		i++;
	}
	return (j);
}

int	lf_infile(char **new)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (new[i])
	{
		if (new[i][0] == '<' && new[i][1] == '\0')
			j = i;
		i++;
	}
	return (j);
}

int	lf_outfile(char **new, int k)
{
	static int	i;
	int			j;

	j = -1;
	if (k == 0)
	{
		i = 0;
		return (0);
	}
	while (new[i])
	{
		if (new[i][0] == '>' && new[i][1] == '\0')
		{
			j = i;
			i++;
			break ;
		}
		i++;
	}
	return (j);
}

int	count_infile(char **new, int i, int j)
{
	int	z;

	z = j;
	while (new[i + 1][j] && new[i + 1][j] != ' ' && new[i + 1][j] != '\t')
		j++;
	j = j - z;
	return (j);
}

char	*table_fixer(char **new)
{
	int		i;
	int		j;
	int		k;
	char	*table;

	k = 0;
	i = lf_infile(new);
	j = 0;
	if (i == -1)
	{
		table = malloc(1);
		table[k] = '\0';
		return (table);
	}
	while (new[i + 1][j] && (new[i + 1][j] == ' ' || new[i + 1][j] == '\t'
			|| new[i + 1][j] == 12))
		j++;
	table = malloc(sizeof(char) * (count_infile(new, i, j) + 1));
	while (new[i + 1][j] && new[i + 1][j] != ' ' && new[i + 1][j] != '\t')
		table[k++] = new[i + 1][j++];
	table[k] = '\0';
	return (table);
}

char	*table_fixer_two(char **new)
{
	int		i;
	int		j;
	int		k;
	char	*outfile;

	k = 0;
	i = lf_outfile(new, 1);
	j = 0;
	if (i == -1)
	{
		outfile = malloc(1);
		outfile[k] = '\0';
		return (outfile);
	}
	while (new[i + 1][j] == ' ' || new[i + 1][j] == '\t' || new[i + 1][j] == 12)
		j++;
	outfile = malloc(sizeof(char) * (count_infile(new, i, j) + 1));
	while (new[i + 1][j] && new[i + 1][j] != ' ' && new[i + 1][j] != '\t')
		outfile[k++] = new[i + 1][j++];
	outfile[k] = '\0';
	return (outfile);
}

size_t	new_count(char *new)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (new[i])
	{
		if (new[i] == '\"')
		{
			i++;
			j++;
			while (new[i] && new[i] != '\"')
			{
				i++;
				j++;
			}
			i++;
			j++;
		}
		if (new[i] == '\'')
		{
			i++;
			j++;
			while (new[i] && new[i] != '\'')
			{
				i++;
				j++;
			}
			i++;
			j++;
		}
		if (new[i] == '<' && new[i + 1] != '<')
		{
			i++;
			j = j + 3;
		}
		else if (new[i] == '>' && new[i + 1] != '>')
		{
			i++;
			j = j + 3;
		}
		else if (new[i] == '|')
		{
			i++;
			j = j + 3;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*new_new(char *new)
{
	int		i;
	int		j;
	char	*new_new;

	new_new = malloc(sizeof(char) * (new_count(new) + 1));
	i = 0;
	j = 0;
	while (new[i])
	{
		if (new[i] == '\"')
		{
			new_new[j++] = new[i++];
			while (new[i] && new[i] != '\"')
				new_new[j++] = new[i++];
		}
		if (new[i] == '\'')
		{
			new_new[j++] = new[i++];
			while (new[i] && new[i] != '\'')
				new_new[j++] = new[i++];
		}
		if (new[i] == '<' && new[i + 1] != '<')
		{
			new_new[j] = 12;
			new_new[++j] = new[i++];
			new_new[++j] = 12;
			j++;
		}
		else if (new[i] == '>' && new[i + 1] != '>')
		{
			new_new[j] = 12;
			new_new[++j] = new[i++];
			new_new[++j] = 12;
			j++;
		}
		else if (new[i] == '<' && new[i + 1] == '<')
		{
			new_new[j] = 12;
			new_new[++j] = new[i++];
			new_new[++j] = new[i++];
			new_new[++j] = 12;
			j++;
		}
		else if (new[i] == '>' && new[i + 1] == '>')
		{
			new_new[j] = 12;
			new_new[++j] = new[i++];
			new_new[++j] = new[i++];
			new_new[++j] = 12;
			j++;
		}
		else if (new[i] == '|')
		{
			new_new[j] = 12;
			new_new[++j] = new[i++];
			new_new[++j] = 12;
			j++;
		}
		else
		{
			new_new[j] = new[i];
			j++;
			i++;
		}
	}
	new_new[j] = '\0';
	free(new);
	return (new_new);
}



void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
    {
        if(str[i] != NULL)
		free(str[i++]);
    }
    if (str != NULL)
       free(str);
}

t_Command_Table2  ft_init(void)
{
	t_Command_Table2 w;
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
    int i = 0;
    
	(void)sig;
	//write(1, "\nminishell$", 12);
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    
    while (i < g_globale.command_count)
    {
        if (g_globale.pid[i]!= 0)
            kill(g_globale.pid[i], SIGINT);
        i++;
    }
    if (g_globale.idheredok != 0)
     kill(g_globale.idheredok, SIGINT);
    //exit(0);
    //kill(0, SIGINT);
}

void	sigquit_handler(int	sig)
{
	(void)sig;
    rl_on_new_line();
    rl_redisplay();
    return ;
	//write(1, "exit\n", 4);
	//exit(0);
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
	t_Command_Table3 *tmp;

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

int	ft_check_syntax_1(char *new)
{
	int i;

	i = 0;
	while (new[i])
	{
		if (new[i] == ' ' || new[i] == '\t')
		{
			i++;
			continue;
		}
		if (new[i] == '|')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61) ,-1);
		else
			break;
	}
	return (0);
}

int ft_check_syntax_3(char *new)
{
	int i;

	i = 0;
	while(new[i])
	{
		if (new[i] == '|' && syntax_help(new + i + 1) == 1)
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		i++;
	}
	return (0);
}
int	ft_check_syntax_2(char *new)
{
	int i;

	i = 0;
	while (new[i])
	{
		if (new[i] == ' ' || new[i] == '\t')
		{
			i++;
			continue;
		}
		if (new[i] == '<' && new[i + 1] == '<' && syntax_help(new + i + 1) == 1)
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '>' && new[i + 1] == '>' && syntax_help(new + i + 1) == 1)
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '<' && syntax_help(new + i + 1) == 1)
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '>' && syntax_help(new + i + 1) == 1)
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '<' && new[i + 1] == '<' && new[i + 2] == '<')
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '>')
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '<' && new[i + 1] == '<' && new[i + 2] == '>')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '<')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		if (new[i] == '<' && new[i + 1] == '>' && new[i + 2] == '<')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		if (new[i] == '>' && new[i + 1] == '<' && new[i + 2] == '>')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		if (new[i] == '<' && new[i + 1] == '>' && new[i + 2] == '>')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '<')
			return (write(2,"minishell: syntax error near unexpected token `redirection'\n",61),-1);
		else
			i++;
	}
	return (0);
}
int		ft_check_syntax_4(char *new)
{
	int i;

	i = 0;
	while(new[i])
	{
		if (new[i] == '\"')
		{
			i++;
			while (new[i] && new[i] != '\"')
				i++;
			if (new[i] == '\0')
				return (write(2,"minishell: syntax error near unexpected token `redirection\n",60),-1);
			i++;
			continue;
		}
		if (new[i] == '\'')
		{
			i++;
			while (new[i] && new[i] != '\'')
				i++;
			if (new[i] == '\0')
				return (write(2,"minishell: syntax error near unexpected token `redirection\n",60),-1);
			i++;
			continue;
		}
		i++;
	}
	return (0);
}

int check_all(char *new)
{
	
	if (ft_check_syntax_1(new) == -1)
		return (-1);
	if (ft_check_syntax_2(new) == -1)
		return (-1);
	if (ft_check_syntax_3(new) == -1)
		return (-1);
	if (ft_check_syntax_4(new) == -1)
		return (-1);
	return (0);
}
int count(t_Command_Table3 *table)
{
    int i;

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
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) ||(c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
		return(0);
	else
		return (1);
}

int	ft_is_ad(char *str)
{
	int i;
	char c;
	
	i = 0;
	while (str[i])
	{
		c = str[i];
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) ||(c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '_'))
			i++;
		else
			return (i);
	}
	return (i);
}


int	ft_strcmpedit2( char *s1,  char *s2 ,size_t j)
{
	size_t	i;

	i = 0;
    //printf("s1 : %s s2: %s \n ",s1,s2);
	while ((s1[i] != '='  || s2[i] != '=' )&& (s1[i] != '\0' || s2[i] != '\0')&&(s1[i] != '=' || s2[i] != '\0')&&(s1[i] != '\0' || s2[i] != '=') && i < j)
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
	if (s2[i] == '=')
		return  0;
	return -1;
}


int	ft_env_count(char *arg,envp *env,int g)
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
		if (arg[i] == '\'' && ft_checkcote(arg,i) == 1 && g == 1)
		{
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
			k = 0;
			z = 0;
			while(tmp)
			{
				if (arg[i + 1] == '?')
				{
					z = ft_is_ad(arg + i + 1);
					new = ft_itoa(g_globale.exit_child);
					j = j + ft_strlen3(new);
					free(new);
					i = i + 2;
					k = 0;
					break;
				}
				if(ft_strcmpedit2(arg + i + 1,tmp->str,ft_is_ad(arg + i +1)) == 0)
				{
					z = ft_is_ad(arg + i + 1);
					new = ft_strplusequal(tmp->str,0);
					j = j + ft_strlen3(new);
					free(new);
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
			{
				i++;
				j++;
			}
			else if (arg[i] == '$' && arg[i + 1] == '$')
			{
				i = i + 2;
				continue;
			}
			else if ((arg[i] == '$' && arg[i + 1] == '+' ) || (arg[i] == '$' && arg[i + 1] == '.') || (arg[i] == '$' && arg[i + 1] == ','))
			{
				i = i + 2;
				j = j + 2;
			}
			else if (z == 0 && arg[i] != '$' && arg[i + 1] != '\0' && arg[i + 1] != ' ' && arg[i + 1] != '\t' && arg[i + 1] != '\n' && arg[i + 1] != '$')
			{
					while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n' && arg[i] != '$')
						i++;
			}
			else if(z == 0 && arg[i] == '$')
			{
				i++;
				while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n' && arg[i] != '$' && char_is_ad(arg[i]) == 0)
					i++;
			}
		}
		
		if (arg[i] && arg[i] != '$')
		{
			j++;
			i++;
		}
		else if (arg[i] && arg[i] == '$' && arg[i + 1] == '$')
		{
			i++;
			j++;
		}
		else if (arg[i] && arg[i] == '$' && arg[i + 1] == '\0')
		{
			i++;
			j++;
		}
		else if(arg[i] && arg[i] == '$' && arg[i + 1] != '\0' )
			continue;
		else
			break;
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

char *ft_en(char *arg,envp *env,int g)
{
	int i;
	int j;
	int k;
	int z;
	envp *tmp;
	char *new2;
	char *new;

	new = malloc(sizeof(char) * ft_env_count(arg,env,g) + 1);
	//printf("%d\n",ft_env_count(arg,env,g));
	i = 0;
	j = 0;
	k = 0;
	while (arg[i])
	{
		tmp = env;
		if (arg[i] == '\'' && ft_checkcote(arg,i) == 1 && g == 1)
		{
				new[j++] = arg[i++];
				while (arg[i] && arg[i] != '\'')
					new[j++] = arg[i++];
				new[j++] = arg[i++];
				continue;
		}
		
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
						new[j++] = new2[k++];
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
				while (arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n' && arg[i] != '$' && char_is_ad(arg[i]) == 0)
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

t_Command_Table	*ft_var(t_Command_Table *table,envp *env)
{
	t_Command_Table *tmp;

	tmp = table;
	while (tmp)
	{
		if (tmp->arg == NULL)
			tmp->arg = NULL;
		else
		{
			if (tmp->index != 3)
				tmp->arg = ft_en(tmp->arg,env, 1);
		}
		tmp = tmp->next;
	}
	return (table);
}
size_t	ft_strlencote(const char *c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
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
			if (c[i])
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
			if (c[i])
				i++;
			continue;
		}
		j++;
		i++;
	}
	return (j);
}

char	*ft_cote2(const char *src)
{
	int		i;
	int		l;
	char	*dest;
	char	*j;

    if (src == NULL)
        return (NULL);
	i = 0;
	l = 0;
	j = ((dest = (char *)malloc(ft_strlencote((char *)src) * sizeof(const char)
					+ 1)));
	if (!j)
		return (0);
	while (src[i] && src[i] != ' ' && src[i] != '\t' && src[i] != 12)
	{
		if (src[i] == '\"' && src[i + 1])
		{
			
			i++;
			while (src[i] && src[i] != '\"')
			{
				dest[l] = src[i];
				i++;
				l++;
			}
			if (src[i] == '\0')
				break;
			i++;
			continue;
		}
		if (src[i] == '\'' && src[i + 1])
		{
			i++;
			while (src[i] && src[i] != '\'')
			{
				dest[l] = src[i];
				i++;
				l++;
			}
			if (src[i] == '\0')
				break;
			i++;
			continue;
		}
		dest[l] = src[i];
		i++;
		l++;
	}
	dest[l] = '\0';
	return (dest);
}

t_Command_Table *ft_cote(t_Command_Table *table)
{
	char *new;
	t_Command_Table *tmp;

	tmp = table;
	while (tmp)
	{
		new = ft_cote2(tmp->arg);
		free(tmp->arg);
		tmp->arg = new;
		tmp = tmp->next;
	}
	return (table);
}

size_t	ft_strlen33(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != 12)
	{
		i++;
	}
	return (i);
}

char	*ft_strdup3(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen33(s1);
	p = malloc(sizeof(char) * (len + 1));
	if (p == 0)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != ' ' && s1[i] != '\t' && s1[i] != 12)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

t_Command_Table3 *ft_all(envp *env)
{
    char *new;
	char *new2;
	char **split;
	int i;
	int k;
	t_Command_Table *table;
	t_Command_Table2 w;
    t_Command_Table3 *last_table;
	t_Command_Table3 *tmp;
    struct termios term;
    struct termios oldterm;
    
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
			(write(1,"exit\n",5),exit(g_globale.exit_child));
		add_history(new);
		if (check_all(new) == -1)
        {
			g_globale.exit_child = 258;
			new = new_new(new);
			split = ft_split(new, 12);
			free(new);
			while (split[i])
			{	
				if (split[i][0] == '<' && split[i][1] == '<' && split[i][2] == '\0')
				{	
					if (split[i + 1])
					{
						new = ft_strdup3(split[i + 1]);
						new2 = heredocstring(new);
						free(new);
						free(new2);
					}
				}
				i++;
			}
			ft_free(split);
            return (NULL);
        }
		
		new = new_new(new);
		split = ft_split(new, 12);
		w = ft_init();
		// mor hna l3iba;
		while (split[i])
			i = ft_make(&table, split,&w);
		if (table == NULL)
		{
			free(new);
			ft_free(split);
			return (NULL);
		}
		table = ft_var(table,env);
		table = ft_cote(table);
    while(table)
		last_table = ft_make_last(&table,last_table, &k);
	tmp = last_table;
	while (tmp)
	{
		last_table->args = arg(last_table->args);
		tmp = tmp->next;
	}
    free(new);
    ft_free(split);
    freestack(&table);
    return (last_table);

}

int	main(int argc,char **argv,char **env)
{
	// char *new;
	// char **split;
	// int i;
	// int k;
	// t_Command_Table *table;
	// t_Command_Table2 w;
    //expand in echo
    //exit in builtin
    g_globale.exit_child = 0;
	t_Command_Table3 *last_table;
    envp *env1 = NULL;
    t_pipex pipex;
     (void)argc;
    (void)argv;
    
     printf("/-----------------------------\n");
    //add OLDPWD
    int r = 0;
    //int j = 1;
    //int error = 0;
	
	while (env[r] != '\0')
		r++;
	r -= 2;
	while (r >= 0)
	{
		make_node(&env1, env[r]);
		r--;
	}
	(signal(SIGINT, sigint_handler),signal(SIGQUIT, sigquit_handler));
    g_globale.env1 = env1;
	while (1)
	{
		last_table = ft_all(env1);
		//system("leaks minishell");
        if (last_table == NULL)
            continue; 
		//printlinkdlist(last_table);
        if(last_table->infile != -1 && last_table->outfile != -1)
        {
            shell_with_pipes(last_table,env,&pipex,&env1);
            ft_free(pipex.paths);
        }
        close(last_table->outfile);
        close(last_table->infile);
       // execve("/usr/bin/make", last_table->args, NULL);
	
		freestack_3(&last_table);  
        
		
	}
}
		
		// i = count_of_outfile(split);
		// while (i > 0)
		// {
		// 	table = ft_make(table, split);
		// 	i--;
		// }
		// table->input = table_fixer(split);
		// lf_outfile(split, 0);
		// printf("%s\n", table->input);
		// while (table)
		// {
		// 	printf("%s\n", table->output);
		// 	table = table->next;
		// }

		// while(table)
		// {	
		// 	printf("%i\n", table->index);
		// 	printf("%s\n", table->arg);
		// 	table = table->next;
		// }