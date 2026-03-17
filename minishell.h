
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

typedef struct s_token
{
    int type;
    char *value;
    struct s_token *next;
}			t_token;

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_APPEND 3
# define TOKEN_REDIR_IN 4
# define TOKEN_HEREDOC 5
# define TOKEN_SPACE 6

t_token	*new_token(char *input, int len, int type);
t_token	*add_back_token(t_token *new_token, t_token **arr_token);
t_token	*free_token_arr(t_token *head);
t_token *tokenization(char *input);
void	print_token_arr(t_token *token_arr);

#endif
/*
 TOKEN_PIPE == |
 TOKEN_REDIR_OUT == >
 TOKEN_APPEND == >>
 TOKEN_REDIR_IN == <
 TOKEN_HEREDOC == <<
*/