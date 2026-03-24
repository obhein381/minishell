
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

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_APPEND 3
# define TOKEN_REDIR_IN 4
# define TOKEN_HEREDOC 5
# define TOKEN_SPACE 6
# define COMMAND_ECHO 10
# define COMMAND_CD 11
# define COMMAND_PWD 12
# define COMMAND_EXPORT 13
# define COMMAND_UNSET 14
# define COMMAND_ENV 15
# define COMMAND_EXIT 16
# define COMMAND_MIN_N 20
# define MALLOC_ERROR 1
# define PIPE_ERROR 2
# define REDIR_ERROR 3
# define FD_ERROR 4
# define TOKEN_EMPTY 5

void		print_commands(t_command *commands);
void		print_token_arr(t_token *token_arr);

t_token		*new_token(char *input, int len, int type);
t_token		*add_back_token(t_token *new_token, t_token **arr_token);
t_token		*free_token_arr(t_token *head);
t_token 	*tokenization(char *input);
t_command	*add_back_command(t_command **commands, t_command *new);
t_command	*new_command(int token_count);
t_command	*free_command_arr(t_command *head);
int			parser_redir(t_command **commands, t_parser_state *state);
int			parser_pipe(t_command **commands, t_command **cur, int token_count);
int			parser_word(t_command **commands, t_parser_state state);
int 		parser(t_token	*token_arr, t_command **commands);
int			check_pipe_syntax(t_command *commands);

#endif
/*
 TOKEN_PIPE == |
 TOKEN_REDIR_OUT == >
 TOKEN_APPEND == >>
 TOKEN_REDIR_IN == <
 TOKEN_HEREDOC == <<
*/