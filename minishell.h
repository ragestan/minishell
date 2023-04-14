/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:46:03 by zbentalh          #+#    #+#             */
/*   Updated: 2023/04/14 15:40:42 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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

typedef struct a_int
{
	int						i;
	int						j;
	int						k;
	int						z;
	char					*new2;
}							t_int;

typedef struct w
{
	char				*new;
	char				**split;
	int					i;
	int					k;
	t_Command_Table		*table;
	t_Command_Table2	z;
	t_Command_Table3	*last_table;
	t_Command_Table3	*tmp;
	struct termios		term;
	struct termios		oldterm;
}							t_w;

typedef struct NODE
{
	char					*str;
	int						option;
	int						free;
	int						prinlast;
	struct NODE				*next;
}							t_envp;
typedef struct pipex
{
	char					**cmd;
	char					**paths;
	int						i;
	char					*save;
	int						dkhlni;
}							t_pipex;
typedef struct cdd
{
	char					*ptr;
	char					*ptr1;
	char					*oldpwd;
	char					*pwd;
	int						value;
}							t_cdd;
typedef struct X
{
	DIR						*dir;
	int						i;
	int						b;
	int						num_pipes;
	char					*str;
	int						pipa[2];
	int						**pipes;
}							t_x;

typedef struct Y
{
	char					*str;
	int						mm;
	int						lb;
	int						lj;
}							t_y;

typedef struct Z
{
	DIR						*dir;
	int						num_pipes;
	int						i;
	int						r;
	int						k;
	int						b;
	int						aka;
	int						mm;
	int						**pipes;
	int						**pixa;
	char					**env;
}							t_z;

typedef struct a_globale
{
	t_envp					*env1;
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
void						ft_cd(t_envp **env, char *str);
void						export(t_envp **env1, char *str);
int							ft_strcmp(char *s1, char *s2);
int							ft_strcmpedit(char *s1, char *s2);
int							unset(t_envp **env1, char *str);
void						echo(char *option, char *str);
void						envv(t_envp *str);
void						pathfinder(t_pipex *pipex, t_envp *envp);
size_t						ft_strlen3(const char *s);
char						*ft_strjoin(char *s1, char *s2, int count);
void						make_node(t_envp **st, char *str);
void						ft_putstr_fd(char *s, int fd);
void						ft_putnbr_fd(int n, int fd);
int							ft_isdigit(int c);
int							ft_isalpha(int c);
int							ft_checkcote(char *str, int j, int i, int k);
int							ft_isalnum(int c);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
size_t						ft_strlen3(const char *s);
char						*ft_strjoin(char *s1, char *s2, int count);
void						make_node(t_envp **st, char *str);
char						*ft_strdup_z(const char *s1);
void						ft_putchar_fd(char c, int fd);
void						shell_with_pipes(t_Command_Table3 *table,
								char **env, t_pipex *pipex, t_envp **envp1);
char						*ft_strjoin2(char *s1, char const *s2);
void						printnodeenv(t_envp *str);
char						*ft_strplusequal(char *str, int k);
int							ft_strcmpedit(char *s1, char *s2);
void						printlinkdlist(t_Command_Table3 *table);
char						*ft_strjoin1(char *s1, char *s2);
char						*ft_strjoin3(char *s1, char *s2);
char						*heredocwhile(char **heredoc);
char						*heredocstring(char *delimiter);
char						*ft_getenv(t_envp *env, char *str);
void						ft_exit(int exit_code);
int							ft_atoi(const char *str);
int							ft_isdigit1(char *str);
int							ft_test(char **str);
int							ft_collect_help(char **str, int i);
char						*ft_collect(char **str, int i);
void						ft_error1(char *str, char *st);
int							valideinput(char *str);
void						sigquit_handler(int sig);
void						herquite(int sig);
void						ft_lstadd_back(t_envp **lst, t_envp *new);
t_envp						*ft_lstlast_z(t_envp *lst);
t_envp						*ft_lstnew(char *content, int option);
void						updatepwd(t_envp **env, char *str);
void						updateoldpwd(t_envp **env, char *str);
int							ft_strnstredit(const char *str);
char						*ft_strdupedit(const char *s1);
int							updateenv(t_envp *env, char *str, int b);
void						printnodealpha(t_envp *str);
void						ft_putstredit(char *s);
void						printnode_export(t_envp *stp);
void						ft_writeme1(char *str);
void						ft_writeme2(t_envp **env1);
int							ft_updateenv_helper(char *str, t_envp *st);
int							ft_updateenv_helper1(char *str, t_envp *st);
t_envp						*sort_list(t_envp *lst, int (*cmp)(char *, char *));
void						ft_export_help(char *str, t_envp **env1, int x,
								char *stredit);
int							ft_creat_pipe(int num_pipes, int **pipes);
void						ft_here_null_with_pipe(char *str, int *pipa,
								char **heredoc, int *b);
void						the_point_case_yay(void);
void						the_dir_case(DIR *dir, char *arg);
void						ft_unset_norm(char **args, t_envp **envp1, int i,
								int j);
void						ft_export_norm(char **args, t_envp **envp1, int i);
void						ft_export(char **args);
void						ft_exiit(char **args);
int							ft_execut_now(t_pipex *pipex,
								t_Command_Table3 *table, char **env);
void						ft_norm(char *arg);
void						ft_wait_unocmd(int i, t_Command_Table3 *table);
int							builtin_check(t_Command_Table3 *table,
								t_envp **envp1, int *b, DIR *dir);
void						child_unocmd(t_Command_Table3 *table, char **env,
								t_pipex *pipex, int *pipa);
void						ft_free_xx(t_x *x);
t_x							*ft_init_xx(t_Command_Table3 *table);
void						ft_onecmd(t_Command_Table3 *table, t_pipex *pipex,
								t_envp **envp1, char **env);
int							count_pi_herdo(t_Command_Table3 *table3);
void						open_pipe_nounocmd(t_z *z, int aka, int **pixa);
t_y							*ft_init_yy(void);
void						ft_here_open(t_Command_Table3 *table, int aka,
								int **pixa, t_y *y);
void						ft_idk(t_Command_Table3 *table, int aka, int **pixa,
								int *b);
void						ft_close_pipe(int num_pipes, int **pipes, int i);
void						ft_close_pipe2(int num_pipes, int **pipes, int i);
void						ft_close_pipe3(int num_pipes, int **pipes, int i);
void						the_point_case_in_multi_pipe(void);
void						if_dir_in_multi_pipe(DIR *dir,
								t_Command_Table3 *table);
void						reading_from_heredoc(int aka, int **pixa, int *mm);
void						not_reading_from_heredoc(int aka, int **pixa,
								int *mm);
void						unset_in_multi_pipe(t_Command_Table3 *table,
								t_envp **envp1);
void						export_in_multipipe(t_Command_Table3 *table,
								t_envp **envp1);
void						echo_in_multipipe(t_Command_Table3 *table);
void						exit_in_multipipe(t_Command_Table3 *table);
void						dir_in_multipipe(t_Command_Table3 *table,
								char **env);
void						dir_in_multipipe2(t_Command_Table3 *table);
void						execute_in_multpipe(t_pipex *pipex,
								t_Command_Table3 *table, char **env);
void						cmd_not_found(t_Command_Table3 *table);
void						closing_pipes(int **pixa, int *mm);
void						closing_more_pipes(int aka, int **pixa);
void						waiting_for_child(int num_pipes, int **pipes);
void						c_more_pipes(t_Command_Table3 *table, int num_pipes,
								int **pipes, int i);
t_z							*ft_init_zz(t_Command_Table3 *table, char **env);
void						norm_work_exec(t_z *z, t_Command_Table3 *table);
void						norm_builtin(t_envp **envp1,
								t_Command_Table3 *table);
void						norm_wrok_exec2(t_Command_Table3 *table,
								t_pipex *pipex, char **env);
int							norm_last(t_z *z, t_Command_Table3 *table,
								t_pipex *pipex, t_envp **envp1);
void						norm_last2(t_z *z);
void						free_z(t_z *z);
t_z							*fork_update_r_value(t_z *z);
t_z							*norm_close_pipes(t_z *z, t_Command_Table3 *table);
t_Command_Table3			*norm_last_realy(t_z *z, t_Command_Table3 *tmp,
								t_envp **envp1, t_pipex *pipex);
void						sigint_handler(int sig);
void						herquite(int sig);
void						sigquit_handler(int sig);
int							count(t_Command_Table3 *table);
void						ft_none_env(char **env, t_envp **env1);
void						ft_lstadd_back1(t_Command_Table **lst,
								t_Command_Table *new);
t_Command_Table3			*make_last(t_Command_Table *table, int i, int j);
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
char						*ft_en(char *arg, t_envp *env, int g);
int							check_all(char *new);
int							ft_check_syntax_2_cnt(char *new, int i, int j);
void						ft_plus(size_t *i, size_t *j);
int							ft_check_syntax_3(char *new);
int							ft_check_syntax_4(char *new, int i);
int							ft_check_syntax_5(char *new, int i);
char						*new_new(char *new, int k);
char						*ft_strdup3(const char *s1);
void						ft_free(char **str);
t_Command_Table2			ft_init(void);
void						ft_lst_normw(char **new, int *i,
								t_Command_Table2 *w);
void						ft_lst_normlast(char **new, t_Command_Table *l,
								int *i, t_Command_Table2 *w);
char						*ft_strdup(const char *src, int *k);
void						ft_lst_norm(int *i, t_Command_Table2 *w);
char						*ft_strdupnor(char *dest, const char *src, int *i,
								int *l);
char						*ft_strdupnor2(char *dest, const char *src, int *i,
								int *l);
size_t						ft_strlen(const char *c, int k);
void						ft_strlen_nor(const char *c, size_t *i, size_t *j);
void						ft_lst_norm0(int *i, t_Command_Table2 *w,
								t_Command_Table *l);
void						ft_lst_norm1(int *i, t_Command_Table2 *w,
								t_Command_Table *l);
void						ft_lst_norm4(int *i, t_Command_Table2 *w,
								t_Command_Table *l);
void						ft_lst_norm3(int *i, t_Command_Table2 *w,
								t_Command_Table *l);
void						ft_lst_norm5(int *i, t_Command_Table2 *w,
								t_Command_Table *l);
t_Command_Table				*ft_lstlast(t_Command_Table *lst);
void						ft_lstadd_back1(t_Command_Table **lst,
								t_Command_Table *new);
t_Command_Table				*ft_var(t_Command_Table *table, t_envp *env);
t_int						ft_initint(void);
int							ft_env_count(char *arg, t_envp *env, int g);
int							ft_checkcote(char *str, int j, int i, int k);
void						ft_env_cote(char *arg, int *i, int *j);
void						ft_plusi(int *i, int *j);
void						ft_env_norm5(char *arg, char *new, t_envp *tmp,
								t_int *w);
void						ft_env_norm2(t_envp *tmp, char *arg, char *new,
								t_int *w);
int							ft_strcmpedit2(char *s1, char *s2, size_t j);
int							ft_is_ad(char *str);
void						ft_env_norm(char *arg, char *new, t_int *w);
char						*ft_itoa(int n);
size_t						ft_count(int n);
void						ft_plus2(int *i, int *j);
void						ft_env_norm3(char *arg, t_int *w);
void						ft_env_norm4(char *arg, t_int *w);
int							char_is_ad(char c);
char						*ft_en_cote(char *arg, char *new, t_int *w);
char						*ft_en_norm4(char *arg, char *new, t_envp *tmp,
								t_int *w);
char						*ft_en_norm2(t_envp *tmp, char *arg, char *new,
								t_int *w);
char						*ft_en_norm(char *arg, char *new, char *new2,
								t_int *w);
char						*ft_en_norm3(char *arg, char *new, t_int *w);
t_Command_Table				*ft_cote(t_Command_Table *table);
char						*ft_cote2(const char *src, int i, int l);
char						*ft_cote2_norm(char *dest, char *src, int *i,
								int *l);
size_t						ft_strlencote(const char *c, size_t i, size_t j);
t_Command_Table3			*ft_make_last(t_Command_Table **a,
								t_Command_Table3 *table, int *k);
t_Command_Table3			*make_last(t_Command_Table *table, int i, int j);
void						ft_lstadd_back_last(t_Command_Table3 **lst,
								t_Command_Table3 *new);
void						freestack_last(t_Command_Table **stack);
t_Command_Table3			*ft_lstlast_last(t_Command_Table3 *lst);
int							last_infile(t_Command_Table *table, int fd);
int							last_outfile_norm(t_Command_Table *table, int fd);
int							last_outfile_norm2(t_Command_Table *table, int fd);
int							last_outfile_norm3(t_Command_Table *table, int fd);
int							last_outfile(t_Command_Table *table, int fd, int i);
int							in_or_here(t_Command_Table *table);
size_t						ft_strlen2(const char *c);
char						*ft_strdup2(const char *src);
int							ft_lstsize(t_Command_Table *lst, int k);
t_Command_Table3			*make_last_norm(t_Command_Table3 *last_table, int i,
								int j);
int							ft_space(char *str);
size_t						new_count(char *new, size_t k);
char						*new_all(char *new, char *new_new, int *i, int *j);
size_t						ft_strlen33(const char *s);
char						*char_plus_2cote(char *str, char *new, int *i,
								int *j);
char						*char_plus_1cote(char *str, char *new, int *i,
								int *j);
char						*char_plus_outfile(char *str, char *new, int *i,
								int *j);
char						*char_plus_heredoc(char *str, char *new, int *i,
								int *j);
char						*char_plus(char *str, char *new, int *i, int *j);
void						new_count_norm(char *new, size_t *i, size_t *j);
char						**arg(char **str, int i, int j);
int							strdoublelen(char **str);
void						freestack(t_Command_Table **stack);
void						freestack_3(t_Command_Table3 **stack);
void						ft_plus3(size_t *i, size_t *j);
t_Command_Table				*ft_all_nor(t_Command_Table *table, t_envp *env);
void						ft_all_nor2_nor(void);
char						**ft_all_nor2_nor2(char **split, char *new);
void						ft_all_nor2(char **split, char *new, int g_fork,
								int i);
void						free_z(t_z *z);
t_w							*ft_init_w(void);
t_w							*ft_all_norm_last(t_w *w);
t_Command_Table3			*ft_all(t_envp *env);
void						norm_main(char **env, int argc, t_envp **env1);
#endif
