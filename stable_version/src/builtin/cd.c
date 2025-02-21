#include "minishell.h"

void ft_update_env(t_env *envp, const char *key, const char *new_value)
{
	while(envp->next)
	{
		if(ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
		{
			free(envp->value);
			envp->value = ft_strdup(new_value);
			return;
		}
		envp = envp->next;
	}
}
int ft_cd(t_shell *shell)
{
	char *path;
	char cwd[1024];
	char *home;
	int size = 0; // sorry la norm

	while (shell->cmds->args[size]) // pour gerer "cd .. hi"
		size++;
	if (size > 2)
	{
		ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(shell->cmds->args[0], 2);
    	ft_putendl_fd(": too many arguments", 2);
		return(1);
	}

	path = shell->cmds->args[1];
	home = NULL;
	if(!path)
	{
		home = builtin_get_envv(shell->env,"HOME");
		if(chdir(home) == -1)
		{
			write(2, "HOME not set\n", 14);
			return(-1) ;
		}
		chdir(home);
		path = home;
		return 0;
	}
	getcwd(cwd, sizeof(cwd));
	if(chdir(path) == -1)
		return(perror("cd"),-1);
	if (getcwd(cwd, sizeof(cwd)))
		ft_update_env(shell->env, "PWD", cwd);
	if (getenv("PWD"))
		ft_update_env(shell->env, "OLDPWD", getenv("PWD"));
	return(0);
}

// gerer cd tout cours
// gerer cd .
