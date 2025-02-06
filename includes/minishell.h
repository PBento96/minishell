/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:39 by pda-silv          #+#    #+#             */
/*   Updated: 2025/02/06 20:15:15 by pda-silv         ###   ########.fr       */
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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_command
{
	t_token	*tokens;
	int		token_count;
}	t_command;

typedef struct s_data
{
	t_token		tokens[MAX_TOKENS];
    char        cwd[MAX_CWD_SIZE];
	char		**env;
	char		*input;
	uint16_t	num_tokens;
	int8_t		retval;
}	t_data;

t_command	*ft_parse_input(char *input, int *command_count);
void		ft_print_commands(t_command *commands, int command_count);
t_token		*ft_tokenize_input(char *input, int *token_count);
char		*ft_parse_word(char **ptr);
bool		ft_is_builtin(const char *command);

// Memory
int			ft_initilaize(t_data **data, char **env);
void		ft_shutdown(t_data **data, int retval);
void		ft_free_commands(t_command *commands, int command_count);

#endif
