/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochamsa <mochamsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:57:58 by mochamsa          #+#    #+#             */
/*   Updated: 2025/02/27 04:22:44 by mochamsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig_received;

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
}								t_builtin;

typedef enum token_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HERE_DOC,
	PIPE,
}								t_cmd_type;

typedef enum word_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}								t_word_type;

typedef struct s_token
{
	char						*value;
	t_cmd_type					type;
	t_word_type					quote;
}								t_token;

typedef struct s_redir
{
	char						*file;
	int							type;
	bool						append;
}								t_redir;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_command
{
	t_redir						**redir;
	char						**args;
	int							argc;
	int							builtin_value;
	int							pid;
	struct s_command			*next;
}								t_command;

typedef struct s_shell
{
	t_command					*cmds;
	t_env						*env;
	char						**here_docs;
	int							exit_status;
}								t_shell;

typedef struct s_pipe_ends
{
	int							read;
	int							write;
}								t_pipe_ends;

typedef struct s_exec_data
{
	char						**env_arr;
	int							last_status;
	int							stdin_backup;
	int							stdout_backup;
}								t_exec_data;

typedef struct s_pipe_data
{
	int							pipe_fds[2];
	int							prev_pipe_read;
}								t_pipe_data;

typedef struct s_executor
{
	t_shell						*shell;
	t_command					*current;
	t_exec_data					*exec;
	t_pipe_data					*pipe_data;
	char						**heredoc_files;
	int							status;
}								t_executor;

//  create_command.c
t_token							*create_token(char *value, t_cmd_type type,
									t_word_type quote);
t_command						*new_command(void);
t_command						*parse_tokens(t_token **tokens);
// tokenize
int								ft_isspace(char c);
t_token							**tokenize(char *line);
int								post_tokenize(t_token **tokens, t_shell *shell);
void							free_tokens(t_token **tokens);
void							show_tokens(t_token **tokens);
t_env							*ft_envlst_new(char *key, char *value);
void							ft_envlst_add_back(t_env **lst, t_env *new);
t_env							*init_env(char **envp);
void							free_env(t_env *env);
t_token							**pre_process_redirections(t_token **tokens);
t_token							**take_ur_token_and_leave_me_alone(char *line,
									t_shell *sh);
int								is_redir_token(t_cmd_type type);

// parsing
void							frcm(t_command **command);

//  parse_utils.c
void							add_argument(t_command *cmd, char *arg);
void							add_redirection(t_command *cmd, t_token *token);
void							init_parse(t_command **cmds,
									t_command **current);
// wichbuiltin.c
int								ft_strlen_tab(char **tab);
int								whichbuiltin(char *s);

// builtins

int								ft_env(t_env *envp);
int								ft_cd(t_shell *shell);
int								change_directory(t_shell *shell, char *path);
int								change_to_home(t_shell *shell);
int								ft_echo(int argc, char **argv);
int								ft_exit(int argc, char **argv, t_shell *shell,
									t_exec_data *exec);
int								ft_pwd(t_env *envp);
int								ft_export(char **args, t_shell *shell);
int								ft_unset(t_env **env, char **args);
char							*builtin_get_envv(t_env *env, char *key);

void							ft_loop(t_shell *shell);

/* Execution prototypes */
int								executor(t_shell *shell);
int								exec_single_cmd(t_shell *shell, t_command *cmd,
									t_exec_data *exec);
void							init_exec_data(t_exec_data *exec,
									t_shell *shell);
void							wait_c(t_shell *shell);
int								exec_builtin(t_command *cmd, t_env *env,
									t_shell *shell, t_exec_data *exec);
int								is_builtin(char *cmd);
char							**process_heredocs(t_command *cmds);
void							clean_heredoc_f(char **heredoc_files, int pid);
void							error_line2(int fd, char *line);
int								count_heredocs(t_command *cmds);
void							cleanup_heredocs(char **heredoc_fi, int count,
									int pid);
char							*get_heredoc_filename(void);
int								cmd_size(t_command *cmds);
int								cmd_size_redi(t_command *cmds);
int								verif_heredoc(char **files, t_command *cmds,
									t_shell *shell);
int								pipe_fork(t_command *cmds, int *pipe_fds,
									char **file);
int								update_pipe_read(int prev_pipe_read,
									t_command *cmds, int *pipe_fds);
int								do_builtin(t_exec_data *exec, t_command *cmd,
									t_shell *shell, char **files);
int								exec_command(t_shell *shell, t_command *cmd,
									t_exec_data *exec, t_pipe_data *pipe_data);
int								handle_command2(t_command *cmd, int pipe_fds[2],
									char **heredoc_files);
int								is_single_builtin(t_command *cmd);

/* Path handling */
char							*find_command_path(char *cmd, char **env_paths);
char							**get_path_dirs(char **env);
int								check_command_access(char *cmd_path);

/* Redirections */
int								handle_redirections(t_command *cmd);
void							reset_redirections(t_exec_data *exec);
void							backup_std_fds(t_exec_data *exec);
void							restore_std_fds(t_exec_data *exec);

/* Environment */
char							**env_list_to_array(t_env *env);
void							free_env_array(char ***env_arr_ptr);
char							*get_env_value(t_env *env, char *key);

/* Error handling */
void							print_exec_error(char *cmd, char *error);
void							hcnf(char *cmd);
int								print_file_error(char *file, char *error);
void							exit_with_error(char *msg, int code);

/* Pipe handling */
int								setup_pipes(t_pipe_ends *pipes);
void							close_pipe_ends(t_pipe_ends *pipes);

void							ft_free_args(char **args);
int								process_redirection(t_redir *redir, int type);

int								handle_hrdc_e(t_executor *executor);
int								handle_btn_e(t_executor *executor);
int								execute_cmd_e(t_executor *executor);
void							init_executor(t_executor *executor,
									t_shell *shell, t_exec_data *exec,
									t_pipe_data *pipe_data);

#endif
