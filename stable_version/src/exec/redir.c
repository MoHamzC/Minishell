#include "minishell.h"


void    reset_redirections(t_exec_data *exec)
{
    if (exec->stdin_backup != -1)
    {
        dup2(exec->stdin_backup, STDIN_FILENO);
        close(exec->stdin_backup);
        exec->stdin_backup = -1;
    }
    if (exec->stdout_backup != -1)
    {
        dup2(exec->stdout_backup, STDOUT_FILENO);
        close(exec->stdout_backup);
        exec->stdout_backup = -1;
    }
}

static char *get_heredoc_filename(void)
{
    static int  count = 0;
    char        *num;
    char        *filename;

    num = ft_itoa(count++);
    filename = ft_strjoin("/tmp/.heredoc_", num);
    free(num);
    return (filename);
}

int    handle_heredoc(char *delimiter)
{
    char    *filename;
    char    *line;
    int     fd;

    filename = get_heredoc_filename();
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        free(filename);
        return (print_file_error("heredoc", strerror(errno)));
    }
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
            line[ft_strlen(delimiter)] == '\n')
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        free(line);
    }
    close(fd);
    fd = open(filename, O_RDONLY);
    unlink(filename);
    free(filename);
    if (fd < 0)
        return (print_file_error("heredoc", strerror(errno)));
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int    handle_input_redir(char *file)
{
    int    fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (print_file_error(file, strerror(errno)));
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        return (print_file_error(file, strerror(errno)));
    }
    close(fd);
    return (0);
}

int    handle_output_redir(char *file, int append)
{
    int    fd;
    int    flags;

    flags = O_WRONLY | O_CREAT;
    flags |= (append ? O_APPEND : O_TRUNC);
    fd = open(file, flags, 0644);
    if (fd < 0)
        return (print_file_error(file, strerror(errno)));
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        close(fd);
        return (print_file_error(file, strerror(errno)));
    }
    close(fd);
    return (0);
}
int    handle_redirections(t_command *cmd)
{
    int     i;
    t_redir **redirs;

    if (!cmd->redir)
        return (0);
    redirs = cmd->redir;
    i = 0;
    while (redirs[i])
    {
        if (redirs[i]->type == REDIRIN)
        {
            if (handle_input_redir(redirs[i]->file) != 0)
                return (1);
        }
        else if (redirs[i]->type == REDIROUT || redirs[i]->type == APPEND)
        {
            if (handle_output_redir(redirs[i]->file, 
                redirs[i]->type == APPEND) != 0)
                return (1);
        }
        else if (redirs[i]->type == HERE_DOC)
        {
            if (handle_heredoc(redirs[i]->file) != 0)
                return (1);
        }
        i++;
    }
    return (0);
}

