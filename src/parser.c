/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/05 13:08:30 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_remove_quotes(char *str)
{
	char *result;
	int i = 0, j = 0;
	int in_single_quotes = 0;
	int in_double_quotes = 0;

	// First count the length without quotes
	int len = 0;
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

	// Allocate memory for the result
	result = malloc(len + 1);
	if (!result)
		return NULL;

	// Copy the string without quotes
	i = 0;
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
	return result;
}

char	**ft_tokens_to_args(t_token *tokens, int token_count)
{
	char	**args;
	int		i;

	args = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type != REDIR_APPEND && tokens[i].type != REDIR_DELIM
				&& tokens[i].type != REDIR_IN && tokens[i].type != REDIR_OUT)
		{
			args[i] = ft_strdup(tokens[i].value);
			if (!args[i])
			{
				while (--i >= 0)
					free(args[i]);
				free(args);
				return (NULL);
			}
		}
		i++;
	}
	args[i] = NULL;
	return (args);
}

// Add this function to handle variable expansion
char	*ft_expand_variables(char *word, t_data *data)
{
	char *result;
	char *var_name;
	char *var_value;
	int i;
	int in_single_quotes;
	int in_double_quotes;


	result = ft_strdup("");
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (word[i])
	{
		// Handle quotes
		if (word[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			// Preserve quotes for now, they'll be removed later
			char tmp_str[2] = {word[i], '\0'};
			char *tmp = ft_strjoin(result, tmp_str);
			free(result);
			result = tmp;
			i++;
			continue;
		}
		else if (word[i] == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			// Preserve quotes for now, they'll be removed later
			char tmp_str[2] = {word[i], '\0'};
			char *tmp = ft_strjoin(result, tmp_str);
			free(result);
			result = tmp;
			i++;
			continue;
		}

		// Handle variable expansion outside single quotes
		if (word[i] == '$' && !in_single_quotes)
		{
			i++;

			// Handle special case where $ is at the end
			if (!word[i])
			{
				char *tmp = ft_strjoin(result, "$");
				free(result);
				result = tmp;
				continue;
			}

			// Handle $? (exit status)
			if (word[i] == '?')
			{
				char *status_str = ft_itoa(data->status);
				char *tmp = ft_strjoin(result, status_str);
				free(result);
				result = tmp;
				free(status_str);
				i++;
			}
			else if (ft_isalnum(word[i]) || word[i] == '_')
			{
				int start = i;

				// Get the variable name
				while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
					i++;

				var_name = ft_substr(word, start, i - start);
				var_value = ft_getenv(var_name, data->env);

				if (var_value)
				{
					char *tmp = ft_strjoin(result, var_value);
					free(result);
					result = tmp;
				}

				free(var_name);
			}
			else if (word[i] == '\'' || word[i] == '\"')
			{
				// Handle case like echo $"HOME" or $'HOME' in bash
				char *tmp = ft_strjoin(result, "$");
				free(result);
				result = tmp;
				// Don't increment i, let the quote handling process this character
			}
			else
			{
				// $ followed by invalid character, just append $
				char *tmp = ft_strjoin(result, "$");
				free(result);
				result = tmp;

				// Add the character after $ as well
				char tmp_str[2] = {word[i], '\0'};
				tmp = ft_strjoin(result, tmp_str);
				free(result);
				result = tmp;
				i++;
			}
		}
		else
		{
			// Append current character
			char tmp_str[2] = {word[i], '\0'};
			char *tmp = ft_strjoin(result, tmp_str);
			free(result);
			result = tmp;
			i++;
		}
	}

	return result;
}

// Modify ft_parse_word to use this expansion function
char *ft_parse_word(char **ptr, t_data *data)
{
	char *start;
	char *word;
	char *expanded_word;
	char *final_word;
	int in_quotes = 0;
	char quote_type = '\0';

	start = *ptr;
	while (**ptr)
	{
		// Handle quotes
		if ((**ptr == '\'' || **ptr == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_type = **ptr;
			(*ptr)++;
			continue;
		}
		else if (in_quotes && **ptr == quote_type)
		{
			in_quotes = 0;
			(*ptr)++;
			continue;
		}
		// End word at unquoted spaces or operators
		if (!in_quotes && (ft_isspace(**ptr) || **ptr == '|' ||
			**ptr == '>' || **ptr == '<'))
			break;

		(*ptr)++;
	}
	word = ft_substr(start, 0, *ptr - start);
	expanded_word = ft_expand_variables(word, data);
	free(word);
	// Remove quotes after expansion
	final_word = ft_remove_quotes(expanded_word);
	free(expanded_word);

	return final_word;
}

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
