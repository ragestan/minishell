#include "minishell.h"

int	ft_test(char **str)
{
	if (str[0][0] == 'e' && str[0][1] == 'c' && str[0][2] == 'h' && str[0][3] == 'o' && str[0][4] == '\0')
	{
		if (str[1][0] == '-')
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
			str[k] = str[i][j];
			j++;
			k++;
		}
		str[k] = ' ';
		i++;
		k++;
	}
	str2[k] = '\0';
	return (str2);
}