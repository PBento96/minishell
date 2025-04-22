/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:23:36 by joseferr          #+#    #+#             */
/*   Updated: 2025/04/22 21:35:05 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote_balanced(const char *str)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !(double_quotes % 2))
			single_quotes++;
		else if (str[i] == '\"' && !(single_quotes % 2))
			double_quotes++;
		i++;
	}
	return ((single_quotes % 2 == 0) && (double_quotes % 2 == 0));
}

int	ft_handle_quotes_in_input(t_data *data)
{
	if (!ft_is_quote_balanced(data->input))
	{
		ft_putendl_fd("minishell: unclosed quotes detected", 2);
		data->status = 1;
		return (0);
	}
	return (1);
}
