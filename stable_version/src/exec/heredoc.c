#include "minishell.h"

static int g_heredoc_interrupted = 0;

static void heredoc_sigint_handler(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    //close(0); si on close on sort de ./minishell
}

static char *get_heredoc_filename(void)
{
    static int count = 0;
    char *num;
    char *filename;

    num = ft_itoa(count++);
    if (!num)
        return (NULL);
    filename = ft_strjoin("/tmp/.heredoc_", num);
    free(num);
    return (filename);
}

static int create_heredoc_file(char *delimiter, char *filename)
{
    int fd;
    char *line;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);

    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line || g_heredoc_interrupted)
        {
            if (line)
                free(line);
            close(fd);
            return (g_heredoc_interrupted ? -1 : 0);
        }
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
    return (0);
}

char **process_heredocs(t_command *cmds)
{
    t_command *current;
    int i;
    int heredoc_count = 0;
    char **heredoc_files;
    struct sigaction sa_old, sa_new;

    // compte nb total de heredoc
    current = cmds;
    while (current)
    {
        i = 0;
        while (current->redir && current->redir[i])
        {
            if (current->redir[i]->type == HERE_DOC)
                heredoc_count++;
            i++;
        }
        current = current->next;
    }

    if (heredoc_count == 0)
        return (NULL);

    // memoire pour heredoc filename
    heredoc_files = malloc(sizeof(char *) * (heredoc_count + 1));
    if (!heredoc_files)
        return (NULL);

    //signal heredoc
    sa_new.sa_handler = heredoc_sigint_handler;
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sigaction(SIGINT, &sa_new, &sa_old);

    // Process heredoc
    current = cmds;
    heredoc_count = 0;
    g_heredoc_interrupted = 0;

    while (current && !g_heredoc_interrupted)
    {
        i = 0;
        while (current->redir && current->redir[i] && !g_heredoc_interrupted)
        {
            if (current->redir[i]->type == HERE_DOC)
            {
                heredoc_files[heredoc_count] = get_heredoc_filename();
                if (!heredoc_files[heredoc_count] ||
                    create_heredoc_file(current->redir[i]->file, 
                                      heredoc_files[heredoc_count]) < 0)
                {
                    //error
                    while (heredoc_count > 0)
                    {
                        unlink(heredoc_files[heredoc_count - 1]);
                        free(heredoc_files[--heredoc_count]);
                    }
                    free(heredoc_files);
                    sigaction(SIGINT, &sa_old, NULL);
                    return (NULL);
                }
                current->redir[i]->file = ft_strdup(heredoc_files[heredoc_count]);
                heredoc_count++;
            }
            i++;
        }
        current = current->next;
    }

    // Restore signal original 
    sigaction(SIGINT, &sa_old, NULL);

    if (g_heredoc_interrupted)
    {
        while (heredoc_count > 0)
        {
            unlink(heredoc_files[heredoc_count - 1]);
            free(heredoc_files[--heredoc_count]);
        }
        free(heredoc_files);
        return (NULL);
    }

    heredoc_files[heredoc_count] = NULL;
    return (heredoc_files);
}

void cleanup_heredoc_files(char **heredoc_files)
{
    int i;

    if (!heredoc_files)
        return;

    i = 0;
    while (heredoc_files[i])
    {
        unlink(heredoc_files[i]);
        free(heredoc_files[i]);
        i++;
    }
    free(heredoc_files);
}