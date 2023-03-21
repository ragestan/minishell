/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:46:03 by zbentalh          #+#    #+#             */
/*   Updated: 2023/03/21 12:03:40 by zbentale         ###   ########.fr       */
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
//---------------------------------------zbentale--------------------------------
typedef struct NODE
{
	char		*str;
    int         option;
    int         free;
	struct NODE	*next;
}				envp;
typedef struct pipex
{
	char	**cmd;
	char	**paths;
	int		i;
	char	*save;
	//int		fd[2];
	//int		r;
	//int		k;
	//int		file1;
	//int		file2;
}			t_pipex;

int ft_strserarch(char *str,char c);
void ft_pwd();
char *ft_strplusequal(char *str,int k);
void ft_cd(envp **env,char *str);
void export(envp **env1 ,char *str);
int	ft_strcmp( char *s1,  char *s2);
int	ft_strcmpedit( char *s1,  char *s2);
int unset(envp **env1,char *str);
void echo(char *option,char *str);
void envv(envp *str);
void	pathfinder(t_pipex *pipex, envp *envp);
size_t	ft_strlen3(const char *s);
char	*ft_strjoin(char *s1, char *s2,int count);
void	make_node(envp **st, char *str);
//------------------------------------zbentalh---------------------------------------
void	ft_lstadd_back1(t_Command_Table **lst,
					t_Command_Table *new);
t_Command_Table3			*make_last(t_Command_Table *table);
t_Command_Table				*ft_lst(char **new, int *i, t_Command_Table2 *w);
char						**ft_split(char const *s, char c);
int							ft_make(t_Command_Table **a, char **new,
								t_Command_Table2 *w);
char						*table_fixer_two(char **new);
t_Command_Table3	*ft_make_last(t_Command_Table **a, t_Command_Table3 *table, int *k);
char	*ft_strjoin(char *s1, char *s2,int count);
void	make_node(envp **st, char *str);
#endif