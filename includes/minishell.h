/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:39 by pda-silv          #+#    #+#             */
/*   Updated: 2025/01/28 11:06:28 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft/libft.h"

# define OP_SQUOTE			'\''
# define OP_DQUOTE			'\"'
# define OP_REDIRECT_IN		'<'
# define OP_REDIRECT_OUT	'>'
# define OP_REDIRECT_DELIM	"<<"
# define OP_REDIRECT_APPEND	">>"
# define OP_PIPE			'|'
# define OP_VAR				'$'
# define OP_EXIT_STATUS		"$?"
# define OP_ECHO			"echo"
# define OP_NO_NL			"-n"
# define OP_PWD				"pwd"
# define OP_EXP				"export"
# define OP_UNS				"unset"
# define OP_ENV				"env"
# define OP_EXT				"exit"
# define OP_OR				"||"
# define OP_AND				"&&"
# define OP_WILD			"*"
# define MAX_INPUT_SIZE 1024
# define MAX_PIPE_COUNT 10
# define MAX_TOKENS 100
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef enum e_token_type
{
	CMD,
	BUILTIN,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
} t_token;

typedef struct s_command
{
	t_token	*tokens;
	int		token_count;
} t_command;

void		ft_header(void);
t_command	*ft_parse_input(char *input, int *command_count);
void		ft_print_commands(t_command *commands, int command_count);
t_token		*ft_tokenize_input(char *input, int *token_count);
void		ft_free_commands(t_command *commands, int command_count);
char		*ft_parse_word(char **ptr);
bool		is_builtin(const char *command);

#endif
