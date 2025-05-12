/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/05/12 19:34:11 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check if quotes in a string are properly balanced
 * Counts single and double quotes ensuring none are left unclosed
 * Returns 1 if balanced, 0 otherwise
 */
int	ft_is_quotes_balanced(const char *str)
{
	int	in_single_quotes;
	int	in_double_quotes;
	int	i;

	if (!str)
		return (1);
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		i++;
	}
	return (!in_single_quotes && !in_double_quotes);
}

/* Function to join three strings together
 * Allocates memory for the resulting string
 * Returns newly allocated string, NULL if allocation fails
 */
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = (char *)malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	ft_strlcpy(result + len1 + len2, s3, len3 + 1);
	return (result);
}

/* Function to handle unclosed quotes in input
 * If quotes are unbalanced, prompts for additional input until quotes are closed
 * Returns 1 if processing successful, 0 if error occurred

int	ft_handle_quotes_in_input(t_data *data)
{
	char	*additional_input;
	char	*temp;
	char	*prompt;

	if (ft_is_quotes_balanced(data->input))
		return (1);
	prompt = "> ";
	while (!ft_is_quotes_balanced(data->input))
	{
		additional_input = readline(prompt);
		if (!additional_input)
		{
			ft_putendl_fd("minishell: unexpected EOF while looking for"
				" matching quote", 2);
			data->status = 1;
			return (0);
		}
		temp = data->input;
		data->input = ft_strjoin3(data->input, "\n", additional_input);
		free(temp);
		free(additional_input);
		if (!data->input)
		{
			ft_putendl_fd("minishell: memory allocation error", 2);
			data->status = 1;
			return (0);
		}
	}
	return (1);
}
	*/
