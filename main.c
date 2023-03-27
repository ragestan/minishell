/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/27 01:52:49 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)sig;
	write(1, "\nminishell$", 12);
}

void	sigint(int	sig)
{
	(void)sig;
	write(1, "exit\n", 4);
	exit(0);
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
    {
        free(tmp->in_or_here);
    }
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
		if (new[i] == '|' && new[i + 1] == '\0')
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
		if (new[i] == '<' && new[i + 1] == '<' && new[i + 2] == '\0')
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '>' && new[i + 1] == '>' && new[i + 2] == '\0')
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '<' && new[i + 1] == '\0')
			return (write(2,"minishell: syntax error near unexpected token `newline'\n",57),-1);
		if (new[i] == '>' && new[i + 1] == '\0')
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


int	ft_env_count(char *arg,envp *env)
{
	int i;
	int j;
	char *new;
	envp *tmp;

	i = 0;
	j = 0;
	while (arg[i])
	{
		tmp = env;
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
					while(arg[i] && arg[i] != ' ' && arg[i] != '\t' && arg[i] != '\n'&& arg[i] != '$')
						i++;
					i--;
					j--;
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
				if(ft_strcmpedit2(arg + i + 1,tmp->str,ft_is_ad(arg + i +1)) == 0)
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
			new[j++] = arg[i++];
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
				tmp->arg = ft_en(tmp->arg,env);
		}
		tmp = tmp->next;
	}
	return (table);
}

t_Command_Table3 *ft_all(envp *env)
{
    char *new;
	char **split;
	int i;
	int k;
	t_Command_Table *table;
	t_Command_Table2 w;
    t_Command_Table3 *last_table;
   
    k = 0;
    i = 0;
	table = NULL;
		new = readline("minishell$ ");
		if (!new)
			(write(1,"exit\n",5),exit(0));
		add_history(new);
		if (check_all(new) == -1)
        {
            free(new);
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
		
    while(table)
		last_table = ft_make_last(&table,last_table, &k);
	
	
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
    
	(signal(SIGINT, sigint_handler),signal(SIGQUIT, sigint));
	while (1)
	{
		last_table = ft_all(env1);
        if (last_table == NULL)
            continue; 
		printlinkdlist(last_table);
        if(last_table->args[0] != NULL && last_table->infile != -1 && last_table->outfile != -1)
        {
            shell_with_pipes(last_table,env,&pipex,&env1);
            ft_free(pipex.paths);
        }
        close(last_table->outfile);
            close(last_table->infile);
       // execve("/usr/bin/make", last_table->args, NULL);
       
		//freestack_3(&last_table);  
		
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