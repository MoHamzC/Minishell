/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:58 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/13 17:48:24 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_builtin
{
	NOT_BUILTIN = -1,
	ECHO = 0,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,	
}				t_builtin;

typedef enum token_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HERE_DOC,	
	PIPE,
}	t_cmd_type;

typedef enum word_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_word_type;

typedef struct s_token
{
	char		*value;
	t_cmd_type	type;
	t_word_type	quote;
}	t_token;

typedef struct s_redir
{
	char	*file;
	int		type;
	bool	append;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_command
{
	t_redir				**redir;
	char				**args;
	int					builtin_value;
	struct s_command	*next;
}				t_command;

typedef struct s_shell
{
	t_command	*cmds;
	t_env		*env;
	int         exit_status;
}	t_shell;

typedef struct s_pipe_ends
{
    int     read;
    int     write;
}               t_pipe_ends;

typedef struct s_exec_data
{
    char    **env_arr;
    int     last_status;
    int     stdin_backup;
    int     stdout_backup;
	int		pid;
}               t_exec_data;

int		ft_isspace(char c);
t_token	**tokenize(char *line);
int		post_tokenize(t_token **tokens, t_env *env);
void	free_tokens(t_token **tokens);

t_env	*ft_envlst_new(char *key, char *value);
void	ft_envlst_add_back(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
void	free_env(t_env *env);
t_token	**pre_process_redirections(t_token **tokens);
t_token	**take_ur_token_and_leave_me_alone(t_env *env, char *line);


//builtins

void ft_env(t_env *envp);

/* Execution prototypes */
int         executor(t_shell *shell);
int         exec_single_cmd(t_shell *shell, t_command *cmd, t_exec_data *exec);
void        init_exec_data(t_exec_data *exec, t_shell *shell);
void    	wait_all_children(t_shell *shell, t_exec_data *exec);
int         is_builtin(char *cmd);

/* Path handling */
char        *find_command_path(char *cmd, char **env_paths);
char        **get_path_dirs(char **env);
int         check_command_access(char *cmd_path);

/* Redirections */
int         handle_redirections(t_command *cmd);
void        reset_redirections(t_exec_data *exec);
void        backup_std_fds(t_exec_data *exec);
void        restore_std_fds(t_exec_data *exec);

/* Environment */
char        **env_list_to_array(t_env *env);
void        free_env_array(char **env_arr);
char        *get_env_value(t_env *env, char *key);

/* Error handling */
void        print_exec_error(char *cmd, char *error);
void        handle_cmd_not_found(char *cmd);
int         print_file_error(char *file, char *error);
void        exit_with_error(char *msg, int code);

/* Pipe handling */
int         setup_pipes(t_pipe_ends *pipes);
void        close_pipe_ends(t_pipe_ends *pipes);
#endif
