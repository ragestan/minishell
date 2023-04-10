#include "minishell.h"



int	ft_strncmp1(const char *s1, const char *s2)
{
	size_t	i;
    //int j = 0;

	i = 0;
	while ( s1[i] != '=' && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		}
		i++;
	}
    i = 0;
    while(s1[i] != '\0' && s1[i] != '=')
    i++;
     if(i == ft_strlen3(s2))
	    return (0);
    else
        return 1;

}
//------------------------------------------
void deleteNode(envp** head, char* str) 
{
    
    // If the list is empty
    if (*head == NULL) {
        return;
    }
    // If the node to be deleted is the head node
    //if (ft_strcmpe)
    if (ft_strncmp1((*head)->str, str) == 0) {
        
        envp* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    // Search for the node to be deleted
    envp* current = *head;
    while (current->next != NULL && ft_strncmp1(current->next->str, str) != 0) {
        current = current->next;
    }
    // If the node is not found
    if (current->next == NULL) {
        return;
    }
    // Delete the node
    free(current->next->str);
    envp* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

int validarg(char *str)
{
    //  int i = 0;
    // if(ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0)
    //     return 1;
    //     i++;
    //     while(str[i])
    //     {
    //         if(str[i] == '=')
    //         return 1;
    //         i++;
    //     }
    //     return 0;
    int	i;

	i = 0;
	if ((ft_isdigit(str[i]) == 1 || ft_isalpha(str[i]) == 0 ) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (1);
	}
	return (0);
}
int  unset(envp **env1,char *str)
{
    if(validarg(str) == 1)
    {
        printf("unset: `%s': not a valid identifier\n",str);
        return 1;
    }
    deleteNode(env1,str);
    //export(env1,NULL);
    return 0;
}

// int main(int argc,char **argv)
// {
//    int i = 1;
//    envp *env1;
//    while(argv[i] != 0)
//    {
//     deleteNode(&env1,argv[i]);
//     i++;
//    }
    
// }