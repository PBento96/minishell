/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:32:25 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to append a character to a string
 * Creates a new string with the character appended
 * Frees the original string and returns the new one
 */
char	*append_char(char *str, char c)
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
