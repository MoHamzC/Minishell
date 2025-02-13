#include "parsing.h"

int whichbuiltin(char *s)
{
    if(ft_strcmp(s, "echo") == 0)
        return(ECHO); 
    else if(ft_strcmp(s, "cd") == 0)
        return(CD); 
    else if(ft_strcmp(s, "pwd") == 0)
        return(PWD); 
    else if(ft_strcmp(s, "export") == 0)
        return(EXPORT); 
    else if(ft_strcmp(s, "unset") == 0)
        return(UNSET); 
    else if(ft_strcmp(s, "env") == 0)
        return(ENV); 
    else if(ft_strcmp(s, "exit") == 0)
        return(EXIT); 
    else    
        return(NOT_BUILTIN); 
}

int ft_strlen_tab(char **tab)
{
	int i; 
	i = 0; 
	while(tab && tab[i])
		i++; 
	return(i); 
}
