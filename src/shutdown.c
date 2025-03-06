/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:37:51 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/06 19:26:20 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shutdown(t_data **data, int retval)
{
	ft_printf(C_YELLOW"\nExiting Minishell...\n"RESET_COLOR);
	ft_free((void **)data);
	exit(retval);
}
