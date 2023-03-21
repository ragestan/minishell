/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:46:46 by zbentale          #+#    #+#             */
/*   Updated: 2023/03/21 17:09:52 by zbentale         ###   ########.fr       */
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
void shell_with_pipes(t_Command_Table3 *table,char **env,t_pipex *pipex) 
{
    (void) env;
    (void) pipex;
    //num args is the number of arguments in the command you cam get it from the table struct
    //num pipes is the number of pipes in the command you can get it from the table struct
    printlinkdlist(table);
    // int pipes[MAX_PIPES][2];
    // pid_t pid[MAX_PIPES+1];
    // int i = 0, j = 0;
    
    // // create pipes
    // i = 0;
    // while (i < num_pipes) {
    //     if (pipe(pipes[i]) < 0) {
    //         perror("pipe error");
    //         exit(-1);
    //     }
    //     i++;
    // }
    
    // // create child processes
    // i = 0;
    // while (i <= num_pipes) {
    //     pid[i] = fork();
    //     if (pid[i] < 0) {
    //         perror("fork error");
    //         exit(-1);
    //     } else if (pid[i] == 0) {
    //         // child process
    //         if (i == 0) {
    //             // first child process
    //             // redirect stdout to the first pipe
    //             dup2(pipes[0][1], STDOUT_FILENO);
    //             // close all pipes except the first one
    //             j = 0;
    //             while (j < num_pipes) {
    //                 if (j != 0) {
    //                     close(pipes[j][0]);
    //                     close(pipes[j][1]);
    //                 }
    //                 j++;
    //             }
                
    //         } else if (i == num_pipes) {
    //             // last child process
    //             // redirect stdin to the last pipe
    //             dup2(pipes[num_pipes-1][0], STDIN_FILENO);
    //             // close all pipes except the last one
    //             j = 0;
    //             while (j < num_pipes) {
    //                 if (j != num_pipes-1) {
    //                     close(pipes[j][0]);
    //                     close(pipes[j][1]);
    //                 }
    //                 j++;
    //             }
    //         } else {
    //             // intermediate child processes
    //             // redirect stdin to the previous pipe
    //             dup2(pipes[i-1][0], STDIN_FILENO);
    //             // redirect stdout to the next pipe
    //             dup2(pipes[i][1], STDOUT_FILENO);
    //             // close all pipes except the previous and next ones
    //             j = 0;
    //             while (j < num_pipes) {
    //                 if (j != i-1 && j != i) {
    //                     close(pipes[j][0]);
    //                     close(pipes[j][1]);
    //                 }
    //                 j++;
    //             }
    //         }
    //         // execute command
    //         // char *cmd_args[MAX_ARGS];
    //         // j = 0;
    //         // while (j < MAX_ARGS) {
    //         //     cmd_args[j] = NULL;
    //         //     j++;
    //         // }
    //         // j = 0;
    //         // while (j < 2) {
    //         //     cmd_args[j] = args[i*2+j];
    //         //     j++;
    //         // }
    //         pipex->i = 0;
    //         pipex->cmd = ft_split(argv[3], ' ');
	//         if (access(pipex->cmd[0], F_OK) == 0)
	//         {
	// 	        if (execve(pipex->cmd[0], pipex->cmd, envp) == -1)
	// 		    ft_perror("ERROR");
	//         }
	//         while (pipex->paths && pipex->paths[pipex->i])
	//         {
	// 	        pipex->paths[pipex->i] = ft_strjoin(pipex->paths[pipex->i], "/");
	// 	        pipex->paths[pipex->i] = ft_strjoin(pipex->paths[pipex->i], pipex->cmd[0]);

	// 	    if (access(pipex->paths[pipex->i], F_OK) == 0)
	// 	    {
    //             printf("pipex->paths[pipex->i] = %s\n", pipex->paths[pipex->i]);
    //             printf("pipex->cmd[0] = %s\n", pipex->cmd[0]);
	// 		    if (execve(pipex->paths[pipex->i], pipex->cmd, envp) == -1)
	// 			ft_perror("ERROR");
	// 	    }
	// 	    pipex->i++;
	//         }
    //         // if (execve(cmd_args[0], cmd_args, envp) < 0) {
    //         //     perror("execve error");
    //         //     exit(-1);
    //         // }
    //         exit(0);
    //     }
    //     i++;
    // }
    
    // // parent process
    // // close all pipes
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
}