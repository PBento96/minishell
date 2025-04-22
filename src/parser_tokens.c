/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:50 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:12:44 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
