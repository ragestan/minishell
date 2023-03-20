/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:46:03 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/20 23:12:58 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct a_Cammand_Table3
{
	char					**heredoc;
	int						infile;
	int						outfile;
	char					*in_or_here;
	char					**args;
	struct a_Cammand_Table3	*next;
}							t_Command_Table3;

typedef struct a_Command_Table
{
	int						index;
	char					*arg; 
	struct a_Command_Table	*next;
}							t_Command_Table;

typedef struct a_Command_Table2
{
	int						i;
	int						l;
	int						j;
	int						m;
	int						n;
	int						k;
}							t_Command_Table2;

void	ft_lstadd_back(t_Command_Table **lst,
					t_Command_Table *new);
t_Command_Table3			*make_last(t_Command_Table *table);
t_Command_Table				*ft_lst(char **new, int *i, t_Command_Table2 *w);
char						**ft_split(char const *s, char c);
int							ft_make(t_Command_Table **a, char **new,
								t_Command_Table2 *w);
char						*table_fixer_two(char **new);
t_Command_Table3	*ft_make_last(t_Command_Table **a, t_Command_Table3 *table, int *k);
#endif