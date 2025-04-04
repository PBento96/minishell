/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:39 by pda-silv          #+#    #+#             */
/*   Updated: 2025/04/04 09:53:17 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define OP_SQUOTE '\''
# define OP_DQUOTE '\"'
# define OP_REDIRECT_IN '<'
# define OP_REDIRECT_OUT '>'
# define OP_REDIRECT_DELIM "<<"
# define OP_REDIRECT_APPEND ">>"
# define OP_PIPE '|'
# define OP_VAR '$'
# define OP_EXIT_STATUS "$?"
# define OP_ECHO "echo"
# define OP_NO_NL "-n"
# define OP_PWD "pwd"
# define OP_EXP "export"
# define OP_UNS "unset"
# define OP_ENV "env"
# define OP_EXT "exit"
# define OP_CD "cd"
# define OP_OR "||"
# define OP_AND "&&"
# define OP_WILD "*"
# define MAX_INPUT_SIZE 1024
# define MAX_CWD_SIZE 4096
# define MAX_PIPE_COUNT 10
# define MAX_TOKENS 100

typedef enum e_token_type
{
	CMD,
	BUILTIN,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND
}	t_token_type;

typedef struct s_redir
{
	char	*in_file;
	char	*out_file;
	char	*delimiter;
	int		in_fd;
	int		out_fd;
	bool	append;
}	t_redir;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_command
{
	t_token	tokens[MAX_TOKENS];
	int		token_count;
}	t_command;

typedef struct s_data
{
	t_command	commands[MAX_PIPE_COUNT];
	char		cwd[MAX_CWD_SIZE];
	char		**env;
	char		*input;
	char		*cmd_path;
	int			status;
	int8_t		cmd_count;
	int			prev_pipe;
	int			piped;
	int8_t		retval;
	pid_t		*pids;
}	t_data;

extern int	g_signal;

//	Parsing
void	ft_tokenize_input(t_data *data);
char	*ft_parse_word(char **ptr, t_data *data);
bool	ft_is_builtin(const char *command);
char	**ft_tokens_to_args(t_token *tokens, int token_count);

//	Memory
int		ft_initilaize(t_data **data, char **env);
void	ft_shutdown(t_data **data, int retval);

//	Execution
void	ft_execute(t_data *data);
char	*ft_getenv(const char *name, char **env);

//	Builtin
void	ft_execute_builtin(t_data *data, char **cmd_args);
void	ft_exit(t_data *data, char **cmd_args);
void	ft_export(t_data *data, char **cmd_args);
void	ft_unset(t_data *data, char **cmd_args);
void	ft_cd(t_data *data, char **cmd_args);

//	Pathing
void	ft_getpath(t_data *data, int i);
char	*ft_expand_variables(char *word, t_data *data);

//	Pipe
void	ft_handle_pipes(t_data *data, int pipefd[2], int command);
void	ft_wait_children(t_data *data, pid_t *pids);
void	ft_pipe_error(t_data *data, char	**cmd_args);

//	Error handling
void	ft_setup_pipes(int pipefd[2]);
void	ft_pipe_error(t_data *data, char	**cmd_args);
void	ft_free_cmd(t_data *data, char	**cmd_args);

//	FD handling
void	ft_open_redirect_fds(t_redir *redir);
void	ft_close_redirect_fds(t_redir *redir);

#endif
