/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseferr <joseferr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:37:51 by pda-silv          #+#    #+#             */
/*   Updated: 2025/03/24 11:27:48 by joseferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shutdown(t_data *data, int retval)
{
	ft_printf(C_YELLOW"\nExiting Minishell...\n"RESET_COLOR);
	ft_free((void **)data);
	exit(retval);
}
