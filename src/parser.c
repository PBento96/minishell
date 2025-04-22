/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 20:39:45 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to count the number of characters in a string without quotes
 * Counts characters while skipping single and double quotes
 * Returns the length of the string without quotes
 */
static int	count_chars_without_quotes(char *str)
{
	int	i;
	int	len;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	len = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			len++;
		i++;
	}
	return (len);
}

/* Function to copy a string while removing quotes
 * Copies characters from input string to result string
 * Skips quote characters while tracking quote state
 */
static void	copy_without_quotes(char *str, char *result)
{
	int	i;
	int	j;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
}

/* Function to remove quotes from a string
 * Creates a new string with all quotes removed
 * Returns the new string or NULL if memory allocation fails
 */
char	*ft_remove_quotes(char *str)
{
	char	*result;
	int		len;

	len = count_chars_without_quotes(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	copy_without_quotes(str, result);
	return (result);
}

/* Function to check if a token is a redirection
 * Checks if token type is one of the redirection types
 * Returns true if token is a redirection, otherwise false
 */
static int	is_redirection(int token_type)
{
	return (token_type == REDIR_APPEND || token_type == REDIR_DELIM
		|| token_type == REDIR_IN || token_type == REDIR_OUT);
}

/* Function to handle redirection tokens
 * Processes output or input redirection based on token type
 * Updates the command's redirection information
 */
static void	handle_redirection(t_command *command, int *i)
{
	if (command->tokens[*i].type == REDIR_OUT
		|| command->tokens[*i].type == REDIR_APPEND)
	{
		if (command->tokens[*i].type == REDIR_APPEND)
			command->redir.append = true;
		(*i)++;
		ft_open_redirect_fds(&command->redir, NULL, command->tokens[*i].value);
	}
	else if (command->tokens[*i].type == REDIR_DELIM)
	{
		(*i)++;
		command->redir.delim = ft_strdup(command->tokens[*i].value);
		printf("delim: %s\n", command->redir.delim);
	}
	else
	{
		(*i)++;
		ft_open_redirect_fds(&command->redir, command->tokens[*i].value, NULL);
	}
}

/* Function to clean up allocated argument array
 * Frees each string in the array and then the array itself
 * Used for error handling to prevent memory leaks
 */
static void	cleanup_args(char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(args[i++]);
	free(args);
}

/* Function to convert tokens to argument array
 * Creates an array of strings from command tokens
 * Handles redirections separately and skips them in the argument array
 * Returns the argument array or NULL if memory allocation fails
 */
/* Function to process non-redirection tokens and add to args array
 * Handles memory allocation and error checking
 * Returns 0 on failure or 1 on success
 */
static int	process_token(t_command *command, char **args, int i, int *j)
{
	args[*j] = ft_strdup(command->tokens[i].value);
	if (!args[*j])
		return (0);
	(*j)++;
	return (1);
}

/* Function to convert tokens to argument array
 * Creates an array of strings from command tokens
 * Handles redirections separately and skips them in the argument array
 * Returns the argument array or NULL if memory allocation fails
 */
char	**ft_tokens_to_args(t_command *command)
{
	char	**args;
	int		i;
	int		j;

	args = (char **)malloc((command->token_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (i < command->token_count)
	{
		if (!is_redirection(command->tokens[i].type))
		{
			if (!process_token(command, args, i, &j))
			{
				cleanup_args(args, j);
				return (NULL);
			}
		}
		else
			handle_redirection(command, &i);
		i++;
	}
	args[j] = NULL;
	return (args);
}

/* Function to append a character to a string
 * Creates a new string with the character appended
 * Frees the original string and returns the new one
 */
static char	*append_char(char *str, char c)
{
	char	tmp_str[2];
	char	*tmp;

	tmp_str[0] = c;
	tmp_str[1] = '\0';
	tmp = ft_strjoin(str, tmp_str);
	free(str);
	return (tmp);
}

/* Function to handle alphanumeric variable expansion
 * Extracts the variable name and looks up its value
 * Appends the value to the result string if found
 * Returns the updated result string
 */
static char	*handle_alphanum_var(char *word, int *i, t_data *data, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		start;

	start = *i;
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		(*i)++;
	var_name = ft_substr(word, start, *i - start);
	var_value = ft_getenv(var_name, data->env);
	free(var_name);
	if (var_value)
	{
		tmp = ft_strjoin(result, var_value);
		free(result);
		return (tmp);
	}
	return (result);
}

/* Function to handle variable expansion
 * Expands environment variables in a string
 * Special handling for $?, alphanumeric variables, and edge cases
 * Returns the result string with expanded variables
 */
static char	*handle_variable(char *word, int *i, t_data *data, char *result)
{
	char	*var_value;
	char	*tmp;

	(*i)++;
	if (!word[*i])
		return (ft_strjoin(result, "$"));
	if (word[*i] == '?')
	{
		var_value = ft_itoa(data->status);
		tmp = ft_strjoin(result, var_value);
		free(result);
		free(var_value);
		(*i)++;
		return (tmp);
	}
	if (ft_isalnum(word[*i]) || word[*i] == '_')
		return (handle_alphanum_var(word, i, data, result));
	if (word[*i] == '\'' || word[*i] == '\"')
		return (ft_strjoin(result, "$"));
	tmp = ft_strjoin(result, "$");
	free(result);
	result = tmp;
	return (append_char(result, word[(*i)++]));
}

/* Function to handle quotes in a string
 * Tracks quote state and updates in_quotes array
 * Adds the quote character to the result string
 * Returns the updated result string
 */
static char	*handle_quote(char *word, int *i, char *result, int *in_quotes)
{
	char	quote;

	quote = word[*i];
	if ((quote == '\'' && !in_quotes[1]) || (quote == '\"' && !in_quotes[0]))
	{
		if (quote == '\'')
			in_quotes[0] = !in_quotes[0];
		else
			in_quotes[1] = !in_quotes[1];
		result = append_char(result, word[*i]);
		(*i)++;
	}
	return (result);
}

/* Function to expand variables in a string
 * Processes the string character by character
 * Handles quotes and variable expansion separately
 * Returns the new string with variables expanded
 */
char	*ft_expand_variables(char *word, t_data *data)
{
	char	*result;
	int		i;
	int		quotes[2];

	result = ft_strdup("");
	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
			result = handle_quote(word, &i, result, quotes);
		else if (word[i] == '$' && !quotes[0])
			result = handle_variable(word, &i, data, result);
		else
			result = append_char(result, word[i++]);
	}
	return (result);
}

/* Function to handle quotes during parsing
 * Updates the quote state when quotes are encountered
 * Advances the pointer past the quote character
 * Returns 1 if a quote was handled, 0 otherwise
 */
static int	handle_quotes(char **ptr, int *in_quotes, char *quote_type)
{
	if ((**ptr == '\'' || **ptr == '\"') && !*in_quotes)
	{
		*in_quotes = 1;
		*quote_type = **ptr;
		(*ptr)++;
		return (1);
	}
	else if (*in_quotes && **ptr == *quote_type)
	{
		*in_quotes = 0;
		(*ptr)++;
		return (1);
	}
	return (0);
}

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
			continue;
		if (is_word_boundary(**ptr, in_quotes))
			break;
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
