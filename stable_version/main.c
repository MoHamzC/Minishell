#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static t_env	*create_simple_env(void)
{
	t_env	*env;
	t_env	*path;
	t_env	*home;

	/* Crée la variable PATH */
	path = ft_envlst_new("PATH", "/usr/local/bin:/usr/bin:/bin");
	if (!path)
		return (NULL);
	/* Crée la variable HOME */
	home = ft_envlst_new("HOME", "/Users/user");
	if (!home)
	{
		free_env(path);
		return (NULL);
	}
	/* Lie PATH et HOME */
	env = path;
	env->next = home;
	return (env);
}

int	main(void)
{
	t_shell	shell;
	t_token	**tokens;
	char	*line;

	shell.env = create_simple_env();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		/* Tokenisation et traitement */
		tokens = take_ur_token_and_leave_me_alone(shell.env, line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		/* Parsing des tokens en commandes */
		shell.cmds = parse_tokens(tokens);
		/* Exécution des commandes */
		executor(&shell);
		/* Libération des ressources */
		free_tokens(tokens);
		free(line);
		/* Si besoin, libérez aussi la liste des commandes :
		   free_commands(shell.cmds); */
	}
	free_env(shell.env);
	return (0);
}
