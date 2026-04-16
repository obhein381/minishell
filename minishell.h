
#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include "srcs/libft/libft.h"

typedef struct s_token
{
    int		type;
    char	*value;
	struct	s_token *next;
}			t_token;

typedef struct s_command
{
	char				**argv;
	pid_t				pid;
	int					count;
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
}						t_command;

typedef struct s_parser_state
{
	t_token	*prev;
	t_token	*cur;
	int		token_count;
}	t_parser_state;

typedef struct	s_shell
{
	char		*input;
	char		**envp;
	t_command	*commands;
}	t_shell;

/* token types */
# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_APPEND 3
# define TOKEN_REDIR_IN 4
# define TOKEN_HEREDOC 5
# define TOKEN_SPACE 6
# define TOKEN_SIG_QUOTE 7
# define TOKEN_DOU_QUOTE 8

/* builtin command types */
# define UNKNOWN_COMMAND 0
# define COMMAND_ECHO 10
# define COMMAND_CD 11
# define COMMAND_PWD 12
# define COMMAND_EXPORT 13
# define COMMAND_UNSET 14
# define COMMAND_ENV 15
# define COMMAND_EXIT 16
# define COMMAND_MIN_N 20

/* parser / runtime errors */
# define MALLOC_ERROR 9
# define PIPE_ERROR 2
# define REDIR_ERROR 3
# define FD_ERROR 4
# define TOKEN_EMPTY 5
# define NO_COMMAND 6
# define EMPTY_ENVP 7
# define READ_ERROR 8

/* command path resolution status */
# define CMD_SUCCESS 0
# define CMD_PERROR 1
# define CMD_NOT_FOUND 127
# define CMD_PERMISSION 126
# define CMD_MALLOC_ERROR 9
# define CMD_UNKNOWN_ERR 10
# define CMD_EOF 11
# define CMD_FAILURE 12
# define CMD_DUP_ERROR 13
# define CMD_ROLLBACK_ERROR 14
# define CMD_QUOTE_ERROR 15

void		print_commands(t_command *commands);
void		print_token_arr(t_token *token_arr);

int			build_commands(t_command **commands, t_shell *shell);
char		**dup_envp(char **envp);
void		free_envp(char **new_envp, int count);
int			envp_len(char **envp);
t_token		*new_token(char *input, int len, int type);
t_token		*add_back_token(t_token *new_token, t_token **arr_token);
void		free_token_arr(t_token *head);
int			identify_token(char *input);
int			tokenization(char *input, t_token **token_arr, t_shell *shell);
t_command	*add_back_command(t_command **commands, t_command *new);
t_command	*new_command(int token_count);
t_command	*free_command_arr(t_command *head);
int			parser_redir(t_command **commands, t_parser_state *state);
int			parser_pipe(t_command **commands, t_command **cur, int token_count);
int			parser_word(t_command **commands, t_parser_state state);
int 		parser(t_token	*token_arr, t_command **commands);
int			check_pipe_syntax(t_command *commands);
int			executor(t_shell *shell);
int			handle_slash_command(char *command, char **path);
int			get_path_index(char **envp);
char		**make_dirs(char *command, char *path);
void		free_dirs(char **dirs);
int			find_cmd_input_path(char **dirs, char **path);
int			find_command_path(char *command, char **envp, char **path);
int			execute_external(t_command *commands, char **envp);
int			execute_echo(t_command *commands);
int			execute_env(t_shell *shell);
int			find_key_index(char *argv);
int			check_key(char *argv, int n);
int			find_key_envp(char **envp, char *key, int key_index);
int			execute_export(t_command *command, t_shell *shell);
int			execute_builtin(t_command *command, t_shell *shell, int type);
int			execute_multi_cmd(t_shell *shell);
int			execute_single_cmd(t_command *command, t_shell *shell);
int			get_builtin_type(t_command *commands);
int			convert_exit_status(int status);
int			execute_external_child(t_shell *shell, t_command *command);
int			wait_all_child(t_command *commands);
void		close_all_fd(int *fd);
int			add_token_sig_quote(t_token **token_arr, char *input, int *i, int type);
int			add_token_dou_quote(t_token **token_arr, t_shell *shell, int *i, int type);

#endif
/*
 TOKEN_PIPE == |
 TOKEN_REDIR_OUT == >
 TOKEN_APPEND == >>
 TOKEN_REDIR_IN == <
 TOKEN_HEREDOC == <<
*/