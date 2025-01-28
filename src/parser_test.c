/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:11:45 by joseferr          #+#    #+#             */
/*   Updated: 2025/01/27 23:02:43 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_commands(t_command *commands, int command_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("Parsed Commands:\n");
	while (i < command_count)
	{
		ft_printf("Command %d:\n", i + 1);
		while (j < commands[i].token_count)
		{
			ft_printf("  Token %d: Type = %d, Value = '%s'\n",
				j + 1,
				commands[i].tokens[j].type,
				commands[i].tokens[j].value);
			j++;
		}
		i++;
	}
}
