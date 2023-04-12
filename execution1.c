/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:12:37 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/12 22:12:55 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_with_pipes(t_Command_Table3 *table, char **env, t_pipex *pipex,
		envp **envp1)
{
	DIR *dir;
	pipex->paths = NULL;
	pathfinder(pipex, *envp1);
	int num_pipes = count(table);
	num_pipes--;
	int pipes[num_pipes][2];
    int pipa[2];
    int i = 0;
	int j = 0;
	int r = 0;
    char *str = NULL;
    
	g_globale.pid = malloc(sizeof(int) * count(table));
	g_globale.command_count = count(table);
	
	// create pipes
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
	i = 0;
	if (num_pipes == 0)
	{
       
		if (table->heredoc[0] != NULL)
		{
			//write(2, "heredoc not supported\n", 22);
            
			if (pipe(pipa) < 0)
			{
				perror("pipe error");
				return ((void)(g_globale.exit_child = 255));
			}

			g_globale.idheredok = 0;
			g_globale.idheredok = fork();
			if (g_globale.idheredok == 0)
			{
				signal(SIGINT, SIG_DFL);
				printf("----------------------------\n");
				str = heredocwhile(table->heredoc);
				if (str)
					write(pipa[1], str, ft_strlen3(str));
				//ft_putstr_fd(str, pipa[1]);
				close(pipa[1]);
				close(pipa[0]);
				free(str);
				exit(0);
			}
			else
			{
				waitpid(g_globale.idheredok, NULL, 0);
				close(pipa[1]);

				//close(pipa[0]);
			}
			
		}
		if (table->args[0] == NULL)
        {
            free(g_globale.pid);
            return ;
        }
             if (  ft_strncmp(table->args[0], ".", 2) == 0)
        {
            printf("----> %s\n", table->args[0]);
                    printf("minishell: .: filename argument required\n.; .: usage: . filename [arguments]\n");
					g_globale.exit_child = 2;
                    free(g_globale.pid);
					return ;
        }
		if ((dir = opendir(table->args[0])) != NULL)
		{
			closedir(dir);
			printf("mini: %s: is a directory\n", table->args[0]);
			g_globale.exit_child = 126;
            free(g_globale.pid);
			return ;
		}
		if (ft_strncmp(table->args[0], "cd", 3) == 0)
		{
			ft_cd(envp1, table->args[1]);
			free(g_globale.pid);
			return ;
		}
		else if (ft_strncmp(table->args[0], "env", 4) == 0)
		{
			envv(*envp1);
			free(g_globale.pid);
			return ;
		}
		else if (ft_strncmp(table->args[0], "unset", 6) == 0)
		{
			int i = 1;
			int j = 0;

			while (table->args[i])
			{
				j = unset(envp1, table->args[i]);
				if (j == 1)
					g_globale.exit_child = 1;
				i++;
			}
			if (i == 1)
				g_globale.exit_child = 0;
			free(g_globale.pid);
			return ;
		}
		else if (ft_strncmp(table->args[0], "export", 7) == 0)
		{
			g_globale.exit_child = 0;
			int i = 1;
			if (table->args[1] == NULL)
			{
				export(envp1, NULL);
				free(g_globale.pid);
				return ;
			}
			else
			{
				while (table->args[i])
				{
					export(envp1, table->args[i]);
					i++;
				}

				//printf("-------------------\n");
				//export(&envp1, NULL);
			}
			free(g_globale.pid);
			return ;
		}
		else if (ft_strncmp(table->args[0], "echo", 5) == 0)
		{
			if (ft_test(table->args) == 1)
				echo(table->args[1], ft_collect(table->args, 2));
			else
			{
				//printf("%s------------>\n",ft_collect(table->args,1));
				echo(NULL, ft_collect(table->args, 1));
			}
			free(g_globale.pid);
			g_globale.exit_child = 0;
			return ;
		}
		else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
		{
			ft_pwd();
			free(g_globale.pid);
			g_globale.exit_child = 0;
			return ;
		}
		else if (ft_strncmp(table->args[0], "exit", 5) == 0)
		{
			free(g_globale.pid);
			printf("exit\n");
			if (table->args[1] != NULL)
			{
				
				if (ft_isdigit1(table->args[1]) == 0)
					g_globale.exit_child = ft_atoi(table->args[1]);
				else if (ft_isdigit1(table->args[1]) == 1)
				{
					printf("minishell: exit: %s: numeric argument required\n",
							table->args[1]);
					g_globale.exit_child = 255;
					exit(g_globale.exit_child);
				}
                if (table->args[2] != NULL)
				{
					printf("minishell: exit: too many arguments\n");
					g_globale.exit_child = 1;
					return ;
				}
			}
			exit(g_globale.exit_child);
		}
      

		g_globale.pid[i] = fork();
		if (g_globale.pid[i] < 0)
		{
			perror("fork error");
			exit(-1);
		}
		else if (g_globale.pid[i] == 0)
		{
			//write in a file
			if (table->outfile != -2 && table->outfile != -1)
			{
				dup2(table->outfile, STDOUT_FILENO);
				close(table->outfile);
				// close(table->infile);
			}
			if (table->infile != -2 && table->infile != -1)
			{
				dup2(table->infile, STDIN_FILENO);
				close(table->infile);
				//close(table->outfile);
			}
			if (table->heredoc[0] != NULL  && ft_strcmp(table->in_or_here, "heredoc") == 0)
			{
				dup2(pipa[0], STDIN_FILENO);
				close(pipa[0]);
				close(pipa[1]);
			}
            else if (table->heredoc[0] != NULL  )
            {
                close(pipa[0]);
                close(pipa[1]);
                
            }
			if ((table->args[0][0] == '.' || table->args[0][0] == '/')
				&& access(table->args[0], F_OK) == 0)
			{
				if (execve(table->args[0], table->args, env) == -1)
				{
					write(2, "minishell: ", 11);
					perror(table->args[0]);
					exit(126);
				}
				// else
				// {
				// write(2, "minishell: ", 11);
				// perror(table->args[0]);
				// exit(127);
				// }
			}
			else if (table->args[0][0] == '.' || table->args[0][0] == '/')
			{
				write(2, "minishell: ", 11);
				perror(table->args[0]);
				exit(127);
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
					if (execve(pipex->paths[pipex->i], table->args, env) == -1)
					{
						perror("execve error");
						exit(126);
					}
				}
				pipex->i++;
				free(pipex->paths[pipex->i - 1]);
			}
			if (table->args)
			{
				if (ft_strserarch(table->args[0], '/') == 1)
				{
					ft_error1("minishell: No such file or directory: ",
							table->args[0]);
				}
				else
					ft_error1("minishell: command not found: ", table->args[0]);
			}
		}
		else
		{
			int status;
			waitpid(g_globale.pid[i], &status, 0);
			close(table->outfile);
			close(table->infile);
            //close(pipa[0]);
			if (WIFSIGNALED(status))
			{
				g_globale.exit_child = 128 + WTERMSIG(status);
			}
			if (WIFEXITED(status))
			{
				g_globale.exit_child = WEXITSTATUS(status);
			}
			free(g_globale.pid);
		}
	}

	//multiple pipes
	else
	{
		int k = count(table);
		int b = 0;
		int aka = 0;
		t_Command_Table3 *table3 = table;
        t_Command_Table3 *table4 = table;
        int mm = 0;  //for heredoc
		while (table3)
		{
			if (table3->heredoc[0] != NULL)
				aka++;
			table3 = table3->next;
		}
        int pixa[aka][2];
            if(aka != 0)
            {
                
                int j = 0;
                while (j < aka)
                {
                    if (pipe(pixa[j]) == -1)
                    {
                        perror("pipe error");
                        return ((void)(g_globale.exit_child = 255));
                    }
                    j++;
                }
                j = 0;
                
            }
            if ( aka != 0 )
		    {
                // free(pipa);
                // pipa = malloc(sizeof(int) * 2);
			    // if (pipe(pipa) == -1)
			    // {
				//     perror("pipe error");
				//     return ((void)(g_globale.exit_child = 255));
			    // } 
                            
			    g_globale.idheredok = fork();
			    if (g_globale.idheredok < 0)
			    {
				    perror("fork error");
				    exit(-1);
			    }
			    else if (g_globale.idheredok == 0)
			    {
                    signal(SIGQUIT, herquite);
				    signal(SIGINT, SIG_DFL);
                    
                    while (table4)
                    {
                       
                        if(table4->heredoc[0] != NULL)
                        {
                            str = heredocwhile(table4->heredoc);
                            write(pixa[mm][1], str, ft_strlen3(str));
                            mm++;  
                        }
                       table4 = table4->next;
                       
                    }
                //     str = heredocwhile(table->heredoc);
                //   write(pixa[mm][1], str, ft_strlen3(str));
				    // close(pipa[1]);
				    // close(pipa[0]);
                    int lb = 0;
                    while (lb < aka)
                    {
                        close(pixa[lb][0]);
                        close(pixa[lb][1]);
                       lb++;
                    }
                    
				    free(str);
				    exit(0);
			    }
			    else
			    {
				    waitpid(g_globale.idheredok, &b, 0);
                    int lj = 0;
                    while (lj < aka)
                    {
                    
                        close(pixa[lj][1]);
                        lj++;
                    }
                    
				    // close(pixa[mm][1]);
                    
				    // close(p[1]);
				    if (WIFSIGNALED(b))
				    {
					    b = 1;
				    }
			    }
		    }
            
		i = 0;
       mm = 0;
		while (!b && i < k)
		{
            // int p[2];
            // pipe(p);
            //-------->heredoc
            
            
            
            // if (table->heredoc[0] != NULL && aka != 0 )
		    // {
            //     // free(pipa);
            //     // pipa = malloc(sizeof(int) * 2);
			//     // if (pipe(pipa) == -1)
			//     // {
			// 	//     perror("pipe error");
			// 	//     return ((void)(g_globale.exit_child = 255));
			//     // } 
                               
			//     g_globale.idheredok = fork();
			//     if (g_globale.idheredok < 0)
			//     {
			// 	    perror("fork error");
			// 	    exit(-1);
			//     }
			//     else if (g_globale.idheredok == 0)
			//     {
			// 	    signal(SIGINT, SIG_DFL);
            //         str = heredocwhile(table->heredoc);
            //         // if(str == NULL)
            //         // {
            //         //     free(str);
            //         //     exit(0);
            //         // }
            //       write(pixa[mm][1], str, ft_strlen3(str));
			// 	    // close(pipa[1]);
			// 	    // close(pipa[0]);
            //         int lb = 0;
            //         while (lb < aka)
            //         {
            //             close(pixa[lb][0]);
            //             close(pixa[lb][1]);
            //             lb++;
            //         }
                    
			// 	    free(str);
			// 	    exit(0);
			//     }
			//     else
			//     {
			// 	    waitpid(g_globale.idheredok, &b, 0);
			// 	    close(pixa[mm][1]);
                    
			// 	    // close(p[1]);
			// 	    if (WIFSIGNALED(b))
			// 	    {
			// 		    return ;
			// 	    }
			//     }
		    // }
            
            //-------->
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
				// child process
				if (i == 0)
				{
					int l = 0;
					// first child process
					// redirect stdout to the first pipe
					dup2(pipes[i][1], 1);
					while (l < num_pipes)
					{
						close(pipes[l][0]);
						close(pipes[l][1]);
						l++;
					}
                   
					// close all pipes except the first one
					// j = 0;
					// while (j < num_pipes)
					// {
					//         close(pipes[j][0]);
					//         close(pipes[j][1]);
					//     j++;
					// }
					//close(pipes[0][0]);
				}
				else if (i == num_pipes)
				{
					// last child process
					// redirect stdin to the last pipe
					dup2(pipes[i - 1][0], 0);
					// close all pipes except the last one
					j = 0;
					while (j < num_pipes)
					{
						close(pipes[j][0]);
						close(pipes[j][1]);
						j++;
					}
                   
					//close(pipes[num_pipes][1]);
				}
				else if (i != 0)
				{
					// intermediate child processes
					// redirect stdin to the previous pipe
					dup2(pipes[i - 1][0], STDIN_FILENO);
					// redirect stdout to the next pipe
					dup2(pipes[i][1], STDOUT_FILENO);
					// close all pipes except the previous and next ones
					j = 0;
					while (j < num_pipes)
					{
						close(pipes[j][0]);
						close(pipes[j][1]);
						j++;
					}
                    
				}
				// execute command
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
				{ 
					 dup2(table->outfile, STDOUT_FILENO);
					//close(table->outfile);
				}
				if (table->infile != -2 && table->infile != -1)
				{
                     dup2(table->infile, STDIN_FILENO);
                   
					//close(table->infile);
				}
				if (table->heredoc[0] != NULL && ft_strcmp(table->in_or_here, "heredoc") == 0)
				{
					if(dup2(pixa[mm][0], STDIN_FILENO) == -1)
                    {
                        perror("dup2 error");
                        exit(-1);
                    }
                   
                    int la = 0;
                    while (la < aka)
                    {
                        close(pixa[la][0]);
                        close(pixa[la][1]);
                        la++;
                    } 
                    mm++;
					// close(pipa[0]);
					// close(pipa[1]);
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
				{
					ft_cd(envp1, table->args[1]);

					exit(0);
				}
				else if (ft_strncmp(table->args[0], "env", 4) == 0)
				{
					printf("env\n");
					envv(*envp1);

					exit(0);
				}
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
					{
						export(envp1, NULL);

						exit(0);
					}
					else
					{
						while (table->args[i])
						{
							export(envp1, table->args[i]);
							i++;
						}

						//printf("-------------------\n");
						//export(&envp1, NULL);
					}

					exit(0);
				}
				else if (ft_strncmp(table->args[0], "echo", 5) == 0)
				{
					if (ft_test(table->args) == 1)
						echo(table->args[1], ft_collect(table->args, 2));
					else
					{
						//printf("%s------------>\n",ft_collect(table->args,1));
						echo(NULL, ft_collect(table->args, 1));
					}

					exit(0);
				}
				else if (ft_strncmp(table->args[0], "pwd", 4) == 0)
				{
					ft_pwd();

					exit(0);
				}
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
					{
						perror("execve error");
						exit(126);
					}
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
						{
							perror("execve error");
							exit(126);
						}
					}
					pipex->i++;
				}
				if (table->args)
				{
					if (ft_strserarch(table->args[0], '/') == 1)
					{
						ft_error1("minishell: No such file or directory: ",
								table->args[0]);
					}
					else
						ft_error1("minishell: command not found: ",
								table->args[0]);
                }
			}
			else
			{
                if (table->heredoc[0] != NULL)
				{
					// close(pipa[0]);
					// close(pipa[1]);
                    //free(pipa);
                    close(pixa[mm][0]);
                    close(pixa[mm][1]);
                    mm++;
				}
				if (i == 0)
				{
					close(pipes[i][1]);
				}
				else if (i == num_pipes)
				{
					close(pipes[i - 1][0]);
					close(pipes[i - 1][1]);
				}
				else
				{
					close(pipes[i][1]);
					close(pipes[i - 1][0]);
					close(pipes[i - 1][1]);
				}
				close(table->outfile);
				close(table->infile);
                //close(pipa[0]);
				table = table->next;

				i++;
			}
		}

        int xx = 0;
       while( xx < aka)
       {
           close(pixa[xx][0]);
           close(pixa[xx][1]);
           xx++;
       }
		if (r)
		{
			int status;
			waitpid(g_globale.pid[num_pipes], &status, 0);
			int j = 0;
			while (j < num_pipes)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			//close(table->outfile);
			//close(table->infile);
            //close(pipa[0]);

			j = 0;
			while (j < num_pipes)
				waitpid(g_globale.pid[j++], NULL, 0);
			if (WIFSIGNALED(status))
			{
				g_globale.exit_child = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
			{
				g_globale.exit_child = WEXITSTATUS(status);
				//fd_putnbr(g_globale.exit_child);
			}
            
		}
		free(g_globale.pid);
        
	}
}
