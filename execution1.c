/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:12:37 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/13 02:47:02 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_creat_pipe(int num_pipes,int pipes[num_pipes][2])
{
	int i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
            i--;
			perror("pipe error");
            while (i >= 0)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                i--;
            }
			return ((void)(g_globale.exit_child = 255));
		}
		i++;
	}
}

void ft_here_null_with_pipe(char *str,int *pipa,char **heredoc,int *b)
{
	int status;
	
	g_globale.idheredok = 0;
	g_globale.idheredok = fork();
	if (g_globale.idheredok == 0)
	{
		signal(SIGINT, SIG_DFL);
		str = heredocwhile(heredoc);
		if (str)
			write(pipa[1], str, ft_strlen3(str));
		close(pipa[1]);
		close(pipa[0]);
		free(str);
		exit(0);
	}
	else
	{
		waitpid(g_globale.idheredok, &status, 0);
		if (WIFSIGNALED(status))
		{
				g_globale.exit_child = 1;
				*b = 1;
		}
		close(pipa[1]);
	}	
}

void the_point_case_yay(void)
{
    printf("minishell: .: filename argument required\n.; .: usage: . filename [arguments]\n");
	g_globale.exit_child = 2;
    free(g_globale.pid);
}

void the_dir_case(DIR *dir,char *arg)
{
	closedir(dir);
	printf("mini: %s: is a directory\n", arg);
	g_globale.exit_child = 126;
    free(g_globale.pid);
}

void	ft_unset_norm(char **args,envp **envp1,int i,int j)
{
	while (args[i])
	{
		j = unset(envp1, args[i]);
		if (j == 1)
			g_globale.exit_child = 1;
		i++;
	}
	if (i == 1)
		g_globale.exit_child = 0;
	free(g_globale.pid);
}

void	ft_export_norm(char **args,envp **envp1,int i)
{
	g_globale.exit_child = 0;
	if (args[1] == NULL)
	{
		export(envp1, NULL);
		free(g_globale.pid);
		return ;
	}
	else
	{
		while (args[i])
		{
			export(envp1, args[i]);
			i++;
		}
	}
	free(g_globale.pid);
}

void	ft_export(char **args)
{
	if (ft_test(args) == 1)
		echo(args[1], ft_collect(args, 2));
	else
		echo(NULL, ft_collect(args, 1));
	free(g_globale.pid);
	g_globale.exit_child = 0;
}

void ft_exiit(char **args)
{
	free(g_globale.pid);
	printf("exit\n");
	if (args[1] != NULL)
	{			
		if (ft_isdigit1(args[1]) == 0)
			g_globale.exit_child = ft_atoi(args[1]);
		else if (ft_isdigit1(args[1]) == 1)
		{
			printf("minishell: exit: %s: numeric argument required\n",args[1]);
			g_globale.exit_child = 255;
			exit(g_globale.exit_child);
		}
        if (args[2] != NULL)
		{
			printf("minishell: exit: too many arguments\n");
			g_globale.exit_child = 1;
			return ;
		}
	}
	exit(g_globale.exit_child);
}

void	ft_execut_now(t_pipex *pipex,t_Command_Table3 *table, char **env)
{
	pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],"/");
	pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],
		table->args[0]);
	if (access(pipex->paths[pipex->i], F_OK) == 0)
	{
		if (execve(pipex->paths[pipex->i], table->args, env) == -1)
			(perror("execve error"),exit(126));
	}
	pipex->i++;
	free(pipex->paths[pipex->i - 1]);
}

void 	ft_norm(char *arg)
{
	if (ft_strserarch(arg, '/') == 1)
		ft_error1("minishell: No such file or directory: ",arg);
	else
		ft_error1("minishell: command not found: ", arg);
}

void	 ft_wait_unocmd(int i,t_Command_Table3 *table)
{
	int status;

	waitpid(g_globale.pid[i], &status, 0);
	close(table->outfile);
	close(table->infile);
	if (WIFSIGNALED(status))
		g_globale.exit_child = 128 + WTERMSIG(status);
	if (WIFEXITED(status))
		g_globale.exit_child = WEXITSTATUS(status);
	free(g_globale.pid);
}

