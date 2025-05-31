/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/29 21:44:48 by joseferr         ###   ########.fr       */
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
	int		i;
	int		j;
	char	quote_type;

	i = 0;
	j = 0;
	quote_type = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (quote_type == '\0'
				|| quote_type == str[i]))
		{
			if (quote_type == '\0')
				quote_type = str[i];
			else
				quote_type = '\0';
		}
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

/* Function to handle quotes during parsing
 * Updates the quote state when quotes are encountered
 * Advances the pointer past the quote character
 * Returns 1 if a quote was handled, 0 otherwise
 */
int	handle_quotes(char **ptr, int *in_quotes, char *quote_type)
{
	if (!ptr || !*ptr || !**ptr)
		return (0);
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
		*quote_type = '\0';
		(*ptr)++;
		return (1);
	}
	return (0);
}

/* Function to handle quotes in a string
 * Tracks quote state and updates in_quotes array
 * Adds the quote character to the result string
 * Returns the updated result string
 */
char	*handle_quote(char *word, int *i, char *result, int *in_quotes)
{
	char	quote;
	char	*new_result;

	quote = word[*i];
	if (quote == '\'' || quote == '\"')
	{
		if ((quote == '\'' && !in_quotes[1])
			|| (quote == '\"' && !in_quotes[0]))
		{
			if (quote == '\'')
				in_quotes[0] = !in_quotes[0];
			else
				in_quotes[1] = !in_quotes[1];
		}
		new_result = append_char(result, word[*i]);
		if (!new_result)
		{
			free(result);
			return (NULL);
		}
		result = new_result;
		(*i)++;
	}
	return (result);
}
