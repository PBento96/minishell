/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:39 by pda-silv          #+#    #+#             */
/*   Updated: 2025/01/27 12:26:01 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef enum e_command_type
{
	BUILTIN,
	EXTERNAL,
	OTHER
}	t_command_type;

typedef struct s_data
{
	t_command_type	type;
	char			*command;
	char			**args;
	int				argc;
	int				input_size;
	char			**env;
}	t_data;

void	ft_header(void);
void	ft_parse_and_exec_cmd(char *input, char **env);

#endif
