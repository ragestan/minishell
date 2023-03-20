/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:16:47 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/19 19:38:32 by zbentalh         ###   ########.fr       */
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

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
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
	ft_free(tmp->args);
	ft_free(tmp->heredoc);
	free(tmp->in_or_here);
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

int check_all(char *new)
{
	
	if (ft_check_syntax_1(new) == -1)
		return (-1);
	if (ft_check_syntax_2(new) == -1)
		return (-1);
	if (ft_check_syntax_3(new) == -1)
		return (-1);
	return (0);
}

int	main(void)
{
	char *new;
	char **split;
	int i;
	int k;
	t_Command_Table *table;
	t_Command_Table2 w;
	t_Command_Table3 *last_table;
	
	(signal(SIGINT, sigint_handler),signal(SIGQUIT, sigint));
	i = 0;
	while (1)
	{
		k = 0;
		new = readline("minishell$");
		if (!new)
			exit(0);
		add_history(new);
		if (check_all(new) == -1)
			continue;
		new = new_new(new);
		split = ft_split(new, 12);
		w = ft_init();
		// while(split[i])
		// printf("%s\n", split[i++]);
		// i = 0;
		while (split[i])
			i = ft_make(&table, split,&w);
		// 		while(table)
		// {	
		// 	printf("%i\n", table->index);
		// 	printf("%s\n", table->arg);
		// 	table = table->next;
		// }
		while(table)
			last_table = ft_make_last(&table,last_table, &k);
		while(last_table)
		{
			i = 0;
			while (last_table->args[i])
				printf("%s\n", last_table->args[i++]);
			i = 0;
			while (last_table->heredoc[i])
				printf("%s\n", last_table->heredoc[i++]);
			printf("%s\n", last_table->in_or_here);	
			last_table = last_table->next;
		}
		free(new);
		ft_free(split);
		freestack(&table);
		freestack_3(&last_table);
		i = 0;
		
	}
}
		//system("leaks minishell");
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