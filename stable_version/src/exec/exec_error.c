#include "minishell.h"

void    handle_cmd_not_found(char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(": command not found", 2);
}

void    handle_permission_denied(char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(": Permission denied", 2);
}

void    exit_with_error(char *msg, int code)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putendl_fd(msg, 2);
    exit(code);
}

void    print_exec_error(char *cmd, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
    {
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(error, 2);
}

int    print_file_error(char *file, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (file)
    {
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putendl_fd(error, 2);
    return (1);
}