int builtin_check(t_Command_Table3 *table, envp **envp1, int *b, DIR *dir)
{
	int i;

	i = 1;
	if (*b != 0 || table->args[0] == NULL)
		return (free(g_globale.pid),1);        
    if (  ft_strncmp(table->args[0], ".", 2) == 0)
        return(the_point_case_yay(),1);
	if ((dir = opendir(table->args[0])) != NULL)
		return(the_dir_case(dir,table->args[0]),1) ;
	if (ft_strncmp(table->args[0], "cd", 3) == 0)
		return (ft_cd(envp1, table->args[1]),free(g_globale.pid),1);
	else if (ft_strncmp(table->args[0], "env", 4) == 0)
		return (envv(*envp1),free(g_globale.pid),1);
	else if (ft_strncmp(table->args[0], "unset", 6) == 0)
		return(ft_unset_norm(table->args,envp1,i,0),1);
	else if (ft_strncmp(table->args[0], "export", 7) == 0)
		return(ft_export_norm(table->args,envp1,i),1) ;
	else if (ft_strncmp(table->args[0], "echo", 5) == 0)
		return(ft_export(table->args),1);
	else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
		return (g_globale.exit_child = 0,free(g_globale.pid),ft_pwd(),1);
	else if (ft_strncmp(table->args[0], "exit", 5) == 0)
		ft_exiit(table->args);
	return (0);
}

void	child_unocmd(t_Command_Table3 *table,char **env,t_pipex *pipex,int *pipa)
{
	if (table->outfile != -2 && table->outfile != -1)
		(dup2(table->outfile, STDOUT_FILENO),close(table->outfile));
	if (table->infile != -2 && table->infile != -1)
		(dup2(table->infile, STDIN_FILENO),close(table->infile));
	if (table->heredoc[0] != NULL  && ft_strcmp(table->in_or_here, "heredoc") == 0)
		(dup2(pipa[0], STDIN_FILENO),close(pipa[0]),close(pipa[1]));
    else if (table->heredoc[0] != NULL  )
        (close(pipa[0]), close(pipa[1]));  
	if ((table->args[0][0] == '.' || table->args[0][0] == '/')
		&& access(table->args[0], F_OK) == 0)
	{
		if (execve(table->args[0], table->args, env) == -1)
			(write(2, "minishell: ", 11), perror(table->args[0]), exit(126));
	}
	else if (table->args[0][0] == '.' || table->args[0][0] == '/')
		(write(2, "minishell: ", 11),perror(table->args[0]),exit(127));
	pipex->i = 0;
	while (pipex->paths && pipex->paths[pipex->i])
		ft_execut_now(pipex,table,env);
	if (table->args)
		ft_norm(table->args[0]);
} 

void ft_free_X(t_x *x)
{
	int i;

	i = 0;
	while(i < x->num_pipes)
	{
		free(x->pipes[i]);
		i++;
	}
	free(x->pipes);
	free(x);
}

t_x	*ft_init_X(t_Command_Table3 *table)
{
	t_x *x;
	int i;
	
	x = malloc(sizeof(t_x));
	i = 0;
	x->dir = NULL;
	x->i = 1;
	x->b = 0;
	x->num_pipes = count(table) - 1;
	x->str =NULL;
	x->pipes = malloc(sizeof(int *)  * x->num_pipes);
	while(i < x->num_pipes)
	{
		x->pipes[i] = malloc(sizeof(int) * 2);	
		i++;
	}
	return (x);
}

void ft_onecmd(t_Command_Table3 *table,t_pipex *pipex,envp **envp1,char **env)
{
	t_x *x;

	x = ft_init_X(table);
	if (table->heredoc[0] != NULL)
	{   
		if (pipe(x->pipa) < 0)
			return (perror("pipe error"),(g_globale.exit_child = 255),ft_free_X(x));
		ft_here_null_with_pipe(x->str,x->pipa,table->heredoc,&x->b);
	}
	if (builtin_check(table,envp1,&x->b,x->dir) == 1)
		return (ft_free_X(x));
	g_globale.pid[x->i] = fork();
	if (g_globale.pid[x->i] < 0)
		(perror("fork error"),ft_free_X(x),exit(-1));
	else if (g_globale.pid[x->i] == 0)
			child_unocmd(table,env,pipex,x->pipa);
	else
			ft_wait_unocmd(x->i,table);
	ft_free_X(x);
}
int count_pi_herdo(t_Command_Table3 *table3)
{
	int aka;

    aka = 0;
	while (table3)
		{
			if (table3->heredoc[0] != NULL)
				aka++;
			table3 = table3->next;
		}
	return (aka);
}

void	open_pipe_nounocmd(int aka, int pixa[aka][2])
{
	 int tl = 0;
     while (tl < aka)
     {
        if (pipe(pixa[tl]) == -1)
        	return (perror("pipe error"),(void)(g_globale.exit_child = 255));
        tl++;
    }
    tl = 0;
}

t_y	*ft_init_Y()
{
	t_y *y;

	y = malloc(sizeof(t_y));
	y->mm = 0;
	y->lb = 0;
	y->lj = 0;
	y->str = NULL;
	return (y);
}

