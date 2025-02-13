#include "../minishell.h"

t_env *ft_envlst_new(char *key, char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = strdup(key);
    if (!new->key)
    {
        free(new);
        return (NULL);
    }
    if (value)
    {
        new->value = strdup(value);
        if (!new->value)
        {
            free(new->key);
            free(new);
            return (NULL);
        }
    }
    else
        new->value = NULL;
    new->next = NULL;
    return (new);
}

void free_env(t_env *env)
{
    t_env *temp;

    while (env)
    {
        temp = env->next;
        if (env->key)
            free(env->key);
        if (env->value)
            free(env->value);
        free(env);
        env = temp;
    }
}

static t_redir *create_redir(char *file, int type, bool append)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->file = strdup(file);
    redir->type = type;
    redir->append = append;
    return (redir);
}

static t_command *create_simple_command(char **args, t_redir **redirs)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = args;
    cmd->redir = redirs;
    cmd->builtin_value = is_builtin(args[0]);
    cmd->next = NULL;
    return (cmd);
}

static t_env *create_simple_env(void)
{
    t_env *env;
    t_env *path;
    t_env *home;

    // Create basic PATH
    path = ft_envlst_new("PATH", "/usr/local/bin:/usr/bin:/bin");
    if (!path)
        return (NULL);
    
    // Create HOME
    home = ft_envlst_new("HOME", "/Users/user");
    if (!home)
    {
        free_env(path);
        return (NULL);
    }

    // Link them together
    env = path;
    env->next = home;
    
    return (env);
}

int main(void)
{
    t_shell shell;
    t_command *cmd1;
    t_command *cmd2;
    char **args1;
    char **args2;
    t_redir **redirs1;
    t_redir **redirs2;

    // Initialize shell structure
    shell.env = create_simple_env();
    if (!shell.env)
        return (1);

    // Create command "ls -l > output.txt"
    args1 = malloc(sizeof(char *) * 3);
    args1[0] = strdup("ls");
    args1[1] = strdup("-l");
    args1[2] = NULL;

    redirs2 = malloc(sizeof(t_redir *) * 2);
    redirs2[0] = create_redir("output.txt", REDIROUT, false);
    redirs2[1] = NULL;

    redirs1 = malloc(sizeof(t_redir *) * 1);
    redirs1[0] = NULL;

    cmd1 = create_simple_command(args1, redirs1);

    // Create command "grep test"
    args2 = malloc(sizeof(char *) * 3);
    args2[0] = strdup("wc");
    args2[1] = strdup("-l");
    args2[2] = NULL;


    cmd2 = create_simple_command(args2, redirs2);

    // Link commands for pipe
    cmd1->next = cmd2;
    shell.cmds = cmd1;
    // Execute commands
    executor(&shell);

    // Clean up (you would need to implement proper cleanup functions)
    // This is just basic cleanup to avoid leaks
    // TODO: Implement proper cleanup functions

    free(args1[0]);
    free(args1[1]);
    free(redirs1[0]);
    free(redirs1);
    free(cmd1);
    free(args2[0]);
    free(args2[1]);
    free(args2);
    free(redirs2);
    free(cmd2);
   	
    free_env(shell.env);

    return (0);
}