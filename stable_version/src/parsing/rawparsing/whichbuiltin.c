#include "../../../include/minishell.h"

int whichbuiltin(char *s)
{
    if(ft_strncmp(s, "echo", ft_strlen(s)) == 0)
        return(ECHO); 
    else if(ft_strncmp(s, "cd", ft_strlen(s)) == 0)
        return(CD); 
    else if(ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
        return(PWD); 
    else if(ft_strncmp(s, "export", ft_strlen(s)) == 0)
        return(EXPORT); 
    else if(ft_strncmp(s, "unset", ft_strlen(s)) == 0)
        return(UNSET); 
    else if(ft_strncmp(s, "env", ft_strlen(s)) == 0)
        return(ENV); 
    else if(ft_strncmp(s, "exit", ft_strlen(s)) == 0)
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

int	is_redir_token(t_cmd_type type)
{
	return (type == REDIRIN || type == REDIROUT
		|| type == APPEND || type == HERE_DOC);
}