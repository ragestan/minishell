/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:46:46 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/22 23:16:42 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void printlinkdlist(t_Command_Table3 *str)
{
    t_Command_Table3 *st;
    st = str;
    int i = 0;
    while(st)
    {
        while(st->heredoc[i])
        {
            printf("%s\n",st->heredoc[i]);
            i++;
        }
        i = 0;
        printf("%d\n",st->infile);
        printf("%d\n",st->outfile);
        printf("%s\n",st->in_or_here);
          while(st->args[i])
        {
            printf("%s\n",st->args[i]);
            i++;
        }
        i = 0;
        st = st->next;
        
    }  
    //print the last lint in the original env
}

void	pathfinder(t_pipex *pipex, envp *envp1)
{
    envp *tmp;
    tmp = envp1;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PATH=", 5) == 0)
		{
			pipex->save = tmp->str  + 5;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp->str == NULL)
	{
		pipex->paths = NULL;
		return ;
	}
	pipex->paths = ft_split(pipex->save, ':');
}
void	ft_error1(char *str, char *st)
{
	write(2, str, ft_strlen3(str));
	if (st)
		write(2, st, ft_strlen3(st));
	write(2, "\n", 1);
	exit(127);
}
void shell_with_pipes(t_Command_Table3 *table,char **env,t_pipex *pipex,envp *envp1) 
{
    (void) env;
    (void) pipex;
    //num args is the number of arguments in the command you cam get it from the table struct
    //num pipes is the number of pipes in the command you can get it from the table struct
    pathfinder(pipex,envp1);
    //printlinkdlist(table);
    int num_pipes = count(table);
    
    num_pipes--;
     int pipes[num_pipes][2];
     pid_t pid[count(table)];
     int i = 0;
     int j = 0;
    
    // create pipes
    i = 0;
    while (i < num_pipes) 
    {
        if (pipe(pipes[i]) < 0) 
        {
            perror("pipe error");
            exit(-1);
        }
        i++;
    }
    i = 0;
    if (num_pipes == 0)
    {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror("fork error");
            exit(-1);
        }
        else if(pid[i] == 0)
        {
            //write in a file
            if(table->outfile != -2 && table->outfile != -1)
            {
                dup2(table->outfile, STDOUT_FILENO);
            }
            if(table->infile != -2 && table->infile != -1)
            {
                dup2(table->infile, STDIN_FILENO);
            }
            if ((table->args[0][0] == '.' || table->args[0][0] == '/') && access(table->args[0], F_OK) == 0)
            {
                if(execve(table->args[0], table->args, env) == -1)
                {
                    write(2, "minishell: ", 11);
                    perror(table->args[0]);
                    exit(-1);
                }
            }
            pipex->i = 0;
            while(pipex->paths && pipex->paths[pipex->i])
            {
                pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], "/");
                pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], table->args[0]);
                if(access(pipex->paths[pipex->i], F_OK) == 0)
                {
                    
                    if(execve(pipex->paths[pipex->i], table->args, env) == -1)
                    {
                        perror("execve error");
                        exit(-1);
                    }
                }
                pipex->i++;
            }
            ft_error1("minishell: command not found: ", table->args[0]);
        }
        else
        {
           waitpid(pid[i], NULL, 0);
        }
        
    }
    //multiple pipes
    else
    {
    int k = count(table);
    // printf("k         = %d\n",k);
    // printf("num_pipes = %d\n",num_pipes);
    // // create child processes
    i = 0;
    while (i < k) 
    {
        pid[i] = fork();
        if (pid[i] < 0) 
        {
            perror("fork error");
            exit(-1);
        } 
        // else if (pid[i] == 0) {
        //     // child process
        //     if (i == 0) {
        //         // first child process
        //         // redirect stdout to the first pipe
        //         dup2(pipes[0][1], STDOUT_FILENO);
        //         // close all pipes except the first one
        //         j = 0;
        //         while (j < num_pipes) {
        //             if (j != 0) {
        //                 close(pipes[j][0]);
        //                 close(pipes[j][1]);
        //             }
        //             j++;
        //         }
                
        //     } else if (i == num_pipes) {
        //         // last child process
        //         // redirect stdin to the last pipe
        //         dup2(pipes[num_pipes-1][0], STDIN_FILENO);
        //         // close all pipes except the last one
        //         j = 0;
        //         while (j < num_pipes) {
        //             if (j != num_pipes-1) {
        //                 close(pipes[j][0]);
        //                 close(pipes[j][1]);
        //             }
        //             j++;
        //         }
        //     } else {
        //         // intermediate child processes
        //         // redirect stdin to the previous pipe
        //         dup2(pipes[i-1][0], STDIN_FILENO);
        //         // redirect stdout to the next pipe
        //         dup2(pipes[i][1], STDOUT_FILENO);
        //         // close all pipes except the previous and next ones
        //         j = 0;
        //         while (j < num_pipes) {
        //             if (j != i-1 && j != i) {
        //                 close(pipes[j][0]);
        //                 close(pipes[j][1]);
        //             }
        //             j++;
        //         }
        //     }
        else if (pid[i] == 0) 
        {
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
                close(pipes[i - 1][1]);
                close(pipes[i - 1][0]);
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
            else 
            {
                // intermediate child processes
                // redirect stdin to the previous pipe
                dup2(pipes[i-1][0], STDIN_FILENO);
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
            if(table->outfile != -2 && table->outfile != -1)
            {
                dup2(table->outfile, STDOUT_FILENO);
            }
            if(table->infile != -2 && table->infile != -1)
            {
                dup2(table->infile, STDIN_FILENO);
            }
            if ((table->args[0][0] == '.' || table->args[0][0] == '/') && access(table->args[0], F_OK) == 0)
            {
                if(execve(table->args[0], table->args, env) == -1)
                {
                    perror("execve error");
                    exit(-1);
                }
            }
            pipex->i = 0;
            while(pipex->paths && pipex->paths[pipex->i])
            {
                pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], "/");
                pipex->paths[pipex->i] = ft_strjoin2(pipex->paths[pipex->i], table->args[0]);
                // ft_putstr_fd(pipex->paths[pipex->i], 2);
                // ft_putstr_fd("\n", 2);
                if( access(pipex->paths[pipex->i], F_OK) == 0)
                {
                    if(execve(pipex->paths[pipex->i], table->args, env) == -1)
                    {
                        perror("execve error");
                        exit(-1);
                    }
                }
                pipex->i++;
            }
            ft_error1("minishell: command not found: ", table->args[0]);
            
            //exit(0);
        }
        else 
        {
            if (i == 0)
            {
                // int l = 0;
                // while ( l < num_pipes)
                // {
                //     /* code */
                //     close(pipes[l][0]);
                //     close(pipes[l][1]);
                //     l++;
                // }
                
                
                close(pipes[i][1]);
                
            }
            else if (i == num_pipes)
            {
                write(2, "last child process\n", 19);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
                
            }
            else
            {
                close(pipes[i - 1][1]);
                close(pipes[i - 1][0]);
                close(pipes[i][1]);
            }
             int status;
        //     // parent process
        //     // close all pipes
            // ft_putstr_fd("parent process id = ", 2);
            // ft_putnbr_fd(num_pipes, 2);
            // ft_putstr_fd("\n", 2);
            waitpid(pid[num_pipes], &status, 0);
            
            j = 0;
           while (j < num_pipes) 
           {
            waitpid(pid[j], NULL, 0);
            j++;
           }
           table = table->next;
            i++;
        }
        
    }
}  
    // parent process
    // close all pipes
    // i = 0;
    // while (i < num_pipes) {
    //     close(pipes[i][0]);
    //     close(pipes[i][1]);
    //     i++;
    // }
    // // wait for child processes to terminate
    // i = 0;
    //    while (i <= num_pipes) {
    //     waitpid(pid[i], NULL, 0);
    //     i++;
    // }
    // }
}