void	ft_here_open(t_Command_Table3 *table,int aka,int pixa[aka][2],t_y *y)
{  
	(signal(SIGQUIT, herquite),signal(SIGINT, SIG_DFL));
        while (table)
        {    
            if(table->heredoc[0] != NULL)
            {
                y->str = heredocwhile(table->heredoc);
                write(pixa[y->mm][1], y->str, ft_strlen3(y->str));
                y->mm++;  
            }
             table = table->next;    
        }
        while (y->lb < aka)
        {
            close(pixa[y->lb][0]);
            close(pixa[y->lb][1]);
            y->lb++;
        }
		free(y->str);
		free(y);
		exit(0);
}

void	ft_idk(t_Command_Table3 *table,int aka,int pixa[aka][2],int *b)
{
	
	t_y *y;

	y = ft_init_Y();
	g_globale.idheredok = fork();
	if (g_globale.idheredok < 0)
		(perror("fork error"),free(y),exit(-1));
	else if (g_globale.idheredok == 0)
		ft_here_open(table,aka,pixa,y);
	else
	{
		waitpid(g_globale.idheredok, b, 0);
    	while (y->lj < aka)
        {
            close(pixa[y->lj][1]);
            y->lj++;
        }
		if (WIFSIGNALED(*b))
			(*b) = 1;	
		free(y);
	}
}
void	shell_with_pipes(t_Command_Table3 *table, char **env, t_pipex *pipex,
		envp **envp1)
{
	DIR *dir;
	pipex->paths = NULL;
	pathfinder(pipex, *envp1);
	int num_pipes;
	 num_pipes = count(table) - 1;
	 int pipes[num_pipes][2];
    // int pipa[2];
     int i = 0;
	int j = 0;
	 int r = 0;
	// int b = 0;
     //char *str = NULL;
	// dir =NULL;
	g_globale.pid = malloc(sizeof(int) * count(table));
	g_globale.command_count = count(table);
	ft_creat_pipe(num_pipes,pipes);
	if (num_pipes == 0)
		ft_onecmd(table,pipex,envp1,env);

// --------------------------------------------------------------------
// 	multiple pipes
	else
	{
		int k = count(table);
		int b = 0;
		int aka = 0;
        t_Command_Table3 *table4 = table;
        int mm = 0;  //for heredoc
		aka = count_pi_herdo(table);
        int pixa[aka][2];
        if(aka != 0)
                (open_pipe_nounocmd(aka,pixa),ft_idk(table4,aka,pixa,&b));
		i = 0;
       mm = 0;
		while (!b && i < k)
		{
			r = 1;
			g_globale.pid[i] = fork();

			if (g_globale.pid[i] < 0)
			{
				perror("fork error");
				exit(-1);
			}
			else if (g_globale.pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				if (i == 0)
				{
					int l = 0;
					dup2(pipes[i][1], 1);
					while (l < num_pipes)
					{
						close(pipes[l][0]);
						close(pipes[l][1]);
						l++;
					}
				}
				else if (i == num_pipes)
				{
					dup2(pipes[i - 1][0], 0);
					j = 0;
					while (j < num_pipes)
					{
						close(pipes[j][0]);
						close(pipes[j][1]);
						j++;
					}
				}
				else if (i != 0)
				{
					dup2(pipes[i - 1][0], STDIN_FILENO);
					dup2(pipes[i][1], STDOUT_FILENO);
					j = 0;
					while (j < num_pipes)
					{
						close(pipes[j][0]);
						close(pipes[j][1]);
						j++;
					}
                    
				}
                    if ( table->args[0] != NULL &&  ft_strncmp(table->args[0], ".", 2) == 0)
                    {
                    write(2,"minishell: .: filename argument required\n.; .: usage: . filename [arguments]\n", 78);
					g_globale.exit_child = 2;
					exit(g_globale.exit_child);
                     }
				if ((dir = opendir(table->args[0])) != NULL)
				{
					closedir(dir);
					write(2, "minishell: is a directory : ", 28);
					write(2, table->args[0], ft_strlen3(table->args[0]));
					write(2, "\n", 1);
					g_globale.exit_child = 126;
					exit(g_globale.exit_child);
				}
				if (table->outfile != -2 && table->outfile != -1)
					 dup2(table->outfile, STDOUT_FILENO);
				if (table->infile != -2 && table->infile != -1)
                     dup2(table->infile, STDIN_FILENO);				
				if (table->heredoc[0] != NULL && ft_strcmp(table->in_or_here, "heredoc") == 0)
				{
					if(dup2(pixa[mm][0], STDIN_FILENO) == -1)
                       (perror("dup2 error"), exit(-1));
                    int la = 0;
                    while (la < aka)
                    {
                        close(pixa[la][0]);
                        close(pixa[la][1]);
                        la++;
                    } 
                    mm++;
				}
                else if (table->heredoc[0] != NULL )
                {
                    int la = 0;
                    while (la < aka)
                    {
                        close(pixa[la][0]);
                        close(pixa[la][1]);
                        la++;
                    }
                    mm++;
                }
				if (ft_strncmp(table->args[0], "cd", 3) == 0)
					(ft_cd(envp1, table->args[1]),exit(0));	
				else if (ft_strncmp(table->args[0], "env", 4) == 0)
					(printf("env\n"),envv(*envp1),exit(0));
				else if (ft_strncmp(table->args[0], "unset", 6) == 0)
				{
					int i = 1;
					printf("unset\n");
					while (table->args[i])
					{
						unset(envp1, table->args[i]);
						i++;
					}
					exit(0);
				}
				else if (ft_strncmp(table->args[0], "export", 7) == 0)
				{
					g_globale.exit_child = 0;
					int i = 1;
					if (table->args[1] == NULL)
						(export(envp1, NULL),exit(0));						
					else
					{
						while (table->args[i])
						{
							export(envp1, table->args[i]);
							i++;
						}
					}
					exit(0);
				}
				else if (ft_strncmp(table->args[0], "echo", 5) == 0)
				{
					if (ft_test(table->args) == 1)
						echo(table->args[1], ft_collect(table->args, 2));
					else
						echo(NULL, ft_collect(table->args, 1));
					exit(0);
				}
				else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
					(ft_pwd(),exit(0));								
				else if (ft_strncmp(table->args[0], "exit", 5) == 0)
				{
					if (table->args[1] != NULL)
					{
						if (table->args[2] != NULL)
						{
							printf("minishell: exit: too many arguments\n");
							g_globale.exit_child = 1;
							exit(1);
						}
						if (ft_isdigit1(table->args[1]) == 0)
							g_globale.exit_child = ft_atoi(table->args[1]);
						else
						{
							printf("minishell: exit: %s: numeric argument required\n",
									table->args[1]);
							g_globale.exit_child = 255;
							exit(g_globale.exit_child);
						}
					}
					exit(g_globale.exit_child);
				}
				if ((table->args[0][0] == '.' || table->args[0][0] == '/')
					&& access(table->args[0], F_OK) == 0)
				{
					if (execve(table->args[0], table->args, env) == -1)
						(perror("execve error"),exit(126));
				}
				else if (table->args[0][0] == '.' || table->args[0][0] == '/')
				{
					write(2, "minishell: ", 11);
					perror(table->args[0]);
					g_globale.exit_child = 127;
					exit(g_globale.exit_child);
				}
				pipex->i = 0;
				while (pipex->paths && pipex->paths[pipex->i])
				{
					pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],
							"/");
					pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i],
							table->args[0]);
					if (access(pipex->paths[pipex->i], F_OK) == 0)
					{
						if (execve(pipex->paths[pipex->i], table->args, env) ==
							-1)
							(perror("execve error"),exit(126));
					}
					pipex->i++;
				}
				if (table->args)
				{
					if (ft_strserarch(table->args[0], '/') == 1)
						ft_error1("minishell: No such file or directory: ",
								table->args[0]);
					else
						ft_error1("minishell: command not found: ",
								table->args[0]);
                }
			}
			else
			{
                if (table->heredoc[0] != NULL)
				{
                    (close(pixa[mm][0]),close(pixa[mm][1]));
                    mm++;
				}
				if (i == 0)
					close(pipes[i][1]);	
				else if (i == num_pipes)
					(close(pipes[i - 1][0]),close(pipes[i - 1][1]));
				else
					(close(pipes[i][1]),close(pipes[i - 1][0]),close(pipes[i - 1][1]));
				(close(table->outfile),close(table->infile));
				table = table->next;
				i++;
			}
		}
        int xx = 0;
       while( xx < aka)
       {
           (close(pixa[xx][0]),close(pixa[xx][1]));
           xx++;
       }
		if (r)
		{
			int status;
			waitpid(g_globale.pid[num_pipes], &status, 0);
			int j = 0;
			while (j < num_pipes)
			{
				(close(pipes[j][0]),close(pipes[j][1]));
				j++;
			}
			j = 0;
			while (j < num_pipes)
				waitpid(g_globale.pid[j++], NULL, 0);
			if (WIFSIGNALED(status))
				g_globale.exit_child = 128 + WTERMSIG(status);
			else if (WIFEXITED(status))
				g_globale.exit_child = WEXITSTATUS(status);
		}
		free(g_globale.pid);
        
	}
}
