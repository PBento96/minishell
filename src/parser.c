/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:33:15 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check if a character is a word boundary
 * Checks for spaces and special shell characters
 * Only considers it a boundary if not inside quotes
 * Returns true if the character is a word boundary
 */
static int	is_word_boundary(char c, int in_quotes)
{
	return (!in_quotes && (ft_isspace(c) || c == '|' || c == '>' || c == '<'));
}

/* Function to extract, expand and process a word
 * Creates a substring from start to current position
 * Expands variables and removes quotes
 * Returns the final processed word
 */
static char	*extract_and_process_word(char *start, char **ptr, t_data *data)
{
	char	*word;
	char	*expanded_word;
	char	*final_word;

	word = ft_substr(start, 0, *ptr - start);
	expanded_word = ft_expand_variables(word, data);
	free(word);
	final_word = ft_remove_quotes(expanded_word);
	free(expanded_word);
	return (final_word);
}

/* Function to parse a word from input
 * Extracts characters until a word boundary is reached
 * Handles quotes according to shell rules
 * Returns the processed word
 */
char	*ft_parse_word(char **ptr, t_data *data)
{
	char	*start;
	int		in_quotes;
	char	quote_type;

	start = *ptr;
	in_quotes = 0;
	quote_type = '\0';
	while (**ptr)
	{
		if (handle_quotes(ptr, &in_quotes, &quote_type))
			continue ;
		if (is_word_boundary(**ptr, in_quotes))
			break ;
		(*ptr)++;
	}
	return (extract_and_process_word(start, ptr, data));
}

/* Function to check if a command is a shell builtin
 * Compares the command name with known builtin commands
 * Returns true if command is a builtin, false otherwise
 */
bool	ft_is_builtin(const char *command)
{
	if (strcmp(command, OP_PWD) == 0
		|| strcmp(command, OP_ENV) == 0
		|| strcmp(command, OP_ECHO) == 0
		|| strcmp(command, OP_EXT) == 0
		|| strcmp(command, OP_EXP) == 0
		|| strcmp(command, OP_UNS) == 0
		|| strcmp(command, OP_CD) == 0)
		return (true);
	return (false);
}
