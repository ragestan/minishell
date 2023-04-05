/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:46:03 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/05 21:16:26 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
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
	char					*str;
	int						option;
	int						free;
	struct NODE				*next;
}							envp;
typedef struct pipex
{
	char					**cmd;
	char					**paths;
	int						i;
	char					*save;
	//int		fd[2];
	//int		r;
	//int		k;
	//int		file1;
	//int		file2;
}							t_pipex;

typedef struct a_globale
{
	envp					*env1;
	int						idheredok;
	int						exit_child;
	int						*pid;
	int						command_count;

}							t_globale;
t_globale					g_globale;

void						rl_replace_line(const char *text, int clear_undo);
int							ft_strserarch(char *str, char c);
void						ft_pwd(void);
char						*ft_strplusequal(char *str, int k);
void						ft_cd(envp **env, char *str);
void						export(envp **env1, char *str);
int							ft_strcmp(char *s1, char *s2);
int							ft_strcmpedit(char *s1, char *s2);
int							unset(envp **env1, char *str);
void						echo(char *option, char *str);
void						envv(envp *str);
void						pathfinder(t_pipex *pipex, envp *envp);
size_t						ft_strlen3(const char *s);
char						*ft_strjoin(char *s1, char *s2, int count);
void						make_node(envp **st, char *str);
void						ft_putstr_fd(char *s, int fd);
void						ft_putnbr_fd(int n, int fd);
int							ft_isdigit(int c);
int							ft_isalpha(int c);
int							ft_checkcote(char *str, int j);
int							ft_isalnum(int c);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
size_t						ft_strlen3(const char *s);
char						*ft_strjoin(char *s1, char *s2, int count);
void						make_node(envp **st, char *str);
char						*ft_strdupZ(const char *s1);
void						ft_putchar_fd(char c, int fd);
void						shell_with_pipes(t_Command_Table3 *table,
								char **env, t_pipex *pipex, envp **envp1);
char						*ft_strjoin2(char *s1, char const *s2);
void						printnodeenv(envp *str);
char						*ft_strplusequal(char *str, int k);
int							ft_strcmpedit(char *s1, char *s2);
void						printlinkdlist(t_Command_Table3 *table);
char						*ft_strjoin1(char *s1, char *s2);
char						*ft_strjoin3(char *s1, char *s2);
char						*heredocwhile(char **heredoc);
char						*heredocstring(char *delimiter);
char						*ft_getenv(envp *env, char *str);
//------------------------------------zbentalh---------------------------------------
void						ft_lstadd_back1(t_Command_Table **lst,
						t_Command_Table *new);
t_Command_Table3			*make_last(t_Command_Table *table);
t_Command_Table				*ft_lst(char **new, int *i, t_Command_Table2 *w);
char						**ft_split(char const *s, char c);
int							ft_make(t_Command_Table **a, char **new,
								t_Command_Table2 *w);
char						*table_fixer_two(char **new);
t_Command_Table3			*ft_make_last(t_Command_Table **a,
								t_Command_Table3 *table, int *k);
int							count(t_Command_Table3 *table);
void						ft_free(char **str);
int							syntax_help(char *r);
char						*ft_itoa(int n);
char						*ft_en(char *arg, envp *env, int g);
								// g != 1 for heredoc;
int							check_all(char *new);
int							ft_check_syntax_2_cnt(char *new, int i, int j);
#endif