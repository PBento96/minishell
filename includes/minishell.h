/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:39:39 by pda-silv          #+#    #+#             */
/*   Updated: 2025/01/17 10:05:23 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

#endif