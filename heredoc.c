/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:24:40 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/08 00:46:06 by zbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
// void heredoc(char* delimiter) {
//   char* line;
//   char* input = NULL;
//   int size = 0;
//   int capacity = 0;

//   printf("Enter input, finish with delimiter \"%s\":\n", delimiter);

//   while ((line = readline("> "))) {
//     // Add input to history
//     add_history(line);

//     if (strcmp(line, delimiter) == 0) {
//       break;
//     }

//     int len = strlen(line);

//     // Make sure there's enough space in the buffer
//     if (size + len + 1 > capacity) {
//       // Allocate more memory
//       capacity = size + len + 1;
//       char* new_input = malloc(capacity);
//       if (new_input == NULL) {
//         fprintf(stderr, "Error: failed to allocate memory\n");
//         exit(EXIT_FAILURE);
//       }
//       if (input != NULL) {
//         strcpy(new_input, input);
//         free(input);
//       }
//       input = new_input;
//     }

//     // Copy input into buffer
//     strcpy(input + size, line);
//     size += len;
//     input[size++] = '\n';

//     // Free readline memory
//     free(line);
//   }
//     printf("Input: ->>>>>>>>>\n%s", input);
//     printf("Input: ->>>>>>>>>\n");
//   // Create pipe
//   int pipefd[2];
//   if (pipe(pipefd) == -1) {
//     perror("pipe");
//     exit(EXIT_FAILURE);
//   }

//   // Fork process
//   pid_t pid = fork();
//   if (pid == -1) {
//     perror("fork");
//     exit(EXIT_FAILURE);
//   }

//   if (pid == 0) {
//     // Child process: write input to pipe
//     close(pipefd[0]);
//     write(pipefd[1], input, size);
//     close(pipefd[1]);
//     exit(EXIT_SUCCESS);
//   } else {
//     // Parent process: read input from pipe
//     close(pipefd[1]);

//     // Read from pipe
//     char buffer[1024];
//     int nbytes;
//     while ((nbytes = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
//       write(STDOUT_FILENO, buffer, nbytes);
//     }

//     // Wait for child process to finish
//     waitpid(pid, NULL, 0);

//     close(pipefd[0]);

//     // Free input memory
//     free(input);
//   }
// }
// int heredoc(char *delimiter)
// {
//     char* string = NULL;
//     char* line = NULL;

//     while ((line = readline("> ")))
//     {
//         if (strcmp(line, delimiter) == 0)
//         {
//             break;
//         }
//         string = ft_strjoin3(string, line);
//         string = ft_strjoin3(string, "\n");
//         free(line);
//     }
//     //create pipe
//     int pipefd[2];
//     if (pipe(pipefd) == -1)
//     {
//         perror("pipe");
//         return 1;
//     }
//     //fork process
//     int pid = fork();
//     if (pid == -1)
//     {
//         perror("fork");
//         return 1;
//     }
//     if (pid == 0)
//     {
//         //child process: write input to pipe
//         close(pipefd[0]);
//         write(pipefd[1], string, strlen(string));
//         close(pipefd[1]);
//         exit(EXIT_SUCCESS);
//     }
//     else
//     {
//         //parent process: read input from pipe
//         close(pipefd[1]);
//         //read from pipe with execve
//         dup2(pipefd[0], 0);
//         close(pipefd[0]);
//         //char *cat[] = {"/bin/cat", NULL};
//         char *wc[] = {"/usr/bin/wc","-l", NULL};
//         execve("/usr/bin/wc", wc, NULL);
//         //wait for child process to finish
//         waitpid(pid, NULL, 0);
//         close(pipefd[0]);
//         //free input memory
//         free(string);
//     }
//     return 0;
// }
char *heredocstring(char *delimiter)
{
    char* string = NULL;
    char* line = NULL;

    line = readline("> ");
    while (line)
    {
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
		//printf("ayaya\n");
        line = ft_en(line,g_globale.env1 ,0);
        string = ft_strjoin3(string, line);
        string = ft_strjoin3(string, "\n");
        free(line);
        line = readline("> ");
    }
    
    return string;
}
char *heredocwhile(char **heredoc)
{
    int i = 0;
    char *string = NULL;
    while (heredoc[i])
    {   
        if (string)
            free(string);
        string = heredocstring(heredoc[i]);
        //free(heredoc[i]);
        i++;
        
    }
    
    return string;
}
// int main()
// {
//     heredoc("EOF");
// }