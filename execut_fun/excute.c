/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:46:46 by zbentale          #+#    #+#             */
/*   Updated: 2023/04/08 18:01:11 by zbentale         ###   ########.fr       */
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
int	ft_test(char **str)
{
   
	if (str[0][0] == 'e' && str[0][1] == 'c' && str[0][2] == 'h' && str[0][3] == 'o' && str[0][4] == '\0')
	{
		if (str[1] && str[1][0] && str[1][0] == '-')
		{
			return(1);
		}
	}
	return (0);
}


int 	ft_collect_help(char **str,int i)
{ 
	
	int j;
	int k;

	j = 0;
	k = 0;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			j++;
			k++;
		}
		i++;
		k++;
	}
	return (k);
}

//i = 1 if no option else i = 2
char	*ft_collect(char **str,int i)
{
	int j;
	int k;
	char *str2;

	j = 0;
	k = 0;
	str2 = malloc(sizeof(char) * ft_collect_help(str,i) + 1);
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			str2[k] = str[i][j];
			j++;
			k++;
		}
		if (str[i + 1] != NULL)
		{
			str2[k] = ' ';
			k++;
		}
		i++;
	}
	str2[k] = '\0';
	return (str2);
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
	//maybe it will be a problem if PATH is in the last node
	if (tmp == NULL)
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
	g_globale.exit_child = 127;
	exit(127);
}
